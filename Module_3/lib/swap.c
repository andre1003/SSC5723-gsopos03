#include "swap.h"
#include "stdlib.h"
#include "stdio.h"




int current_used_swap = 0;

#pragma region Get Used Swap
int get_used_swap(void) {
    return current_used_swap;
}
#pragma endregion

#pragma region Create
process_swap_area* create_swap_area(int image_size) {
    process_swap_area* swap_area = NULL;
    int new_used_swap = current_used_swap + image_size;

    if(new_used_swap <= SECONDARY_MEMORY_MAX_SIZE) {
        current_used_swap = new_used_swap;
        swap_area = malloc(sizeof(process_swap_area));

        swap_area->first_address = get_bits_from_decimal(0, VIRTUAL_ADDRESS_SIZE);
        if(image_size > VIRTUAL_MEMORY_SIZE) {
            printf("O processo não pode ser alocado na área de troca! Tamanho do processo maior do que o permitido para endereçamento.\n");
            swap_area = NULL;
            current_used_swap -= image_size;
        }
        else {
            swap_area->last_address = get_bits_from_decimal(image_size * 1024 - 1, VIRTUAL_ADDRESS_SIZE);
        }
    }
    else {
        printf("O processo não pode ser alocado na área de troca! Sem espaço suficiente na área de troca.\n");
        current_used_swap -= image_size;
    }

    return swap_area;
}
#pragma endregion

#pragma region Free
void free_swap_area(process_swap_area* swap_area, int size) {
    printf("Liberando área de troca em disco...\n");

    if(swap_area != NULL) {
        current_used_swap -= size;
        free(swap_area->first_address);
        free(swap_area->last_address);
        free(swap_area);
    }
}
#pragma endregion

#pragma region Get from Disc
int* get_page_in_disc(process_swap_area* swap_area, int* page_number_bits) {
    if(page_number_bits == NULL) {
        printf("A página não pode ser buscada no disco, pois o valor 'NULL' é inválido.\n");
        return NULL;
    }

    int page_number = get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN);

    if(page_number >= 0 && page_number <= ((swap_area->last_address->decimal + 1) / 1024) - 1) {
        printf("Página '%d' (%s) foi buscada no disco.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return page_number_bits;
    }
    else {
        printf("A página '%d' (%s) não pode ser buscada no disco! Endereço fora do escopo da imagem do processo.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return NULL;
    }
}

int** get_pages_set_in_disc(process_swap_area* swap_area, int** pages_set, int size) {
    printf("Buscando conjunto de páginas no disco...\n");

    if(pages_set != NULL) {
        for(int i = 0; i < size; i++) {
            if(get_page_in_disc(swap_area, pages_set[i]) == NULL) {
                return NULL;
            }
        }
        return pages_set;
    }

    pages_set = malloc(sizeof(int*) * size);
    for(int i = 0; i < size; i++) {
        pages_set[i] = get_bits_from_decimal(i, PAGES_NUMBER_LEN);
        if(get_page_in_disc(swap_area, pages_set[i]) == NULL) {
            return NULL;
        }
    }

    return pages_set;
}
#pragma endregion

#pragma region Send to Disc
page* send_page_to_disc(process_swap_area* swap_area, page* virtual_page, int* page_number_bits) {
    int page_number = get_decimal_from_bits(page_number_bits, PAGES_NUMBER_LEN);

    if(page_number >= 0 && page_number <= ((swap_area->last_address->decimal + 1) / 1024) - 1) {
        printf("A página '%d' (%s) foi enviada para o disco.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        virtual_page->modifed = FALSE;
        return virtual_page;
    }
    else {
        printf("A página '%d' (%s) não pode ser enviada para o disco! Endereço fora do escopo da imagem do processo.\n",
            page_number,
            bits_to_string_bits(page_number_bits, PAGES_NUMBER_LEN));
        return NULL;
    }
}

page_table* send_page_table_to_disc(process_swap_area* swap_area, page_table* pages_table) {
    printf("Enviando todas as págins modificadas do processo para o disco...\n");

    for(int i = 0; i < PAGES_NUMBER; i++) {
        if(pages_table->pages[i].present == TRUE && pages_table->pages[i].modifed == TRUE) {
            if(send_page_to_disc(swap_area, &pages_table->pages[i], get_bits_from_decimal(i, PAGES_NUMBER_LEN)) == NULL) {
                return NULL;
            }
        }
    }

    return pages_table;
}
#pragma endregion

#pragma region Print
void print_swap_situation(void) {
    printf("Quantidade de memória usada na SWAP: %d/%d\n", get_used_swap(), SECONDARY_MEMORY_MAX_SIZE);
}
#pragma endregion
