#ifndef PROCESS_H
#define PROCESS_H

#include "swap.h"
#include "manager.h"

#define IN_DISC FALSE
#define IN_RAM TRUE



#pragma region Structs
typedef struct PROCESS {
	char* id;
	int image_size;
	int status;
	process_swap_area* swap_area;
	page_table* table;
} process;

typedef struct PROCESS_NODE {
	process* proc;
	struct PROCESS_NODE* next;
} process_node;

typedef struct PROCESS_LIST {
	process_node* start;
} process_list;
#pragma endregion

#pragma region Functions
/// <summary>
/// Initialize process list.
/// </summary>
/// <param name=""></param>
void init_process_list(void);

/// <summary>
/// Find last process.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process_node* find_last(void);

/// <summary>
/// Create a process.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* create_process(void);

/// <summary>
/// Find last process.
/// </summary>
/// <returns></returns>
process_node* find_last(void);

/// <summary>
/// Remove a process from process table.
/// </summary>
/// <param name=""></param>
void remove_process(process*);

/// <summary>
/// Find a process from char.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* find_process(char*);

/// <summary>
/// Choose a process to sleep.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* choose_process_to_sleep(void);

/// <summary>
/// Put a given process to sleep.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* sleep(process*);

/// <summary>
/// Wake up a process.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* wakeup(process*);

/// <summary>
/// Reset a process.
/// </summary>
/// <param name=""></param>
void reset_process(process*);

/// <summary>
/// Force a process to sleep.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int force_sleep(int);

/// <summary>
/// Print current process situation.
/// </summary>
/// <param name=""></param>
void print_process_situation(void);

/// <summary>
/// Send a page to disc.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int send_page_to_disc_page_only(page*);

/// <summary>
/// Find a process from a given page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* find_process_from_page(page*);
#pragma endregion
#endif // !PROCESS_H
