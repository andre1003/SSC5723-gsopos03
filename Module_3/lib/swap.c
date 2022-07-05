#pragma region Includes
#include "swap.h"
#include "stdlib.h"
#include "stdio.h"
#pragma endregion




int current_used_swap = 0;

#pragma region Get Used Swap
int get_used_swap(void) {
    return current_used_swap;
}
#pragma endregion

#pragma region Create
process_swap_area* create_swap_area(int image_size) {
    // Variable declaration
    process_swap_area* swap_area = NULL;
    int new_used_swap = current_used_swap + image_size;

    // If there is secondary memory size for SWAP
    if(new_used_swap <= SECONDARY_MEMORY_MAX_SIZE) {
        // Variable declaration
        current_used_swap = new_used_swap;
        swap_area = malloc(sizeof(process_swap_area));

        // SWAP area first address error
        swap_area->first_address = init_address_decimal(0, VIRTUAL_ADDRESS_SIZE);
        if(image_size > VIRTUAL_MEMORY_SIZE) {
            printf("The process cannot be allocated in the SWAP area! Process size larger than allowed for addressing.\n");
            swap_area = NULL;
            current_used_swap -= image_size;
        }
        // Set SWAP area first address
        else {
            swap_area->last_address = init_address_decimal(image_size * 1024 - 1, VIRTUAL_ADDRESS_SIZE);
        }
    }
    // Else, don't allow process allocation
    else {
        printf("The process cannot be allocated in the swap area! Not enough space in the SWAP area.\n");
        current_used_swap -= image_size;
    }

    // Return SWAP area
    return swap_area;
}
#pragma endregion

#pragma region Free
void free_swap_area(process_swap_area* swap_area, int size) {
    printf("Free SWAP area in disk..\n");

    // If there is a SWAP area, free it
    if(swap_area != NULL) {
        current_used_swap -= size;
        free(swap_area->first_address);
        free(swap_area->last_address);
        free(swap_area);
    }
}
#pragma endregion

#pragma region Get from Disk
int* get_page_in_disk(process_swap_area* swap_area, int* page_number_bits) {
    // Page fetch error
    if(page_number_bits == NULL) {
        printf("Page cannot be fetched from disk because value 'NULL' is invalid.\n");
        return NULL;
    }

    // Page fetch
    int page_number = get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN);
    if(page_number >= 0 && page_number <= ((swap_area->last_address->decimal + 1) / 1024) - 1) {
        printf("Page '%d' (%s) fetched in disk.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return page_number_bits;
    }
    // Image error
    else {
        printf("Page '%d' (%s) could not be fetched in disk. Address out of scope of process image.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return NULL;
    }
}

int** get_pages_set_in_disk(process_swap_area* swap_area, int** pages_set, int size) {
    printf("Fetching pages set in disk...\n");

    // If there is a pages set, get it from disk
    if(pages_set != NULL) {
        for(int i = 0; i < size; i++) {
            if(get_page_in_disk(swap_area, pages_set[i]) == NULL) {
                return NULL;
            }
        }

        return pages_set;
    }

    // Allocat the pages set and get the bits vector
    pages_set = malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++) {
        pages_set[i] = get_bits_from_decimal(i, PAGES_NUMBER_LEN);
        if(get_page_in_disk(swap_area, pages_set[i]) == NULL) {
            return NULL;
        }
    }

    // Return pages set, if possible
    return pages_set;
}
#pragma endregion

#pragma region Send to Disk
page* send_page_to_disk(process_swap_area* swap_area, page* virtual_page, int* page_number_bits) {
    // Page sent to disk successfully
    int page_number = get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN);
    if(page_number >= 0 && page_number <= ((swap_area->last_address->decimal + 1) / 1024) - 1) {
        printf("Page '%d' (%s) sent to disk.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        virtual_page->modified = FALSE;
        return virtual_page;
    }
    // Page could not be sent to disk
    else {
        printf("Page '%d' (%s) could not be sent to disk! Address out of scope of process image.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return NULL;
    }
}

page_table* send_page_table_to_disk(process_swap_area* swap_area, page_table* pages_table) {
    printf("Sending all process modified pages to disk...\n");

    // Try to send all pages from page table to disk
    for(int i = 0; i < PAGES_NUMBER; i++) {
        if(pages_table->pages[i].present == TRUE && pages_table->pages[i].modified == TRUE) {
            if(send_page_to_disk(swap_area, &pages_table->pages[i], get_bits_from_decimal(i, PAGES_NUMBER_LEN)) == NULL) {
                return NULL;
            }
        }
    }

    // Return the page table if possible
    return pages_table;
}
#pragma endregion

#pragma region Print
void print_swap_situation(void) {
    printf("Used SWAP: %d/%d\n", get_used_swap(), SECONDARY_MEMORY_MAX_SIZE);
}
#pragma endregion
