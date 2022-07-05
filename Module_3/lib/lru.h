#ifndef LRU_H
#define LRU_H

#pragma region Include
#include "manager.h"
#pragma endregion




#pragma region Structs
// LRU node struct
typedef struct LRU_NODE {
	page* page;
	struct LRU_NODE* next;
} lru_node;

// LRU list struct
typedef struct LRU_LIST {
	lru_node* start;
} lru_list;
#pragma endregion


#pragma region Functions
/// <summary>
/// Initialize LRU.
/// </summary>
void init_lru(void);

/// <summary>
/// Insert a page vector in the active global page list in LRU algorithm.
/// </summary>
page* insert_set_pages_lru(page*, int);

/// <summary>
/// Insert a page in LRU algorithm.
/// </summary>
page* insert_page_lru(page*);

/// <summary>
/// Insert a LRU node in LRU algorithm.
/// </summary>
int insert_node_lru(lru_node*);

/// <summary>
/// Remove a page vector in the active global page list in LRU algorithm.
/// </summary>
page* remove_set_pages_lru(page*, int);

/// <summary>
/// Remove a page in LRU algorithm.
/// </summary>
page* remove_page_lru(page*);

/// <summary>
/// Select the best page of LRU to bem swapped in LRU algorithm.
/// </summary>
int* remove_best_page_lru(void);

/// <summary>
/// Get the number of pages at this moment in LRU algorithm.
/// </summary>
int get_number_mapped_pages_lru(void);

/// <summary>
/// Find a LRU node.
/// </summary>
lru_node* find_node_lru(page*, lru_node**);
#pragma endregion

#endif // !LRU_H
