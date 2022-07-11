#pragma region Includes
#include "process.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "stdio.h"
#include "manager.h"
#pragma endregion




process_list* process_table = NULL;

#pragma region Init
void init_process_list() {
	process_table = (process_list*)malloc(sizeof(process_list));
	process_table->start = NULL;
}
#pragma endregion

#pragma region Finders
process_node* find_last() {
	// Variable declaration
	process_node* current = process_table->start;

	// If current is null, exit this function
	if(current == NULL)
		return NULL;

	// Go through the list
	while(current->next != NULL)
		current = current->next;

	// Return the node
	return current;
}

process* find_process(char* pid) {
	// Variable declaration
	process_node* current = process_table->start;
	process* proc = NULL;

	// Go through the list
	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(pid, current->proc->id) == 0) {
			proc = current->proc;
			break;
		}

		current = current->next;
	}

	// Return the process
	return proc;
}

process* find_process_from_page(page* pg) {
	// Variable declaration
	process_node* current = process_table->start;
	process* proc = NULL;

	// Go through the list
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

	// If no process has been returned, return null
	return NULL;
}

process* choose_process_to_sleep() {
	// Variable declaration
	process_node* current = process_table->start;
	process* proc = NULL;
	int most_number = INT_MIN;

	// Go through the list
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

	// Return the process
	return proc;
}
#pragma endregion

#pragma region Create and Remove Process
process* create_process() {
	// Variable declaration
	process* proc = (process*)malloc(sizeof(process));
	proc->image_size = 0;
	proc->id = NULL;
	proc->status = -1;
	proc->swap_area = NULL;
	proc->table = NULL;

	// If process table is null, init it
	if(process_table == NULL)
		init_process_list();

	// Process node declaration
	process_node* last = find_last();
	process_node* current = (process_node*)malloc(sizeof(process_node));
	
	// Create the node
	current->next = NULL;
	current->proc = proc;

	// If last is null, set the current in the beginning
	if(last == NULL)
		process_table->start = current;
	// Else, set current in the last->next
	else
		last->next = current;

	// Return process
	return proc;
}

void remove_process(process* proc) {
	// Variable declaration
	process_node* current = process_table->start;
	process_node* previous = NULL;

	// Go through the list
	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(proc->id, current->proc->id) == 0) {
			current->proc;
			break;
		}

		previous = current;
		current = current->next;
	}

	// If current is not null
	if(current != NULL) {
		if(previous == NULL)
			process_table->start = current->next;
		else
			previous->next = current->next;

		// Free process and current
		free(current->proc);
		free(current);
	}
}
#pragma endregion

#pragma region Sleep and Wakeup
process* sleep(process* proc) {
	printf("Suspending process '%s'...\n", proc->id);

	// If send page table to disk returns null, exit this function
	if(send_page_table_to_disk(proc->swap_area, proc->table) == NULL)
		return NULL;

	// Set frame status from pages that are present
	int i;
	for(i = 0; i < PAGES_NUMBER; i++) {
		if(proc->table->pages[i].present == TRUE)
			set_frame(proc->table->pages[i].frame_number, FALSE);
	}

	// Varaible declaration
	int number_mapped = count_mapped_pages(proc->table);
	page** mapped_pages = malloc(sizeof(page*) * number_mapped);
	int count = 0;

	// Remove pages until return NULL, then exit this function
	for(i = 0; i < number_mapped; i++) {
		if(remove_page(mapped_pages[i]) == NULL)
			return NULL;
	}

	// Set process status to IN_DISK
	proc->status = IN_DISK;

	// Return process
	return proc;
}

int force_sleep(int size) {
	// Varable declaration
	int free_space = get_free_frames_number();

	// Try to sleep a chosen process
	while(free_space < size) {
		// If sleep returns null, return 0
		if(sleep(choose_process_to_sleep()) == NULL)
			return 0;

		free_space = get_free_frames_number();
	}

	// Return 1
	return 1;
}

process* wakeup(process* proc) {
	printf("Taking process '%s' to the RAM...\n", proc->id);

	// Variable declaration
	int frames = allocation_policy(proc->image_size);
	int free_frames = get_free_frames_number();

	// Is there are free frames
	if(frames <= free_frames) {
		// Set mapped pages number
		int mapped_pages_number = count_mapped_pages(proc->table);
		if(mapped_pages_number > free_frames)
			mapped_pages_number = free_frames;

		// Get mapped pages
		page** mapped_pages = malloc(sizeof(page*) * mapped_pages_number);
		for(int i = 0; i < mapped_pages_number; i++) {
			int* page_number_bits = get_first_present_page(proc->table);
			page* page_address = &proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)];

			proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)].present = FALSE;

			if(get_page_in_disk(proc->swap_area, page_number_bits) == NULL)
				return NULL;

			mapped_pages[i] = page_address;
		}

		// Try to map pages
		for(int i = 0; i < mapped_pages_number; i++) {
			// If map page returns null, exit this function
			if(map_page(proc->table, mapped_pages[i]) == NULL)
				return NULL;
		}

		// Unmap the page table
		unmap_whole_page_table(proc->table);

		// Set mapped pages present to true
		for(int i = 0; i < mapped_pages_number; i++)
			mapped_pages[i]->present = TRUE;

		// Free mapped pages
		free(mapped_pages);

		// If mapped pages number is lower than free frames, get page in disk an map page
		if(mapped_pages_number < free_frames) {
			int count = frames - mapped_pages_number;
			for(int i = mapped_pages_number; i <= proc->image_size / VIRTUAL_PAGE_SIZE; i++) {
				if(count-- > 0) {
					int* page_number_bits = get_bits_from_decimal(i, PAGES_NUMBER_LEN);

					if(get_page_in_disk(proc->swap_area, page_number_bits) == NULL)
						return NULL;

					if(map_page(proc->table, &proc->table->pages[get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN)]) == NULL)
						return NULL;
				}
				else
					break;
			}
		}
	}
	// Else, force to sleep and return the process wakeup
	else {
		if(force_sleep(frames) == 0)
			return NULL;

		return wakeup(proc);
	}

	// Set process status to IN_RAM and return process
	proc->status = IN_RAM;
	return proc;
}
#pragma endregion

#pragma region Reset
void reset_process(process* proc) {
	// Free the process, if it exists
	if(proc != NULL) {
		printf("Deleting process...\n");
		free_swap_area(proc->swap_area, proc->image_size);
		free_page_table(proc->table);
		remove_process(proc);
	}
}
#pragma endregion

#pragma region Print
void print_process_situation() {
	// Variable declaration
	process_node* current = process_table->start;
	int process_count = 0;
	int active = 0;

	// Go through the list
	while(current != NULL) {
		if(current->proc->id != NULL && strcmp(current->proc->id, "") != 0) {
			process_count++;

			if(current->proc->status == IN_RAM) {
				active++;
			}
		}

		current = current->next;
	}

	// Print stats
	printf("Number of existing processes: %d\n", process_count);
	printf("Number of active processes in RAM: %d\n", active);
}
#pragma endregion

#pragma region Page to Disk
int send_page_to_disk_page_only(page* pg) {
	// Try to find process from page
	process* proc = find_process_from_page(pg);
	if(proc == NULL) {
		return 0;
	}

	// Try to find the page
	int i;
	for(i = 0; i < PAGES_NUMBER; i++) {
		if(&proc->table->pages[i] == pg) {
			break;
		}
	}

	// If send page to disk  returns null, return 0
	if(send_page_to_disk(proc->swap_area, pg, get_bits_from_decimal(i, PAGES_NUMBER_LEN)) == NULL) {
		return 0;
	}

	// Return 1
	return 1;
}
#pragma endregion