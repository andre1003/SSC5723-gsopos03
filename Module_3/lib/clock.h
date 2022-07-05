#ifndef CLOCK_H
#define CLOCK_H

#include "manager.h"



#pragma region Structs
typedef struct CLOCK_NODE {
	page* page;
	struct CLOCK_NODE* next;
} clock_node;

typedef struct CLOCK_LIST {
	clock_node* end;
} clock_list;
#pragma endregion


#pragma region Functions
/// <summary>
/// Initialize clock.
/// </summary>
/// <param name=""></param>
void init_clock(void);

/// <summary>
/// Insert a page vector in the active global page list.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* insert_set_pages_clock(page*, int);

/// <summary>
/// Insert a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* insert_page_clock(page*);

/// <summary>
/// Remove a page vector in the active global page list.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* remove_set_pages_clock(page*, int);

/// <summary>
/// Remove a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* remove_page_clock(page*);

/// <summary>
/// Select the best page of clock to bem swapped.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* remove_best_page_clock(void);

/// <summary>
/// Get the number of pages at this moment.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_number_mapped_pages_clock(void);

/// <summary>
/// Check if list is empty.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int list_empty(void);

/// <summary>
/// Find a clock node.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
clock_node* find_node_clock(page*, clock_node**);
#pragma endregion

#endif // !CLOCK_H
