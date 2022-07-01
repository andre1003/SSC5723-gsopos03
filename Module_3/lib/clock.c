#include "clock.h"
#include "stdlib.h"
#include "stdio.h"
#include "limits.h"




typedef struct CLOCK_NODE {
	page* page;
	struct CLOCK_NODE* next;
} clock_node;

typedef struct CLOCK_LIST {
	clock_node* end;
} clock_list;

clock_list* global_clock_list = NULL;

void init_clock(void) {
	global_clock_list = malloc (sizeof(clock_node));
	global_clock_list->end = NULL;
}

void update_global_list_clock(void) {
}

page* insert_set_pages_clock(page*, int) {
	return nullptr;
}

page* insert_page_clock(page*) {
	return nullptr;
}

page* remove_set_pages_clock(page*, int) {
	return nullptr;
}

page* remove_page_clock(page*) {
	return nullptr;
}

int* remove_best_page_clock(void) {
	return nullptr;
}

int get_number_mapped_pages_clock(void) {
	return 0;
}
