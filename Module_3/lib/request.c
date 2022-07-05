#include "request.h"
#include "stdio.h"
#include "stdlib.h"
#include "manager.h"
#include "process.h"




address* exec(request* req) {
    // Try to find process
    process* proc = find_process(req->id);
    if(proc == NULL) {
        printf("Error: Process '%s' does not exist!\n", req->id);
        return NULL;
    }

    // Try to get process (and wake it up if needed)
    if(proc->status == IN_DISK) {
        if(wakeup(proc) == NULL) {
            printf("Error: Process '%s' could not be awaken!\n", req->id);
            return NULL;
        }
    }
    
    // Get physical address
    int** page_number_bits = malloc(sizeof(int*));
    address* physical_address = get_physical_address(init_address_decimal(req->number, VIRTUAL_ADDRESS_SIZE),
        proc->table, req->op, page_number_bits);
    
    // If physical address and page number bits are null, exit this function
    if(physical_address == NULL && (*page_number_bits) == NULL) {
        return NULL;
    }
    
    // If physical address is null but page number bits is not
    if(physical_address == NULL && (*page_number_bits) != NULL) {
        int* frame_number_bits = NULL;

        // Depending on free frames number, get the first free fram or remove the best page
        if(get_free_frames_number() > 0) {
            frame_number_bits = get_first_free_frame();
        }
        else {
            frame_number_bits = remove_best_page();
        }

        // Virtual page replacement error
        if(frame_number_bits == NULL) {
            printf("Error: could not replace a virtual page!\n");
            return NULL;
        }

        // Get page in disk error
        if(get_page_in_disk(proc->swap_area, (*page_number_bits)) == NULL) {
            return NULL;
        }

        // Map page error
        if(map_page(proc->table, &proc->table->pages[get_decimal_from_bits((*page_number_bits), PAGES_NUMBER_LEN)]) == NULL) {
            printf("Error: could not map page!\n");
            return NULL;
        }
        // Receive the request recursivly
        else {
            receive_request(req);
            return NULL;
        }

        // return null
        return NULL;
    }

    // Return the physical address
    return physical_address;
}

void receive_request(request* req) {
    // Increase instruction counter
    increase_ic();

    // If there is no id, exit this function
    if(req->id == NULL) {
        return;
    }

    // Variable declaration
    address* physical_address;
    process* proc;

    // Switch operation cases
    switch(req->op) {
        #pragma region EXEC
        // Execution case
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
        // I/O case
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
        // Read case
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
        // Write case
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
        // Create case
        case CREATE:
            printf("Creating process '%s'...\n", req->id);

            proc = create_process();

            proc->id = req->id;
            proc->image_size = req->number;
            proc->swap_area = create_swap_area(proc->image_size);

            // SWAP error
            if(proc->swap_area == NULL) {
                printf("Unable to create process '%s'! SWAP error.\n", proc->id);
                reset_process(proc);
                break;
            }

            // Page table creation error
            proc->table = create_page_table();
            if(proc->table == NULL) {
                printf("Unable to create process '%s'! Page table error.\n", proc->id);
                reset_process(proc);
                break;
            }

            // Image size error
            if(proc->image_size > VIRTUAL_MEMORY_SIZE) {
                printf("Unable to create process '%s'! Image larger than virtual memory.\n", proc->id);
                reset_process(proc);
                break;
            }

            // Create process in disk
            proc->status = IN_DISK;
            printf("Process '%s' created in disk.\n", proc->id);
            
            // Process creation errro
            if(wakeup(proc) == NULL) {
                printf("Unable to create process '%s' na RAM!\n", proc->id);
                reset_process(proc);
                break;
            }

            // Process creation success
            printf("Process '%s' creation successfully.\n", proc->id);
            break;
        #pragma endregion
    }

    // Print current situation
    print_situation();
}
