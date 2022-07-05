#pragma region Includes
#include "lib/manager.h"
#include "lib/input.h"
#include "stdio.h"
#include "stdlib.h"
#pragma endregion




void print_config() {
    printf("\n--------------------------------------------\n");
    printf("Simulator features:\n");
    printf("Current page replacement method: %s\n", CURRENT_METHOD == CLOCK ? "Clock" : "LRU");
    printf("Virtual page and frame page size: %d\n", VIRTUAL_PAGE_SIZE);
    printf("Maximum RAM size: %d/%d\n", RAM_SIZE, FRAMES_NUMBER);
    printf("Maximum virtual memory size: %d/%d\n", VIRTUAL_MEMORY_SIZE, PAGES_NUMBER);
    printf("Maximum SWAP size: %d\n", SECONDARY_MEMORY_MAX_SIZE);
    printf("Virtual address size: %d\n", VIRTUAL_ADDRESS_SIZE);
    printf("Physical address size: %d\n", PHYSICAL_ADDRESS_SIZE);
    printf("--------------------------------------------\n");
}

#pragma region Main Code
int main() {
    // Print initial config
    print_config();

	// Initialize the global variables list
    init();

    // Read input file and execute the code
    read_file();

    return 0;
}
#pragma endregion