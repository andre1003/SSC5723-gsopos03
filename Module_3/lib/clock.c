#include "clock.h"
#include "manager.h"
#include "process.h"
#include "stdlib.h"
#include "stdio.h"
#include "swap.h"
#include "limits.h"




#pragma region Structs
typedef struct CLOCK_NODE {
	page* page;
	struct CLOCK_NODE* next;
} clock_node;

typedef struct CLOCK_LIST {
	clock_node* end;
} clock_list;
#pragma endregion


clock_list* global_clock_list = NULL;

#pragma region Init
void init_clock() {
	global_clock_list = malloc(sizeof(clock_node));
	global_clock_list->end = NULL;
}
#pragma endregion

#pragma region Checker and Finder
int list_empty(void) {
	if(global_clock_list->end == NULL)
		return TRUE;
	return FALSE
}

clock_node* find_node_clock(page* pg, clock_node** previous) {
	*previous = NULL;
	clock_node* current = global_clock_list->end->next;

	if(list_empty() == TRUE)
		return NULL;

	do {
		if(current->page == pg)
			return current;

		*previous = current;
		current = current->next;
	} while(current != global_clock_list->end->next);

	return NULL;
}
#pragma endregion

#pragma region Insert
page* insert_set_pages_clock(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		if(insert_page_clock(&pages_set[i]) == NULL)
			return NULL;
	}
	return pages_set;
}

page* insert_page_clock(page* new_page) {
	clock_node* node = malloc(sizeof(clock_node));
	node->next = NULL;
	node->page = new_page;

	if(list_empty() == TRUE) {
		global_clock_list->end = node;
		global_clock_list->end->next = global_clock_list->end;
		return new_page;
	}

	node->next = global_clock_list->end->next;
	global_clock_list->end->next = node;
	global_clock_list->end = node;

	return new_page;
}
#pragma endregion

#pragma region Remove
page* remove_set_pages_clock(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		if(remove_page_clock(&pages_set[i]) == NULL)
			return NULL;
	}

	return pages_set;
}

page* remove_page_clock(page* remove_page) {
	clock_node** previous = malloc(sizeof(clock_node*));
	clock_node* node = find_node_clock(remove_page, previous);

	if(node == NULL)
		return NULL;

	if(*previous == NULL)
		global_clock_list->end->next = node->next;
	else
		(*previous)->next = node->next;

	if(node == node->next)
		global_clock_list->end = NULL;

	if(remove_page->modifed == TRUE) {
		if(send_page_to_disc_page_only(remove_page) == 0)
			return NULL;
	}

	set_frame(remove_page->frame_number, FALSE);
	int* page_number_bits = page_number_from_page(remove_page);
	process* proc = find_process_from_page(remove_page);

	printf("Página '%lld' (%s) do Processo '%s' removida da lista global de páginas.\n",
		get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN),
		bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN),
		proc->id
	);

	free(node);

	return remove_page;

}

int* remove_best_page_clock() {
	clock_node* current = global_clock_list->end->next;
	int* frame_number;

	while(current->page->referenced != 0) {
		current->page->referenced = 0;
		current = current->next;
	}

	frame_number = current->page->frame_number;
	current->page->present = FALSE;

	if(remove_page_clock(current->page) == NULL)
		return NULL;

	return frame_number;
}
#pragma endregion

#pragma region Mapped
int get_number_mapped_pages_clock() {
	clock_node* current = global_clock_list->end->next;
	int count = 0;

	if(list_empty() == TRUE)
		return count;

	do {
		count++;
		current = current->next;
	} while(current != global_clock_list->end->next);

	return count;
}
#pragma endregion
