#include "swap.h"

int get_used_swap(void) {
	return 0;
}

process_swap_area* create_swap_area(int) {
	return nullptr;
}

void free_swap_area(process_swap_area*, int) {
}

int* get_page_in_disc(process_swap_area*, int*) {
	return nullptr;
}

page* send_page_to_disc(process_swap_area*, page*, int*) {
	return nullptr;
}

page_table* send_page_table_to_disc(process_swap_area*, page_table*) {
	return nullptr;
}

int** get_pages_set_in_disc(process_swap_area*, int**, int) {
	return nullptr;
}

void print_swap_situation(void) {
}
