#ifndef LRU_H
#define LRU_H

#include "manager.h"




#pragma region Structs
typedef struct LRU_NODE {
	page* page;
	struct LRU_NODE* next;
} lru_node;

typedef struct LRU_LIST {
	lru_node* start;
} lru_list;
#pragma endregion


#pragma region Functions
/// <summary>
/// Initialize LRU.
/// </summary>
/// <param name=""></param>
void init_lru(void);

/// <summary>
/// Insert a page vector in the active global page list.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* insert_set_pages_lru(page*, int);

/// <summary>
/// Insert a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* insert_page_lru(page*);

/// <summary>
/// Insert a LRU node.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int insert_node_lru(lru_node*);

/// <summary>
/// Remove a page vector in the active global page list.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* remove_set_pages_lru(page*, int);

/// <summary>
/// Remove a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* remove_page_lru(page*);

/// <summary>
/// Select the best page of LRU to bem swapped.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* remove_best_page_lru(void);

/// <summary>
/// Get the number of pages at this moment.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_number_mapped_pages_lru(void);

/// <summary>
/// Find a LRU node.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
lru_node* find_node_lru(page*, lru_node**);
#pragma endregion

#endif // !LRU_H
