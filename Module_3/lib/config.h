#ifndef CONFIG_H
#define CONFIG_H

#pragma region Defines
#pragma region Allocation
#define ALLOCATION_PERCENT 0.15
#define VIRTUAL_PAGE_SIZE 4
#define VIRTUAL_MEMORY_SIZE (VIRTUAL_PAGE_SIZE * 2000)
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
#define RAM_SIZE (FRAME_SIZE * 6)
#define SECONDARY_MEMORY_MAX_SIZE (FRAME_SIZE * 10000)
#define VIRTUAL_ADDRESS_SIZE bits_len(VIRTUAL_MEMORY_SIZE)
#define PHYSICAL_ADDRESS_SIZE bits_len(RAM_SIZE);
#pragma endregion

#pragma region Method
#define LRU 0
#define CLOCK 1
#define CURRENT_METHOD CLOCK
#pragma endregion
#pragma endregion

#pragma region Functions
/// <summary>
/// Get the bits length in decimal.
/// </summary>
/// <param name=""></param>
/// <returns>Bit length</returns>
int bits_len_decimal(int);

/// <summary>
/// Get the bits length in KB.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int bits_len(int);
#pragma endregion
#endif // !CONFIG_H
