#include "request.h"
#include "stdio.h"
#include "stdlib.h"
#include "manager.h"
#include "process.h"




address* exec(request* req) {
    process* proc = find_process(req->id);
    if(proc == NULL) {
        printf("Error: Process '%s' does not exist!\n", req->id);
        return NULL;
    }
    if(proc->status == IN_DISK) {
        if(wakeup(proc) == NULL) {
            printf("Error: Process '%s' could not be awaken!\n", req->id);
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
            printf("Error: could not replace a virtual page!\n");
            return NULL;
        }
        if(get_page_in_disk(proc->swap_area, (*page_number_bits)) == NULL) {
            return NULL;
        }
        if(map_page(proc->table, &proc->table->pages[get_decimal_from_bits((*page_number_bits), PAGES_NUMBER_LEN)]) == NULL) {
            printf("Error: could not map page!\n");
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
            printf("Process '%s' requesting instruction execution - operand - '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            if(physical_address != NULL) {
                printf("Process '%s' instruction executed - operand - '%d' (%s) \n\tin the physical address '%lld' (%s) \n\tin the page frame '%lld' (%s).\n",
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
            printf("Process '%s' requesting I/O for the device '%d' (%s)...\n",
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
            printf("Processo '%s' requesting read in '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            printf("Process '%s' read in '%d' (%s) \n\tin the physical address '%lld' (%s) \n\tin the page frame '%lld' (%s).\n",
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
            printf("Process '%s' requesting write in '%d' (%s)...\n",
                req->id,
                req->number,
                bits_to_string_decimal(req->number, VIRTUAL_ADDRESS_SIZE));

            physical_address = exec(req);

            printf("Process '%s' wrote in '%d' (%s) \n\tin the physical address '%lld' (%s) \n\tin the page frame '%lld' (%s).\n",
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
            printf("Creating process '%s'...\n", req->id);

            proc = create_process();

            proc->id = req->id;
            proc->image_size = req->number;
            proc->swap_area = create_swap_area(proc->image_size);

            if(proc->swap_area == NULL) {
                printf("Unable to create process '%s'! SWAP error.\n", proc->id);
                reset_process(proc);
                break;
            }

            proc->table = create_page_table();
            if(proc->table == NULL) {
                printf("Unable to create process '%s'! Page table error.\n", proc->id);
                reset_process(proc);
                break;
            }

            if(proc->image_size > VIRTUAL_MEMORY_SIZE) {
                printf("Unable to create process '%s'! Image larger than virtual memory.\n", proc->id);
                reset_process(proc);
                break;
            }

            // o processo ainda n�o foi enviado para a RAM.
            proc->status = IN_DISK;
            printf("Process '%s' created in disk.\n", proc->id);

            if(wakeup(proc) == NULL) {
                printf("Unable to create process '%s' na RAM!\n", proc->id);
                reset_process(proc);
                break;
            }

            printf("Process '%s' creation successfully.\n", proc->id);

            break;
        #pragma endregion
    }

    print_situation();
}
