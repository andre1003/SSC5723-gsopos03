#include "lru.h"




typedef struct LRU_NODE {
	page* page;
	struct LRU_NODE* next;
} lru_node;

typedef struct LRU_LIST {
	lru_node* start;
} lru_list;

lru_list* global_lru_list = NULL;

void init_lru(void) {
	global_lru_list = malloc(sizeof(lru_node));
	global_lru_list->start = NULL;
}

void update_global_list_lru(void) {
}

page* insert_set_pages_lru(page*, int) {
	return nullptr;
}

page* insert_page_lru(page*) {
	return nullptr;
}

page* remove_set_pages_lru(page*, int) {
	return nullptr;
}

page* remove_page_lru(page*) {
	return nullptr;
}

int* remove_best_page_lru(void) {
	return nullptr;
}

int get_number_mapped_pages_lru(void) {
	return 0;
}
