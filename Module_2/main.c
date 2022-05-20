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
#include "pthreads.h"




/* STRUCTS */
typedef struct BUFFER {
    int id;
    struct BUFFER* next;
} buffer;


/* FUNCTIONS */
buffer* insert(buffer* bffr, int id) {
    return NULL;
}

buffer* remove(buffer* bffr, int id) {
    return NULL;
}


/* MAIN */
int main() {
    return 0;
}