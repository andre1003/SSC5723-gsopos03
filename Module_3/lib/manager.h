#ifndef MANAGER_H
#define MANAGER_H


#pragma region Defines
#define TRUE 1
#define FALSE 0
#define VIRTUAL_PAGE_SIZE 4
#define VIRTUAL_MEMORY_SIZE (VIRTUAL_PAGE_SIZE * 2000)
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
#define RAM_SIZE (FRAME_SIZE * 6)
#define PAGES_NUMBER (VIRTUAL_MEMORY_SIZE / VIRTUAL_PAGE_SIZE)
#define FRAMES_NUMBER (RAM_SIZE / FRAME_SIZE)
#define PAGES_NUMBER_LEN bits_len_decimal(PAGES_NUMBER)
#define FRAMES_NUMBER_LEN bits_len_decimal(FRAMES_NUMBER)
#pragma endregion

#pragma region Structs
typedef struct PAGE {
	// Indica se a página está referenciada ou não
	int referenced;

	// Indica se a página foi modificada ou não
	int modifed;

	// Indica se a página possui uma moldura
	int present;

	// Quadro de página
	int* frame_number;
} page;


typedef struct PAGE_TABLE {
	// Page vector
	page* pages;
} page_table;
#pragma endregion


#pragma region Functions
/// <summary>
/// Initialize all the global configuration.
/// </summary>
/// <param name="">None</param>
void init(void);

/// <summary>
/// Get the bits length of a given param.
/// </summary>
/// <param name=""></param>
/// <returns>Bit length</returns>
int bits_len_decimal(int);

#pragma region Page Management
/// <summary>
/// Remove a set of pages.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* remove_set_pages(page*, int);

/// <summary>
/// Remove a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* remove_page(page*);

/// <summary>
/// Insert a set of pages.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* insert_set_pages(page*, int);

/// <summary>
/// Insert a page.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* insert_page(page*);

/// <summary>
/// Remove best page, if possible.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* remove_best_page(void);
#pragma endregion

/// <summary>
/// Get the number of pages in the global list.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_mapped_pages_number(void);

/// <summary>
/// Print the current situation.
/// </summary>
/// <param name=""></param>
void print_situation(void);

#pragma region Counters
/// <summary>
/// Get the global instruction counter.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_global_ic(void);

/// <summary>
/// Increase the global instruction counter.
/// </summary>
/// <param name=""></param>
void increase_ic(void);

/// <summary>
/// Get the number of used frames.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_used_frames_number(void);

/// <summary>
/// Get number of free frames.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_free_frames_number(void);

/// <summary>
/// Get first free frame bit vector.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* get_first_free_frame(void);

/// <summary>
/// Initialize frames.
/// </summary>
/// <param name=""></param>
void init_frames(void);

/// <summary>
/// Change the informed status frame to the given value.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
int* mark_frame(int*, int);

/// <summary>
/// Get the first virtual page activated in memory
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* get_first_present_page(page_table*);

/// <summary>
/// Creates and assing a new page table.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page_table* create_page_table(void);

/// <summary>
/// Free a page table of a process.
/// </summary>
/// <param name=""></param>
void free_page_table(page_table*);
#pragma endregion

#pragma endregion
#endif // !MANAGER_H
