#pragma region Includes
#include "clock.h"
#include "manager.h"
#include "process.h"
#include "stdlib.h"
#include "stdio.h"
#include "swap.h"
#include "limits.h"
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
	return FALSE;
}

clock_node* find_node_clock(page* pg, clock_node** previous) {
	*previous = NULL;
	clock_node* current = global_clock_list->end->next;

	// If list is empty, return null
	if(list_empty() == TRUE)
		return NULL;

	// Go through the clock list
	do {
		if(current->page == pg)
			return current;

		*previous = current;
		current = current->next;
	} while(current != global_clock_list->end->next);

	// If didn't return anything, return null
	return NULL;
}
#pragma endregion

#pragma region Insert
page* insert_set_pages_clock(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		// If insert page returns null, exit this function
		if(insert_page_clock(&pages_set[i]) == NULL)
			return NULL;
	}

	// Return the pages set
	return pages_set;
}

page* insert_page_clock(page* new_page) {
	// Create the node
	clock_node* node = malloc(sizeof(clock_node));
	node->next = NULL;
	node->page = new_page;

	// If list is empty, set it to this new node
	if(list_empty() == TRUE) {
		global_clock_list->end = node;
		global_clock_list->end->next = global_clock_list->end;
		return new_page;
	}
	
	// Reseting the global list pointers
	node->next = global_clock_list->end->next;
	global_clock_list->end->next = node;
	global_clock_list->end = node;

	// Return the new page inserted in list
	return new_page;
}
#pragma endregion

#pragma region Remove
page* remove_set_pages_clock(page* pages_set, int size) {
	int i;
	for(i = 0; i < size; i++) {
		// If remove page returns null exit this function
		if(remove_page_clock(&pages_set[i]) == NULL)
			return NULL;
	}

	// Return the pages set updated
	return pages_set;
}

page* remove_page_clock(page* remove_page) {
	// Variable init
	clock_node** previous = malloc(sizeof(clock_node*));
	clock_node* node = find_node_clock(remove_page, previous);

	// If node was not found, exit this function
	if(node == NULL)
		return NULL;

	// If previous is null, remove the first element
	if(*previous == NULL)
		global_clock_list->end->next = node->next;
	// Else, reconect the previous->next with node->next
	else
		(*previous)->next = node->next;

	// List is now null
	if(node == node->next)
		global_clock_list->end = NULL;

	// If page was modified, send to disk
	if(remove_page->modified == TRUE) {
		if(send_page_to_disk_page_only(remove_page) == 0)
			return NULL;
	}

	// Set frame status
	set_frame(remove_page->frame_number, FALSE);
	int* page_number_bits = page_number_from_page(remove_page);
	process* proc = find_process_from_page(remove_page);

	printf("Page '%lld' (%s) from process '%s' removed from global page list.\n",
		get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN),
		bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN),
		proc->id
	);

	// Free the node
	free(node);

	// Return the updated list
	return remove_page;

}

int* remove_best_page_clock() {
	// Variable declaration
	clock_node* current = global_clock_list->end->next;
	int* frame_number;

	// Go through the pages
	while(current->page->referenced != 0) {
		current->page->referenced = 0;
		current = current->next;
	}

	// Set frame number and present
	frame_number = current->page->frame_number;
	current->page->present = FALSE;

	// If remove page return null, exit the function
	if(remove_page_clock(current->page) == NULL)
		return NULL;

	// Return the frame number
	return frame_number;
}
#pragma endregion

#pragma region Mapped
int get_number_mapped_pages_clock() {
	// Variable declaration
	clock_node* current = global_clock_list->end->next;
	int count = 0;

	// If list is empty, return 0
	if(list_empty() == TRUE)
		return count;

	// Count mapped pages
	do {
		count++;
		current = current->next;
	} while(current != global_clock_list->end->next);

	// Return mapped pages number
	return count;
}
#pragma endregion