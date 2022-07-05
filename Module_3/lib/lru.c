#pragma region Includes
#include "lru.h"
#include "manager.h"
#include "process.h"
#include "stdlib.h"
#include "stdio.h"
#include "swap.h"
#include "limits.h"
#pragma endregion




lru_list* global_lru_list = NULL;

#pragma region Init
void init_lru(void) {
	global_lru_list = malloc(sizeof(lru_node));
	global_lru_list->start = NULL;
}
#pragma endregion

#pragma region Find
lru_node* find_node_lru(page* pg, lru_node** previous) {
	// Variables declaration
	*previous = NULL;
	lru_node* current = global_lru_list->start;

	// Go through the global list
	while(current != NULL) {
		if(current->page == pg) {
			return current;
		}
		*previous = current;
		current = current->next;
	}

	// If no node has been returned, return null
	return NULL;
}
#pragma endregion

#pragma region Insert
int insert_node_lru(lru_node* node) {
	lru_node* current = global_lru_list->start;

	// Go through the list
	while(current != NULL) {
		if(current->next == NULL)
			break;

		current = current->next;
	}

	// If there is not a current node, set it to start
	if(current == NULL) {
		global_lru_list->start = node;
		return 1;
	}

	// Set current->next to node
	current->next = node;
	return 1;
}

page* insert_set_pages_lru(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		// If insert page return null, exit this function
		if(insert_page_lru(&pages_set[i]) == NULL)
			return NULL;
	}

	// Return pages set updated
	return pages_set;
}

page* insert_page_lru(page* new_page) {
	// Variable declaration
	lru_node* node = malloc(sizeof(lru_node));
	node->next = NULL;
	node->page = new_page;

	// If node insertion returns 0, exit this function
	if(insert_node_lru(node) == 0)
		return NULL;

	// Return the new page
	return new_page;
}
#pragma endregion

#pragma region Remove
page* remove_set_pages_lru(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		// If remove page returns null, exit this function
		if(remove_page_lru(&pages_set[i]) == NULL)
			return NULL;
	}

	// Return pages set updated
	return pages_set;
}

page* remove_page_lru(page* remove_page) {
	// Variable declaration
	lru_node** previous = malloc(sizeof(lru_node*));
	lru_node* node = find_node_lru(remove_page, previous);

	// If node is null, return null
	if(node == NULL)
		return NULL;

	// If there is no previous, remove from the beginning
	if(*previous == NULL)
		global_lru_list->start = node->next;
	// Else, remove from previous->next
	else
		(*previous)->next = node->next;

	// If the page to be removed was modified, send it to disk
	if(remove_page->modified == TRUE)
		if(send_page_to_disk_page_only(remove_page) == 0)
			return NULL;

	// Set frame status and varaibles
	set_frame(remove_page->frame_number, FALSE);
	int* page_number_bits = page_number_from_page(remove_page);
	process* proc = find_process_from_page(remove_page);

	printf("Page '%lld' (%s) from process '%s' removed from global page list.\n",
		get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN),
		bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN),
		proc->id
	);

	// Free node
	free(node);

	// Return updated list
	return remove_page;
}

int* remove_best_page_lru(void) {
	// Variable declaration
	lru_node* current = global_lru_list->start;
	lru_node* most_node = NULL;
	int most_counter = INT_MAX;

	// Go through the list
	while(current != NULL) {
		if(current->page->referenced < most_counter) {
			most_counter = current->page->referenced;
			most_node = current;
		}

		current = current->next;
	}

	// If most node is null, exit this function
	if(most_node == NULL)
		return NULL;

	// get frame number and set most node page present to false
	int* frame_number = most_node->page->frame_number;
	most_node->page->present = FALSE;

	// If remove page returns null, exit this function
	if(remove_page_lru(most_node->page) == NULL)
		return NULL;

	// Return the frame number
	return frame_number;
}
#pragma endregion

#pragma region Mapped
int get_number_mapped_pages_lru(void) {
	// Variable declaration
	lru_node* current = global_lru_list->start;
	int count = 0;

	// Go through the list
	while(current != NULL) {
		count++;
		current = current->next;
	}

	// Return the number of mapped pages
	return count;
}
#pragma endregion
