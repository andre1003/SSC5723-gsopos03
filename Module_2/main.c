/*
- Produtor
- Consumidor
- Controle de buffer (struct)
    -> Cheio
    -> Vazio

Tem que ter:
- Semáforo
*/

/* INCLUDES */
#include "stdlib.h"
#include "stdio.h"
//#include "pthreads.h"




/* STRUCTS */
typedef struct BUFFER {
    int id;
    struct BUFFER* next;
} buffer;


/* FUNCTIONS */
buffer* insert(buffer* head, int id) {
    buffer* node = (buffer*) malloc (sizeof(buffer));
    node->id = id;
    node->next = NULL; // For now, this is a queue

    if(!head)
        return node;

    buffer* aux = head;
    while(aux->next)
        aux = aux->next;

    aux->next = node;

    return head;
}

buffer* consume(buffer* head, int id) {
    buffer* current = head;
    buffer* previous = NULL;

    while(current && current->id != id) {
        previous = current;
        current = current->next;
    }

    if(current) {
        if(previous) {
            previous->next = current->next;
            free(current);
        }
        else {
            previous = current->next;
            free(current);
            return previous;
        }
    }
    else {
        printf("This value was not found on the list...\n");
    }

    return head;
}

// Print
void printBuffer(buffer* head) {
    buffer* aux = head;

    while(aux != NULL) {
        printf("%d", aux->id);

        if(aux->next != NULL)
            printf(" -> ");
        else
            printf("\n");

        aux = aux->next;
    }
}


/* MAIN */
int main() {
    buffer* head = NULL;
    int i, consumeId;

    for(i = 0; i < 5; i++)
        head = insert(head, i);

    printBuffer(head);

    for(i = 0; i < 3; i++) {
        printf("\nType a value to be removed: ");
        scanf("%d", &consumeId);
        head = consume(head, consumeId);
        printBuffer(head);
    }
}