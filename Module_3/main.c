#pragma region Includes
#include "lib/manager.h"
#include "lib/input.h"
#include "stdio.h"
#include "stdlib.h"
#pragma endregion




void print_config() {
    printf("\n--------------------------------------------\n");
    printf("Características do simulador.\n");
    printf("Método de substituição de páginas atual: %s\n", CURRENT_METHOD == CLOCK ? "Relógio" : "LRU");
    printf("Tamanho da página virtual e quadros de página: %d\n", VIRTUAL_PAGE_SIZE);
    printf("Tamanho max. da RAM (tamanho / N° quadros): %d/%d\n", RAM_SIZE, FRAMES_NUMBER);
    printf("Tamanho max. da memória virtual (tamanho / N° páginas): %d/%d\n", VIRTUAL_MEMORY_SIZE, PAGES_NUMBER);
    printf("Tamanho max. da SWAP: %d\n", SECONDARY_MEMORY_MAX_SIZE);
    printf("Tamanho do endereço virtual: %d\n", VIRTUAL_ADDRESS_SIZE);
    printf("Tamanho do endereço físico: %d\n", PHYSICAL_ADDRESS_SIZE);
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