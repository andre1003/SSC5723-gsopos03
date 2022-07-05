#ifndef CONFIG_H
#define CONFIG_H

#pragma region Defines
#pragma region Allocation
// Percentage of process image must be sent to main memory on creation or 'wake up'
#define ALLOCATION_PERCENT 0.15
// Virtual page size in kB
#define VIRTUAL_PAGE_SIZE 4
// Total virtual memory size
#define VIRTUAL_MEMORY_SIZE (VIRTUAL_PAGE_SIZE * 2000)
// Page frame size in kB
#define FRAME_SIZE VIRTUAL_PAGE_SIZE
// Total size of main memory
#define RAM_SIZE (FRAME_SIZE * 6)
// Secondary memory swap area size
#define SECONDARY_MEMORY_MAX_SIZE (FRAME_SIZE * 10000)
// Virtual address size
#define VIRTUAL_ADDRESS_SIZE bits_len(VIRTUAL_MEMORY_SIZE)
// Physical address size
#define PHYSICAL_ADDRESS_SIZE bits_len(RAM_SIZE);
#pragma endregion

#pragma region Method
// LRU page replacement algorithm
#define LRU 0
// Clock page replacement algorithm
#define CLOCK 1
// Page replacement algorithm applied in the simulator
#define CURRENT_METHOD CLOCK
#pragma endregion
#pragma endregion

#pragma region Functions
/// <summary>
/// Get the bits length in decimal.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int bits_len_decimal(int);

/// <summary>
/// Get the bits length in KB.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int bits_len(int);

/// <summary>
/// Returns the number of page frames that should be reserved for the process
/// based on the process image size informed as a parameter.
/// </summary>
/// <param name=""></param>
/// <returns></returns>
int allocation_policy(int);
#pragma endregion
#endif // !CONFIG_H
