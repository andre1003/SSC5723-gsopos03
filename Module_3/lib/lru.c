#include "lru.h"
#include "manager.h"
#include "process.h"
#include "stdlib.h"
#include "stdio.h"
#include "swap.h"
#include "limits.h"






lru_list* global_lru_list = NULL;

#pragma region Init
void init_lru(void) {
	global_lru_list = malloc(sizeof(lru_node));
	global_lru_list->start = NULL;
}
#pragma endregion

#pragma region Find
lru_node* find_node_lru(page* pg, lru_node** previous) {
	*previous = NULL;
	lru_node* current = global_lru_list->start;
	while(current != NULL) {
		if(current->page == pg) {
			return current;
		}
		*previous = current;
		current = current->next;
	}
	return NULL;
}
#pragma endregion

#pragma region Insert
int insert_node_lru(lru_node* node) {
	lru_node* current = global_lru_list->start;

	while(current != NULL) {
		if(current->next == NULL)
			break;

		current = current->next;
	}

	if(current == NULL) {
		global_lru_list->start = node;
		return 1;
	}

	current->next = node;
	return 1;
}

page* insert_set_pages_lru(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		if(insert_page_lru(&pages_set[i]) == NULL)
			return NULL;
	}

	return pages_set;
}

page* insert_page_lru(page* new_page) {
	lru_node* node = malloc(sizeof(lru_node));
	node->next = NULL;
	node->page = new_page;

	if(insert_node_lru(node) == 0)
		return NULL;

	return new_page;
}
#pragma endregion

#pragma region Remove
page* remove_set_pages_lru(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		if(remove_page_lru(&pages_set[i]) == NULL)
			return NULL;
	}

	return pages_set;
}

page* remove_page_lru(page* remove_page) {
	lru_node** previous = malloc(sizeof(lru_node*));
	lru_node* node = find_node_lru(remove_page, previous);

	if(node == NULL)
		return NULL;

	if(*previous == NULL)
		global_lru_list->start = node->next;
	else
		(*previous)->next = node->next;

	if(remove_page->modified == TRUE)
		if(send_page_to_disc_page_only(remove_page) == 0)
			return NULL;

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

int* remove_best_page_lru(void) {
	lru_node* current = global_lru_list->start;
	lru_node* most_node = NULL;
	int most_counter = INT_MAX;

	while(current != NULL) {
		if(current->page->referenced < most_counter) {
			most_counter = current->page->referenced;
			most_node = current;
		}

		current = current->next;
	}

	if(most_node == NULL)
		return NULL;

	int* frame_number = most_node->page->frame_number;
	most_node->page->present = FALSE;

	if(remove_page_lru(most_node->page) == NULL)
		return NULL;

	return frame_number;
}
#pragma endregion

#pragma region Mapped
int get_number_mapped_pages_lru(void) {
	lru_node* current = global_lru_list->start;
	int count = 0;

	while(current != NULL) {
		count++;
		current = current->next;
	}

	return count;
}
#pragma endregion
