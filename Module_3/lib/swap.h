#ifndef SWAP_H
#define SWAP_H

#include "config.h"
#include "manager.h"




#pragma region Struct
// Process SWAP area struct
typedef struct PROCESS_SWAP_AREA {
    address* first_address;
    address* last_address;
} process_swap_area;
#pragma endregion

#pragma region Functions
/// <summary>
/// Get the used swap memory size.
/// </summary>
int get_used_swap(void);

/// <summary>
/// Create the process swap area.
/// </summary>
process_swap_area* create_swap_area(int);

/// <summary>
/// Free the process swap area.
/// </summary>
void free_swap_area(process_swap_area*, int);

/// <summary>
/// Get a page in disk.
/// </summary>
int* get_page_in_disk(process_swap_area*, int*);

/// <summary>
/// Send a page to disk.
/// </summary>
page* send_page_to_disk(process_swap_area*, page*, int*);

/// <summary>
/// Send a page table to disk.
/// </summary>
page_table* send_page_table_to_disk(process_swap_area*, page_table*);

/// <summary>
/// Get page set in disk.
/// </summary>
int** get_pages_set_in_disk(process_swap_area*, int**, int);

/// <summary>
/// Print the swap current situation.
/// </summary>
void print_swap_situation(void);
#pragma endregion
#endif // !SWAP_H
