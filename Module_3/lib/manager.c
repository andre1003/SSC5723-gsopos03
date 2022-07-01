#pragma region Includes
#include "clock.h"
#include "lru.h"
#include "manager.h"
#include "stdio.h"
#pragma endregion




void init() {
	switch(CURRENT_METHOD) {
		case LRU:
			// LRU init
			init_lru();
			break;

		case CLOCK:
			// clock init
			init_clock();
			break;
	}
}

page* remove_set_pages(page*, int) {
	return nullptr;
}

page* remove_page(page*) {
	return nullptr;
}

page* insert_set_pages(page*, int) {
	return nullptr;
}

page* insert_page(page*) {
	return nullptr;
}

int* remove_best_page(void) {
	return nullptr;
}

int get_mapped_pages_number(void) {
	return 0;
}

void print_situation(void) {
}

void ram_status(void) {
}

int get_global_ic(void) {
	return 0;
}

void increase_ic(void) {
}

int get_used_frames_number(void) {
	return 0;
}

int get_free_frames_number(void) {
	return 0;
}

int* get_first_free_frame(void) {
	return nullptr;
}

void init_frames(void) {
}

int* set_frame(int*, int) {
	return nullptr;
}

int* get_first_present_page(page_table*) {
	return nullptr;
}

page_table* create_page_table(void) {
	return nullptr;
}

void free_page_table(page_table*) {
}

page_table* map_page(page_table*, page*) {
	return nullptr;
}

page_table* map_pages_set(page_table*, page*, int) {
	return nullptr;
}

void unmap_whole_page_table(page_table*) {
}

address* get_physical_address(page_table*) {
	return nullptr;
}

int count_mapped_pages(page_table*) {
	return 0;
}

int* page_number_from_page(page*) {
	return nullptr;
}

address* init_address_decimal(unsigned long long, int) {
	return nullptr;
}

int* get_bits_from_decimal(unsigned long long, int) {
	return nullptr;
}

address* init_address_bits(int*, int) {
	return nullptr;
}

unsigned long long get_decimal_from_bits(int*, int) {
	return 0;
}

char* bits_to_string_address(address*) {
	return nullptr;
}

char* bits_to_string_bits(int*, int) {
	return nullptr;
}

char* bits_to_string_decimal(int, int) {
	return nullptr;
}
