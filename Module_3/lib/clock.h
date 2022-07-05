#ifndef CLOCK_H
#define CLOCK_H

#pragma region Include
#include "manager.h"
#pragma endregion




#pragma region Structs
// Clock node struct
typedef struct CLOCK_NODE {
	page* page;
	struct CLOCK_NODE* next;
} clock_node;

// Clock list struct
typedef struct CLOCK_LIST {
	clock_node* end;
} clock_list;
#pragma endregion


#pragma region Functions
/// <summary>
/// Initialize clock.
/// </summary>
void init_clock(void);

/// <summary>
/// Insert a page vector in the active global page list in clock algorithm.
/// </summary>
page* insert_set_pages_clock(page*, int);

/// <summary>
/// Insert a page in clock algorithm.
/// </summary>
page* insert_page_clock(page*);

/// <summary>
/// Remove a page vector in the active global page list in clock algorithm.
/// </summary>
page* remove_set_pages_clock(page*, int);

/// <summary>
/// Remove a page in clock algorithm.
/// </summary>
page* remove_page_clock(page*);

/// <summary>
/// Select the best page of clock to be swapped in clock algorithm.
/// </summary>
int* remove_best_page_clock(void);

/// <summary>
/// Get the number of pages at this moment in clock algorithm.
/// </summary>
int get_number_mapped_pages_clock(void);

/// <summary>
/// Check if list is empty.
/// </summary>
int list_empty(void);

/// <summary>
/// Find a clock node.
/// </summary>
clock_node* find_node_clock(page*, clock_node**);
#pragma endregion

#endif // !CLOCK_H
