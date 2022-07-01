#ifndef PROCESS_H
#define PROCESS_H

#include "swap.h"
#include "manager.h"

#define IN_DISC FALSE
#define IN_RAM TRUE

typedef struct PROCESS {
	char* id;
	int image_size;
	int status;
	process_swap_area* swap_area;
	page_table* table;
} process;


#pragma region Functions
/// <summary>
/// Create a process.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* create_process(void);

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
int send_page_to_disc(page*);

/// <summary>
/// Find a process from a given page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
process* find_process_from_page(page*);
#pragma endregion
#endif // !PROCESS_H
