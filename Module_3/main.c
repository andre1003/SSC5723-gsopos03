#pragma region Includes
#include "lib/manager.h"
#include "lib/input.h"
#include "stdio.h"
#include "stdlib.h"
#pragma endregion




void print_config() {
    printf("\n--------------------------------------------\n");
    printf("Caracter�sticas do simulador.\n");
    printf("M�todo de substitui��o de p�ginas atual: %s\n", CURRENT_METHOD == CLOCK ? "Rel�gio" : "LRU");
    printf("Tamanho da p�gina virtual e quadros de p�gina: %d\n", VIRTUAL_PAGE_SIZE);
    printf("Tamanho max. da RAM (tamanho / N� quadros): %d/%d\n", RAM_SIZE, FRAMES_NUMBER);
    printf("Tamanho max. da mem�ria virtual (tamanho / N� p�ginas): %d/%d\n", VIRTUAL_MEMORY_SIZE, PAGES_NUMBER);
    printf("Tamanho max. da SWAP: %d\n", SECONDARY_MEMORY_MAX_SIZE);
    printf("Tamanho do endere�o virtual: %d\n", VIRTUAL_ADDRESS_SIZE);
    printf("Tamanho do endere�o f�sico: %d\n", PHYSICAL_ADDRESS_SIZE);
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