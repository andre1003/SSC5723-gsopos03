#ifndef MANAGER_H
#define MANAGER_H

#include "config.h"

#pragma region Defines
#define TRUE 1
#define FALSE 0
#define PAGES_NUMBER (VIRTUAL_MEMORY_SIZE / VIRTUAL_PAGE_SIZE)
#define FRAMES_NUMBER (RAM_SIZE / FRAME_SIZE)
#define PAGES_NUMBER_LEN bits_len_decimal(PAGES_NUMBER)
#define FRAMES_NUMBER_LEN bits_len_decimal(FRAMES_NUMBER)
#pragma endregion

#pragma region Structs
typedef struct PAGE {
	// Indicates whether the page is referenced or not
	int referenced;

	// Indicates whether the page has been modified or not
	int modified;

	// Indicates whether the page has a frame
	int present;

	// Page frame number
	int* frame_number;

	// Next list element reference
	struct PAGE* next;
} page;

typedef struct PAGE_TABLE {
	// Page vector
	page* pages;
} page_table;

typedef struct ADDRESS {
	// Bit vector
	int* bits;

	// Number of bits in the bits vector
	int size;

	// Decimal version of bits vector
	unsigned long long decimal;
} address;
#pragma endregion

#pragma region Functions
#pragma region Initialize
/// <summary>
/// Initialize the global list of active pages.
/// </summary>
/// <param name="">None</param>
void init(void);
#pragma endregion

#pragma region Page Management
/// <summary>
/// Remove page set from global list of active pages.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* remove_set_pages(page*, int);

/// <summary>
/// Remove page from the global list of active pages.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* remove_page(page*);

/// <summary>
/// Insert page set from global list of active pages.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page* insert_set_pages(page*, int);

/// <summary>
/// Insert page from the global list of active pages.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
page* insert_page(page*);

/// <summary>
/// Remove the best page based on the running algorithm, if possible.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* remove_best_page(void);

/// <summary>
/// Get the number of pages in the global list.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int get_mapped_pages_number(void);
#pragma endregion

#pragma region Output
/// <summary>
/// Print how many virtual pages are mapped in the global list.
/// </summary>
/// <param name=""></param>
void print_situation(void);

/// <summary>
/// Print number of page frames used.
/// </summary>
/// <param name=""></param>
void ram_status(void);
#pragma endregion

#pragma region MMU Functionalities
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
int* set_frame(int*, int);

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

/// <summary>
/// Map a virtual page to a free frame.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page_table* map_page(page_table*, page*);

/// <summary>
/// Map a virtual page group to a free frame group.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
page_table* map_pages_set(page_table*, page*, int);

/// <summary>
/// Set all pages present variable to FALSE.
/// </summary>
/// <param name=""></param>
void unmap_whole_page_table(page_table*);

/// <summary>
/// Converts a virtual address to physical addres.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
address* get_physical_address(address*, page_table*, char, int **);

/// <summary>
/// Get the number of mapped pages of a given page table.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int count_mapped_pages(page_table*);

/// <summary>
/// Get the page number from the local page table.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int* page_number_from_page(page*);
#pragma endregion

#pragma region Address
#pragma region Decimal Functions
/// <summary>
/// Get bits vector from a given decimal address.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
int* get_bits_from_decimal(unsigned long long, int);

/// <summary>
/// Create and initialize a new address from decimal.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
address* init_address_decimal(unsigned long long, int);
#pragma endregion

#pragma region Bit Functions
/// <summary>
/// Get decimal address from a given bit vector.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
unsigned long long get_decimal_from_bits(int*, int);

/// <summary>
/// Create and initializes a new address from a given bit vector.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
address* init_address_bits(int*, int);
#pragma endregion

#pragma region Strings
/// <summary>
/// Get the bits vector string from a given address.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
char* bits_to_string_address(address*);

/// <summary>
/// Get the bits vector string from a given bits vector.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
char* bits_to_string_bits(int*, int);

/// <summary>
/// Get the bits vector string from a given decimal address.
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
/// <returns></returns>
char* bits_to_string_decimal(int, int);
#pragma endregion
#pragma endregion
#pragma endregion
#endif // !MANAGER_H
