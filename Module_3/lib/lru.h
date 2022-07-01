#ifndef LRU_H
#define LRU_H

#include "manager.h"




#pragma region Functions
/// <summary>
/// Initialize LRU.
/// </summary>
/// <param name=""></param>
void init_lru(void);

/// <summary>
/// Update global page list.
/// </summary>
/// <param name=""></param>
void update_global_list_lru(void);

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
#pragma endregion

#endif // !LRU_H
