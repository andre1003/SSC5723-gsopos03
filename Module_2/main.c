#pragma region Defines
/* DEFINES */
#define MAX_BUFFER_SIZE 5   // Maximum number of elements in buffer node list
#define TRUE            1   // True const value
#define FALSE           0   // False const value
#pragma endregion




#pragma region Includes
/* INCLUDES */
#include "pthread.h"
#include "semaphore.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "unistd.h"
#pragma endregion



sem_t full;
sem_t empty;
pthread_mutex_t mutex;


#pragma region Structs
/* STRUCTS */
// Node struct
typedef struct NODE {
    int id;                 // Node ID
    int value;              // Value
    int isEmpty;            // TRUE - is empty | FALSE - is full
    struct NODE* next;      // Next element
} node;


// Buffer struct
typedef struct BUFFER {
    node* head;             // Node list head
    node* nextEmpty;        // Next empty memory slot
    node* nextFull;         // Next full memory slot
} buffer;
#pragma endregion




#pragma region Functions
#pragma region Node List
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
    newNode->value = -1;                // Value is -1 (not a valid value)
    newNode->isEmpty = isEmpty;         // Is empty
    newNode->next = NULL;               // Next element

    // Insert the element
    if(!head)                          // If head is null
        return newNode;                 // Return the node

    node* current = head;               // Init the current node at the list's head
    while(current->next)               // While the current node has a next element
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
    while(current && current->id != id) {
        previous = current;
        current = current->next;
    }

    // If there is a node to be removed
    if(current) {
        // Is not the first element
        if(previous) {
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
        printf(">> This value was not found on the list...\n");
    }

    // Return the node list
    return head;
}


/// <summary>
/// Print the node list.
/// </summary>
/// <param name="head">Node list first element.</param>
void print_data(node* head) {
    node* aux = head;

    printf("\n---------------------\n>> Node list:\n");

    // Go through the node list
    while(aux != NULL) {
        printf("|ID: %d\tIs Empty: %d\tValue: %d|\n", aux->id, aux->isEmpty, aux->value);
        fflush(stdout);
        aux = aux->next;
    }

    printf("---------------------\n\n");
}
#pragma endregion


#pragma region Buffer
/// <summary>
/// Creates the buffer.
/// </summary>
/// <param name="buff">Buffer struct.</param>
/// <returns>Created buffer.</returns>
buffer create(buffer buff) {
    buff.head = NULL;
    buff.nextFull = NULL;
    buff.nextEmpty = NULL;

    printf(">> Buffer created successfully!\n");

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
        buff.head = insert(buff.head, i, TRUE);

    buff.nextEmpty = buff.head;             // The next empty element is the first buffer list element  
    buff.nextFull = NULL;                   // The next full element is NULL

    // Semaphores init
    pthread_mutex_init(&mutex, NULL);       // Mutex
    sem_init(&empty, 0, MAX_BUFFER_SIZE);   // Empty
    sem_init(&full, 0, 0);                  // Full

    printf(">> Buffer initialized successfully!\n");

    // Return buffer
    return buff;
}


/// <summary>
/// Function for updating a given buffer.
/// </summary>
/// <param name="buff">Buffer struct.</param>
/// <param name="value">Value to be inserted.</param>
/// <returns>Updated buffer.</returns>
buffer update(buffer buff, int value, int isEmpty) {
    

    node* current = buff.head;

    // Update nextEmpty node
    while(current && current->isEmpty == FALSE)
        current = current->next;

    if(current) {
        buff.nextEmpty = current;
    }
    else {
        buff.nextEmpty = NULL;
    }

    // Update nextFull node
    current = buff.head;
    while(current && current->isEmpty == TRUE)
        current = current->next;

    if(current) {
        buff.nextFull = current;
    }
    else {
        buff.nextFull = NULL;
    }

    // Check if is producing or consuming
    if(isEmpty == TRUE) {   // Consuming
        buff.nextFull->value = value;
        buff.nextFull->isEmpty = isEmpty;
    }
    else {                  // Producing

        buff.nextEmpty->value = value;
        buff.nextEmpty->isEmpty = isEmpty;
    }

    // Return the buffer
    return buff;
}


/// <summary>
/// Destroy the buffer struct.
/// </summary>
/// <param name="buff"> Buffer struct.</param>
/// <returns>Return the destroyed buffer.</returns>
buffer destroy(buffer buff) {
    // Destroy the semaphores
    sem_destroy(&empty);            // Empty
    sem_destroy(&full);             // Full
    pthread_mutex_destroy(&mutex);  // Mutex

    // Destroy the node list
    int i;
    for(i = 0; i < MAX_BUFFER_SIZE; i++)
        buff.head = del(buff.head, i);

    printf("\n\033[0;37m>> Buffer destroyed successfully!\n");

    // Return an empty buffer struct
    return buff;
}
#pragma endregion

#pragma region Producer and Consumer
/// <summary>
/// Producer function. It creates items and insert them in the buffer, if possible.
/// </summary>
/// <param name="arg">Buffer struct in void* type.</param>
void* produce(void* arg) {
    // Reparse void* to buffer
    buffer buff = *(buffer*)arg;

    // Producer
    while(TRUE) {
        // Produce item
        int item = rand() % 100 + 1;

        sem_wait(&empty);               // Down empty
        pthread_mutex_lock(&mutex);     // Lock mutex semaphore

        buff = update(buff, rand() % 100 + 1, FALSE);
		printf("\n\033[0;32m>> The producer has produced an item.");
		fflush(stdout);
        sleep(1);

        pthread_mutex_unlock(&mutex);   // Unlock mutex semaphore
        sem_post(&full);                // Up full
    }
    pthread_exit(NULL);
}


/// <summary>
/// Consumer function. It consumes items and remove them from the buffer, if possible.
/// </summary>
/// <param name="arg">Buffer struct in void* type.</param>
void* consume(void* arg) {
    // Reparse void* to buffer
    buffer buff = *(buffer*)arg;

    // Consumer
    while(TRUE) {
        sem_wait(&full);                // Down full
        pthread_mutex_lock(&mutex);     // Lock mutex semaphore

        buff = update(buff, -1, TRUE);
        printf("\n\033[0;31m>> The consumer has consumed an item.");
        fflush(stdout);
        sleep(1);

        pthread_mutex_unlock(&mutex);   // Unlock mutex semaphore
        sem_post(&empty);               // Up empty
    }
    pthread_exit(NULL);
}
#pragma endregion
#pragma endregion

pthread_mutex_t potato = PTHREAD_MUTEX_INITIALIZER;

#pragma region Main Code
/* MAIN */
int main() {
    // Print header
    printf("\n#################################################\n");
    printf("#\t\tProducer and Consumer\t\t#\n");
    printf("#################################################\n\n\n");

    // Random values seed
    srand(time(NULL));

    // Create buffer
    buffer buff;                                                // Buffer

    buff = create(buff);                                        // Create buffer
    buff = init(buff);                                          // Init buffer

    print_data(buff.head);                                      // Print the initialized buffer node list

    // Create the threads
    pthread_t producer;                                         // Producer thread variable
    pthread_t consumer;                                         // Consumer thread variable

    pthread_create(&producer, NULL, &produce, (void*)(&buff));   // Producer thread creation
    pthread_create(&consumer, NULL, &consume, (void*)(&buff));   // Consumer thread creation

    pthread_join(producer, NULL);                               // Wait for the producer end
    pthread_join(consumer, NULL);                               // Wait for the consumer end

    // Destroy the buffer
    buff = destroy(buff);                                       // Destroy the buffer struct completely

    // Exit
    return 0;
}
#pragma endregion