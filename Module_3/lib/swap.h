#ifndef SWAP_H
#define SWAP_H

#include "config.h"
#include "manager.h"




typedef struct PROCESS_SWAP_AREA {
    
    ADDRESS* first_address;
    
    ADDRESS* last_address;
} process_swap_area;


/// <summary>
/// Get the used swap memory size.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_used_swap(void);

/// <summary>
/// Create the process swap area.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process_swap_area* create_swap_area(int);

/// <summary>
/// Free the process swap area.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
void free_swap_area(process_swap_area*, int);

/// <summary>
/// Get a page in disc.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
int* get_page_in_disc(process_swap_area*, int*);

/// <summary>
/// Send a page to disc.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* send_page_to_disc(process_swap_area*, page*, int*);

/// <summary>
/// Send a page table to disc.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page_table* send_page_table_to_disc(process_swap_area*, page_table*);

/// <summary>
/// Get page set in disc.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
int** get_pages_set_in_disc(process_swap_area*, int**, int);

/// <summary>
/// Print the swap current situation.
/// </summary>
/// <param name=""></param>
void print_swap_situation(void);
#endif // !SWAP_H
