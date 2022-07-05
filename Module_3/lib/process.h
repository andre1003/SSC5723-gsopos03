#ifndef PROCESS_H
#define PROCESS_H

#pragma region Includes
#include "swap.h"
#include "manager.h"
#pragma endregion



#pragma region Defines
#define IN_DISK FALSE
#define IN_RAM TRUE
#pragma endregion

#pragma region Structs
// Process struct
typedef struct PROCESS {
	char* id;
	int image_size;
	int status;
	process_swap_area* swap_area;
	page_table* table;
} process;

// Process node struct
typedef struct PROCESS_NODE {
	process* proc;
	struct PROCESS_NODE* next;
} process_node;

// Process list struct
typedef struct PROCESS_LIST {
	process_node* start;
} process_list;
#pragma endregion

#pragma region Functions
/// <summary>
/// Initialize process list.
/// </summary>
void init_process_list(void);

/// <summary>
/// Find last process.
/// </summary>
process_node* find_last(void);

/// <summary>
/// Create a process.
/// </summary>
process* create_process(void);

/// <summary>
/// Find last process.
/// </summary>
process_node* find_last(void);

/// <summary>
/// Remove a process from process table.
/// </summary>
void remove_process(process*);

/// <summary>
/// Find a process from char.
/// </summary>
process* find_process(char*);

/// <summary>
/// Choose a process to sleep.
/// </summary>
process* choose_process_to_sleep(void);

/// <summary>
/// Put a given process to sleep.
/// </summary>
process* sleep(process*);

/// <summary>
/// Wake up a process.
/// </summary>
process* wakeup(process*);

/// <summary>
/// Reset a process.
/// </summary>
void reset_process(process*);

/// <summary>
/// Force a process to sleep.
/// </summary>
int force_sleep(int);

/// <summary>
/// Print current process situation.
/// </summary>
void print_process_situation(void);

/// <summary>
/// Send a page to disk.
/// </summary>
int send_page_to_disk_page_only(page*);

/// <summary>
/// Find a process from a given page.
/// </summary>
process* find_process_from_page(page*);
#pragma endregion
#endif // !PROCESS_H
