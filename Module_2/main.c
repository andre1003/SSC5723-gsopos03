/* DEFINES */
#define MAX_BUFFER_SIZE 5   // Maximum number of elements in buffer node list



/* INCLUDES */
#include "stdlib.h"
#include "stdio.h"
#include "pthread.h"




/* STRUCTS */
// Node struct
typedef struct NODE {
    int id;             // Node ID
    int isEmpty;        // 1 - is empty | 0 - is full
    struct NODE* next;  // Next element
} node;


// Buffer struct
typedef struct BUFFER {
    pthread_cond_t full;    // Full semaphore
    pthread_cond_t empty;   // Empty semaphore
    pthread_mutex_t mutex;  // Mutex semaphore

    int countFull;          // Full slots counter
    int countEmpty;         // Empty slots counter

    node* head;             // Node list head
    node* nextEmpty;        // Next empty memory slot
    node* nextFull;         // Next full memory slot
} buffer;




/* FUNCTIONS */
/// <summary>
/// Insert a node into a given list
/// </summary>
/// <param name="head">List to insert the node.</param>
/// <param name="id">Node's ID.</param>
/// <param name="isEmpty">Is the node empty.</param>
/// <returns>Return the full list.</returns>
node* insert(node* head, int id, int isEmpty) {
    // Allocates the node
    node* newNode = (node*)malloc(sizeof(node));

    // Node variables setting
    newNode->id = id;                   // ID
    newNode->isEmpty = isEmpty;         // Is empty
    newNode->next = NULL;               // Next element

    // Insert the element
    if (!head)                          // If head is null
        return newNode;                 // Return the node

    node* current = head;               // Init the current node at the list's head
    while (current->next)               // While the current node has a next element
        current = current->next;        // Go through the list

    current->next = newNode;            // Insert the created node

    return head;                        // Return the list
}


/// <summary>
/// Remove a node by id.
/// </summary>
/// <param name="head">The first node list element.</param>
/// <param name="id">The node's ID to be removed.</param>
/// <returns>The node list without the removed node.</returns>
node* del(node* head, int id) {
    node* current = head;
    node* previous = NULL;

    // Try to find the node to be removed
    while (current && current->id != id) {
        previous = current;
        current = current->next;
    }

    // If there is a node to be removed
    if (current) {
        // Is not the first element
        if (previous) {
            previous->next = current->next;
            free(current);
        }
        // Is the first element
        else {
            previous = current->next;
            free(current);
            return previous;
        }
    }
    // Node not founded
    else {
        printf("This value was not found on the list...\n");
    }

    // Return the node list
    return head;
}


/// <summary>
/// Creates the buffer.
/// </summary>
/// <param name="buff">Buffer struct.</param>
/// <returns>Created buffer.</returns>
buffer create(buffer buff) {
    buff.countFull = 0;
    buff.countEmpty = MAX_BUFFER_SIZE;

    buff.head = NULL;
    buff.nextFull = NULL;
    buff.nextEmpty = NULL;

    return buff;
}

/// <summary>
/// Initializes buffer. Creates the node list and sets the semaphores.
/// </summary>
/// <param name="buff">Buffer struct.</param>
/// <returns>Initializes buffer.</returns>
buffer init(buffer buff) {
    // Create node list
    int i;

    // Insert MAX_BUFFER_SIZE nodes in the buffer head list
    for(i = 0; i < MAX_BUFFER_SIZE; i++)
        buff.head = insert(buff.head, i, 1);

    buff.nextEmpty = buff.head;             // The next empty element is the first buffer list element

    // Semaphores init with NULL value
    pthread_mutex_init(&buff.mutex, NULL);  // Mutex
    pthread_cond_init(&buff.empty, NULL);   // Empty
    pthread_cond_init(&buff.full, NULL);    // Full

    // Return buffer
    return buff;
}


/// <summary>
/// Print the node list.
/// </summary>
/// <param name="head">Node list first element.</param>
void print_data(node* head) {
    node* aux = head;

    // Go through the node list
    while(aux != NULL) {
        printf("|ID: %d, Is Empty: %d|", aux->id, aux->isEmpty);

        if(aux->next != NULL)
            printf(" --> ");
        else
            printf("\n");

        aux = aux->next;
    }
}


/// <summary>
/// Destroy the buffer struct.
/// </summary>
/// <param name="buff"> Buffer struct.</param>
/// <returns>Return the destroyed buffer.</returns>
buffer destroy(buffer buff) {
    // Destroy the semaphores
    pthread_cond_destroy(&buff.empty);  // Empty
    pthread_cond_destroy(&buff.full);   // Full
    pthread_mutex_destroy(&buff.mutex); // Mutex

    // Destroy the node list
    int i;
    for (i = 0; i < MAX_BUFFER_SIZE; i++)
        buff.head = del(buff.head, i);

    // Return an empty buffer struct
    return buff;
}


void* produce() {

}


void* consume() {

}




/* MAIN */
int main() {
    // Create buffer
    buffer buff;                                    // Buffer
    buff = create(buff);                            // Create buffer
    buff = init(buff);                              // Init buffer

    print_data(buff.head);                          // Print the initialized buffer node list

    // Create the threads
    pthread_t producer;                             // Producer thread variable
    pthread_t consumer;                             // Consumer thread variable

    pthread_create(&producer, NULL, produce, NULL); // Producer thread creation
    pthread_create(&consumer, NULL, consume, NULL); // Consumer thread creation

    pthread_join(producer, NULL);                   // Wait for the producer end
    pthread_join(consumer, NULL);                   // Wait for the consumer end

    // Destroy the buffer
    buff = destroy(buff);                           // Destroy the buffer struct completely

    // Exit
    return 0;
}