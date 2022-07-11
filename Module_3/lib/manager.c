#pragma region Includes
#include "clock.h"
#include "config.h"
#include "lru.h"
#include "manager.h"
#include "math.h"
#include "process.h"
#include "request.h"
#include "stdio.h"
#include "stdlib.h"
#pragma endregion




#pragma region Variables
// Global instruction counter
// Used when the LRU algorithm is enabled
int global_ic = 0;
// Array to mark whether each page frame is linked to some virtual page
// Constant size and represented by FRAMES_NUMBER
int *frames_status = NULL;
#pragma endregion

#pragma region Functions
#pragma region Initialize
void init() {
	// Check the current method
	switch(CURRENT_METHOD) {
		case LRU:
			init_lru(); // LRU algorithm init
			break;
		case CLOCK: // Clock algorithm init
			init_clock();
			break;
	}
}
#pragma endregion

#pragma region Page Management
page* remove_set_pages(page* pag_set, int size) {
	// Check the current method
	// The pointer to the given page set is returned, if all goes well
	switch(CURRENT_METHOD) {
		case LRU: // Remove set pages in the LRU
			return remove_set_pages_lru(pag_set, size);
			break;
		case CLOCK: // Remove set pages in the Clock
			return remove_set_pages_clock(pag_set, size);
			break;
	}
}

page* remove_page(page* pg) {
	// Check the current method
	// If removed, the pointer to the given page is returned
	switch(CURRENT_METHOD) {
		case LRU: // Remove page in the LRU
			return remove_page_lru(pg);
			break;
		case CLOCK: // Remove page in the Clock
			return remove_page_clock(pg);
			break;
	}
}

page* insert_set_pages(page* pag_set, int size) {
	// Check the current method
	// The pointer to the given page set is returned, if all goes well
	switch(CURRENT_METHOD) {
		case LRU: // Insert set pages in the LRU
			return insert_set_pages_lru(pag_set, size);
			break;
		case CLOCK: // Insert set pages in the Clock
			return insert_set_pages_clock(pag_set, size);
			break;
	}
}

page* insert_page(page* pg) {
	// Check the current method
	// If inserted, the pointer to the given page is returned
	switch(CURRENT_METHOD) {
		case LRU: // Insert page in the LRU
			return insert_page_lru(pg);
		case CLOCK: // Insert page in the Clock
			return insert_page_clock(pg);
	}
}

int* remove_best_page() {
	// Check the current method
	// The vector of bits representing the page frame number removed is returned,
	// if all goes well
	switch(CURRENT_METHOD) {
		case LRU: // Remove best page in the LRU
			return remove_best_page_lru();
			break;
		case CLOCK: // Remove best page in the Clock
			return remove_best_page_clock();
			break;
	}
}

int get_mapped_pages_number() {
	// Check the current method
	switch(CURRENT_METHOD) {
		case LRU: // Get number mapped pages in the LRU
			return get_number_mapped_pages_lru();
			break;
		case CLOCK: // Get number mapped pages in the Clock
			return get_number_mapped_pages_clock();
			break;
	}
}
#pragma endregion

#pragma region Output
void print_situation() {
	printf("Number of virtual pages in the global list: %d\n", get_mapped_pages_number());
}

void ram_status() {
	printf("Page frame usage: %d/%d\n", get_used_frames_number(), FRAMES_NUMBER);
}
#pragma endregion

#pragma region MMU Functionalities
int get_global_ic() {
	return global_ic;
}

void increase_ic() {
	global_ic++;
}

int get_used_frames_number(void) {
    int count = 0;
    
	if(frames_status == NULL) {
        init_frames();
        return 0;
    }

    int i = 0;
    for(i = 0; i < FRAMES_NUMBER; i++) {
        count += frames_status[i];
	}
    
	return count;
}

int get_free_frames_number(void) {
	return FRAMES_NUMBER - get_used_frames_number();
}

int* get_first_free_frame(void) {
    if(get_free_frames_number() == 0)
        return NULL;

	int i = 0;
	while(i < FRAMES_NUMBER) {
		if(frames_status[i] == FALSE)
			break;

		i++;
	}

    if (i < FRAMES_NUMBER)
        return get_bits_from_decimal(i, FRAMES_NUMBER_LEN);
	
    return NULL;
}

void init_frames() {
	frames_status = malloc(sizeof(int) * FRAMES_NUMBER);

	int i = 0;
    for(i = 0; i < FRAMES_NUMBER; i++) {
        frames_status[i] = FALSE;
	}
}

int* set_frame(int *frame_number_bits, int status) {
    if(frames_status == NULL)
        init_frames();

    int frame_number = get_decimal_from_bits(frame_number_bits, FRAMES_NUMBER_LEN);
    
	if(frame_number >= 0 && frame_number < FRAMES_NUMBER) {
        frames_status[frame_number] = status;
        return frame_number_bits;
    }

    return NULL;
}

int* get_first_present_page(page_table* table) {
	int i = 0;
    for (i = 0; i < PAGES_NUMBER; i++) {
        if (table->pages[i].present == TRUE)
            return get_bits_from_decimal(i, PAGES_NUMBER_LEN);
    }

    return NULL;
}

page_table* create_page_table() {
    page_table* table = malloc(sizeof(page_table));
    table->pages = malloc(sizeof(page) * PAGES_NUMBER);
	
	int i = 0;
    for(i = 0; i < PAGES_NUMBER; i++) {
        table->pages[i].frame_number = get_bits_from_decimal(0, FRAMES_NUMBER_LEN);
        table->pages[i].modified = FALSE;
        table->pages[i].present = FALSE;
        table->pages[i].referenced = 0;
    }
	
    return table;
}

void free_page_table(page_table* table) {
    printf("Free page table...\n");
    if (table != NULL && table->pages != NULL) {
		int i = 0;
        for(i = 0; i < PAGES_NUMBER; i++) {
            if(table->pages[i].present == TRUE) {
                if(remove_page(&table->pages[i]) == NULL)
                    printf("Could not remove page '%d' (%s) from global page table.\n",
                           i, bits_to_string_decimal(i, PAGES_NUMBER_LEN));
                           
                set_frame(table->pages[i].frame_number, FALSE);
            }
        }

        free(table->pages);
        free(table);
    }
}

page_table* map_page(page_table* table, page* pg) {
    if(pg == NULL)
        return NULL;

    int *frame_number_bits = get_first_free_frame();
    if(frame_number_bits == NULL)
        return NULL;
	
    set_frame(frame_number_bits, TRUE);
    pg->frame_number = frame_number_bits;
    pg->modified = FALSE;
    pg->present = TRUE;
    pg->referenced = 0;
    insert_page(pg);
    return table;
}

page_table* map_pages_set(page_table* table, page* pages_set, int size) {
    if(size > get_free_frames_number())
        return NULL;

	int i = 0;
    for (i = 0; i < size; i++) {
        if(map_page(table, &pages_set[i]) == NULL)
            return NULL;
    }
    return table;
}

void unmap_whole_page_table(page_table* table) {
	int i = 0;
    for(i = 0; i < PAGES_NUMBER; i++) {
        table->pages[i].present = FALSE;
    }
}

address* get_physical_address(address* virtual_address, page_table* table, char op, int** page_number_bits) {
    address* physical_address = NULL;
    *page_number_bits = malloc(sizeof(int) * PAGES_NUMBER_LEN);

	int i = 0;
    for (i = 0; i < PAGES_NUMBER_LEN; i++) {
        (*page_number_bits)[i] = virtual_address->bits[i];
    }

    int page_number = get_decimal_from_bits((*page_number_bits), PAGES_NUMBER_LEN);
    if (page_number >= 0 && page_number < PAGES_NUMBER) {
        if (table->pages[page_number].present == TRUE) {
            int *physical_bits = malloc(sizeof(int) * PHYSICAL_ADDRESS_SIZE);
            
			// Copy the page frame number
            for (int i = 0; i < FRAMES_NUMBER_LEN; i++) {
                physical_bits[i] = table->pages[page_number].frame_number[i];
            }
            
			// Copy the offset value.
            int mov = PAGES_NUMBER_LEN;
            for (int i = FRAMES_NUMBER_LEN; i < PHYSICAL_ADDRESS_SIZE; i++) {
                physical_bits[i] = virtual_address->bits[mov++];
            }

            physical_address = init_address_bits(physical_bits, PHYSICAL_ADDRESS_SIZE);

            // Always set as referenced
            // Check the current method
			switch (CURRENT_METHOD) {
            case LRU:
                table->pages[page_number].referenced = get_global_ic();
                break;
            case CLOCK:
                table->pages[page_number].referenced = 1;
                break;
            }

            if (op == WRITE)
                table->pages[page_number].modified = TRUE;
        }
        else
            printf("Page fault! Virtual address '%llu' (%s). Page Number: '%d'.\n",
                   virtual_address->decimal, bits_to_string_address(virtual_address), page_number);
    }
    else {
        printf("Virtual address '%llu' (%s) does not belong to the virtual address space.\n",
               virtual_address->decimal, bits_to_string_address(virtual_address));
        (*page_number_bits) = NULL;
    }

    return physical_address;
}

int count_mapped_pages(page_table* table) {
    int count = 0;
	int i = 0;

    for(i = 0; i < PAGES_NUMBER; i++) {
        count += table->pages[i].present;
    }

    return count;
}

int* page_number_from_page(page* pg) {
    process* proc = find_process_from_page(pg);

    if (proc == NULL)
        return NULL;

	int i = 0;
	while(i < PAGES_NUMBER) {
		if (&proc->table->pages[i] == pg)
            break;

		i++;
	}

    return get_bits_from_decimal(i, PAGES_NUMBER_LEN);
}
#pragma endregion

#pragma region Address
#pragma region Decimal Functions
int* get_bits_from_decimal(unsigned long long decimal, int bits_size) {
    int *bits = malloc(sizeof(int) * bits_size);
    unsigned long long mask = 1ULL << (bits_size - 1);

	int i = 0;
    for(i = 0; i < bits_size; i++) {
        bits[i] = (decimal & mask) ? 1 : 0;
        decimal <<= 1;
    }
	
    return bits;
}

address* init_address_decimal(unsigned long long decimal, int bits_size) {
    address* addr = malloc(sizeof(address));
    addr->decimal = decimal;
    addr->size = bits_size;
    addr->bits = get_bits_from_decimal(decimal, bits_size);
    return addr;
}
#pragma endregion

#pragma region Bit Functions
unsigned long long get_decimal_from_bits(int *bits, int size) {
    unsigned long long decimal = 0;
    int expo = size - 1;

    for (int i = 0; i < size; i++) {
        decimal += bits[i] * pow(2, expo--);
    }

    return decimal;
}

address* init_address_bits(int* bits, int size) {
    address* addr = malloc(sizeof(address));
    addr->size = size;
    addr->bits = bits;
    addr->decimal = get_decimal_from_bits(bits, size);
    return addr;
}
#pragma endregion

#pragma region Strings
char* bits_to_string_address(address* addr) {
	return bits_to_string_bits(addr->bits, addr->size);
}

char* bits_to_string_bits(int* bits, int size) {
    char *formated = malloc(sizeof(char) * size + 1);
    int i = 0;

	for(i = 0; i < size; i++) {
        formated[i] = bits[i] == 1 ? '1' : '0';
    }

    formated[size] = '\0';
    return formated;
}

char* bits_to_string_decimal(int decimal, int size) {
    return bits_to_string_bits(get_bits_from_decimal(decimal, size), size);
}
#pragma endregion
#pragma endregion
#pragma endregion