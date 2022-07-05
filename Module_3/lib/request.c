#include "request.h"
#include "stdio.h"
#include "stdlib.h"
#include "manager.h"
#include "process.h"




address* exec(request* req) {
    process* proc = find_process(req->id);
    if(proc == NULL) {
        printf("Erro: Processo '%s' não existe!\n", req->id);
        return NULL;
    }
    if(proc->status == IN_DISC) {
        if(wakeup(proc) == NULL) {
            printf("Erro: Processo '%s' não pode ser acordado!\n", req->id);
            return NULL;
        }
    }
    int** page_number_bits = malloc(sizeof(int*));
    address* physical_address = get_physical_address(init_address_decimal(req->number, VIRTUAL_ADDRESS_SIZE),
        proc->table, req->op, page_number_bits);
    if(physical_address == NULL && (*page_number_bits) == NULL) {
        return NULL;
    }
    if(physical_address == NULL && (*page_number_bits) != NULL) {
        int* frame_number_bits = NULL;
        if(get_free_frames_number() > 0) {
            frame_number_bits = get_first_free_frame();
        }
        else {
            frame_number_bits = remove_best_page();
        }
        if(frame_number_bits == NULL) {
            printf("Error: não foi possível substituir uma página virtual!\n");
            return NULL;
        }
        if(get_page_in_disc(proc->swap_area, (*page_number_bits)) == NULL) {
            return NULL;
        }
        if(map_page(proc->table, &proc->table->pages[get_decimal_from_bits((*page_number_bits), PAGES_NUMBER_LEN)]) == NULL) {
            printf("Erro: não foi possível mapear a página!\n");
            return NULL;
        }
        else {
            receive_request(req);
            return NULL;
        }

        return NULL;
    }

    return physical_address;
}

void receive_request(request* req) {
    increase_ic();

    if(req->id == NULL) {
        return;
    }

    address* physical_address;
    process* proc;

    switch(req->op) {
        #pragma region EXEC
        case EXEC:
            printf("Processo '%s' solicitando a execução da instrução - operando - '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            if(physical_address != NULL) {
                printf("Processo '%s' executou a instrução - operando - '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
                    req->id,
                    req->number,
                    bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE),
                    physical_address->decimal,
                    bits_to_string_address(physical_address),
                    physical_address->decimal / 1024 / FRAME_SIZE,
                    bits_to_string_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAMES_NUMBER_LEN));
            }
            break;
        #pragma endregion

        #pragma region IO
        case IO:
            printf("Processo '%s' solicitando E/S para o dispositivo '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, bits_len(1)));

            proc = find_process(req->id);

            if(proc == NULL) {
                printf("Error: Process '%s' do not exist", req->id);
                break;
            }

            printf("I/O request finished!");
            break;
        #pragma endregion

        #pragma region READ
        case READ:
            printf("Processo '%s' solicitando leitura em '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            printf("Processo '%s' leu em '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE),
                physical_address->decimal,
                bits_to_string_address(physical_address),
                physical_address->decimal / 1024 / FRAME_SIZE,
                bits_to_string_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAMES_NUMBER_LEN));
            break;
        #pragma endregion
                    
        #pragma region WRITE
        case WRITE:
            printf("Processo '%s' solicitando escrita em '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            printf("Processo '%s' escreveu em '%d' (%s) \n\tno endereço físico '%lld' (%s) \n\tna quadro de página '%lld' (%s).\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE),
                physical_address->decimal,
                bits_to_string_address(physical_address),
                physical_address->decimal / 1024 / FRAME_SIZE,
                bits_to_string_decimal(physical_address->decimal / 1024 / FRAME_SIZE, FRAMES_NUMBER_LEN));
            break;
        #pragma endregion

        #pragma region CREATE
        case CREATE:
            printf("Criando o Processo '%s'...\n", req->id);

            proc = create_process();

            proc->id = req->id;
            proc->image_size = req->number;
            proc->swap_area = create_swap_area(proc->image_size);

            if(proc->swap_area == NULL) {
                printf("Não é possível criar o processo '%s'! Erro na SWAP.\n", proc->id);
                reset_process(proc);
                break;
            }

            proc->table = create_page_table();
            if(proc->table == NULL) {
                printf("Não é possível criar o processo '%s'! Erro na tabela de páginas.\n", proc->id);
                reset_process(proc);
                break;
            }

            if(proc->image_size > VIRTUAL_MEMORY_SIZE) {
                printf("Não é possível criar o processo '%s'! Imagem maior do que a memória virtual.\n", proc->id);
                reset_process(proc);
                break;
            }

            // o processo ainda não foi enviado para a RAM.
            proc->status = IN_DISC;
            printf("Processo '%s' criado em disco.\n", proc->id);

            if(wakeup(proc) == NULL) {
                printf("Não é possível criar o processo '%s' na RAM!\n", proc->id);
                reset_process(proc);
                break;
            }

            printf("Processo '%s' criado completamente.\n", proc->id);

            break;
        #pragma endregion
    }

    print_situation();
}
    

