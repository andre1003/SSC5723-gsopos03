#pragma region Includes
#include "config.h"
#include "math.h"
#include "manager.h"
#include "stdio.h"
#pragma endregion

#pragma region Functions
int bits_len_decimal(int size) {
	// Bits required to represent a decimal value
	return ((floor(log(size) / log(2)) + 1));
}

int bits_len(int size) {
	// Bits required to represent an amount of memory in kB
	return ((floor(log(size * 1024) / log(2)) + 1));
}

int allocation_policy(int image) {
    // Calculate the number of frames and maximum frames
	// Processes can dynamically increase or decrease the amount of RAM
	int frames = floor((image / VIRTUAL_PAGE_SIZE) * ALLOCATION_PERCENT);
	int max_frames = floor(0.50 * NUMBER_OF_FRAMES);

	// Guarantee that at least 1 frame is reserved for the process
	if (frames == 0) 
        frames = 1;
	
	// Ensure a maximum of 50% of RAM is allocated to a single process at one time
    if (frames > max_frames)
        frames = max_frames;
    
    return frames;
}
#pragma endregion
