#include "process.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "stdio.h"
#include "manager.h"






process_list* process_table = NULL;

#pragma region Init
void init_process_list() {
	process_table = (process_list*)malloc(sizeof(process_list));
	process_table->start = NULL;
}
#pragma endregion

#pragma region Finders
process_node* find_last() {
	process_node* current = process_table->start;

	if(current == NULL)
		return NULL;

	while(current->next != NULL)
		current = current->next;

	return current;
}

process* find_process(char* pid) {
	process_node* current = process_table->start;
	process* proc = NULL;

	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(pid, current->proc->id) == 0) {
			proc = current->proc;
			break;
		}

		current = current->next;
	}

	return proc;
}

process* find_process_from_page(page* pg) {
	process_node* current = process_table->start;
	process* proc = NULL;

	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(current->proc->id, "") != 0) {
			int i;
			for(i = 0; i < PAGES_NUMBER; i++) {
				if(&current->proc->table->pages[i] == pg)
					return current->proc;
			}
		}

		current = current->next;
	}

	return NULL;
}

process* choose_process_to_sleep() {
	process_node* current = process_table->start;
	process* proc = NULL;
	int most_number = INT_MIN;

	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(current->proc->id, "") != 0) {
			if(current->proc->status == IN_RAM) {
				int aux = count_mapped_pages(current->proc->table);

				if(aux > most_number) {
					most_number = aux;
					proc = current->proc;
				}
			}
		}

		current = current->next;
	}

	return proc;
}
#pragma endregion

#pragma region Create and Remove Process
process* create_process() {
	process* proc = (process*)malloc(sizeof(process));
	proc->image_size = 0;
	proc->id = NULL;
	proc->status = -1;
	proc->swap_area = NULL;
	proc->table = NULL;

	if(process_table == NULL)
		init_process_list();

	
	process_node* last = find_last();
	process_node* current = (process_node*)malloc(sizeof(process_node));
	
	current->next = NULL;
	current->proc = proc;

	if(last == NULL)
		process_table->start = current;
	else
		last->next = current;

	return proc;
}

void remove_process(process* proc) {
	process_node* current = process_table->start;
	process_node* previous = NULL;

	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(proc->id, current->proc->id) == 0) {
			current->proc;
			break;
		}
		previous = current;
		current = current->next;
	}

	if(current != NULL) {
		if(previous == NULL)
			process_table->start = current->next;
		else
			previous->next = current->next;

		free(current->proc);
		free(current);
	}
}
#pragma endregion

#pragma region Sleep and Wakeup
process* sleep(process* proc) {
	printf("Suspendento o Processo '%s'...\n", proc->id);

	if(send_page_table_to_disc(proc->swap_area, proc->table) == NULL)
		return NULL;

	int i;
	for(i = 0; i < PAGES_NUMBER; i++) {
		if(proc->table->pages[i].present == TRUE)
			set_frame(proc->table->pages[i].frame_number, FALSE);
	}

	int number_mapped = count_mapped_pages(proc->table);
	page** mapped_pages = malloc(sizeof(page*) * number_mapped);
	int count = 0;

	for(i = 0; i < number_mapped; i++) {
		if(remove_page(mapped_pages[i]) == NULL)
			return NULL;
	}

	proc->status = IN_DISC;

	return proc;
}

int force_sleep(int size) {
	int free_space = get_free_frames_number();

	while(free_space < size) {
		if(sleep(choose_process_to_sleep()) == NULL)
			return 0;

		free_space = get_free_frames_number();
	}

	return 1;
}

process* wakeup(process* proc) {
	printf("Levando Processo '%s' para a RAM...\n", proc->id);
	int frames = allocation_policy(proc->image_size);
	int free_frames = get_free_frames_number();

	if(frames <= free_frames) {
		int mapped_pages_number = count_mapped_pages(proc->table);
		if(mapped_pages_number > free_frames)
			mapped_pages_number = free_frames;

		page** mapped_pages = malloc(sizeof(page*) * mapped_pages_number);
		for(int i = 0; i < mapped_pages_number; i++) {
			int* page_number_bits = get_first_present_page(proc->table);
			page* page_address = &proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)];

			proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)].present = FALSE;

			if(get_page_in_disc(proc->swap_area, page_number_bits) == NULL)
				return NULL;

			mapped_pages[i] = page_address;
		}

		for(int i = 0; i < mapped_pages_number; i++) {
			if(map_page(proc->table, mapped_pages[i]) == NULL)
				return NULL;
		}

		unmap_whole_page_table(proc->table);

		for(int i = 0; i < mapped_pages_number; i++)
			mapped_pages[i]->present = TRUE;

		free(mapped_pages);

		if(mapped_pages_number < free_frames) {
			int count = frames - mapped_pages_number;
			for(int i = mapped_pages_number; i <= proc->image_size / VIRTUAL_PAGE_SIZE; i++) {
				if(count-- > 0) {
					int* page_number_bits = get_bits_from_decimal(i, PAGES_NUMBER_LEN);

					if(get_page_in_disc(proc->swap_area, page_number_bits) == NULL)
						return NULL;

					if(map_page(proc->table, &proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)]) == NULL)
						return NULL;
				}
				else
					break;
			}
		}
	}
	else {
		if(force_sleep(frames) == 0)
			return NULL;

		return wakeup(proc);
	}

	proc->status = IN_RAM;
	return proc;
}
#pragma endregion

#pragma region Reset
void reset_process(process* proc) {
	if(proc != NULL) {
		printf("Excluindo processo...\n");
		free_swap_area(proc->swap_area, proc->image_size);
		free_page_table(proc->table);
		remove_process(proc);
	}
}
#pragma endregion

#pragma region Print
void print_process_situation() {
	process_node* current = process_table->start;
	int process_count = 0;
	int active = 0;

	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(current->proc->id, "") != 0) {
			process_count++;
			if(current->proc->status == IN_RAM) {
				active++;
			}
		}
		current = current->next;
	}

	printf("Quantidade de Processos existentes: %d\n", process_count);
	printf("Quantidade de Processos ativos na RAM: %d\n", active);
}
#pragma endregion

#pragma region Page to Disc
int send_page_to_disc_page_only(page* pg) {
	process* proc = find_process_from_page(pg);
	if(proc == NULL) {
		return 0;
	}

	int i = 0;
	for(; i < PAGES_NUMBER; i++) {
		if(&proc->table->pages[i] == pg) {
			break;
		}
	}

	if(send_page_to_disc(proc->swap_area, pg, get_bits_from_decimal(i, PAGES_NUMBER_LEN)) == NULL) {
		return 0;
	}

	return 1;
}
#pragma endregion
