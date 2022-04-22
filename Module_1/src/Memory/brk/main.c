/* INCLUDES */
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


/* MAIN CODE */
int main(int argc, char const* argv[]) {
    // Use sbrk to know the current pontier to the memory limit allocated for the process
    void *programBreak = sbrk(0);

    // Declarate the ptr variable for manipulating integers
    int *intPtr = (int *) programBreak;

    // Allocate memory for this process using brk. This function returns 0 for success and -1 for error. It takes a ptr for the memory limit of the process
    int response = brk(intPtr + 3);

    // Check if not successful
    if (response != 0) {
        // Print error message and exit
        printf("Couldn't allocate memory!\n");
        return EXIT_FAILURE;
    }

    // Start normal operation with ptr. For this example, it was used Fibonacci serie
    // Start first number
    *(intPtr) = 0;
    // Start second number
    *(intPtr + 1) = 1;

    // Auxiliar variables
    int i = 0, n = 0;

    // Ask user how many numbers the series shoud have, not letting be lower than 2
    do {
        printf("Insert the total fibonacci numbers (greater than 2): ");
        scanf("%d", &n);
    } while(n < 3);
    
    // Print the first two numbers of serie
    printf("\nFibonacci serie:\n%d -> %d -> ", *(intPtr), *(intPtr + 1));
    fflush(stdout); // Needed to print the ptr. See https://stackoverflow.com/questions/1716296/why-does-printf-not-flush-after-the-call-unless-a-newline-is-in-the-format-strin for more info
    
    // Fibonacci loop
    for(i = 2; i < n; i++) {
        // Get the next value
        *(intPtr + 2) = *(intPtr) + *(intPtr + 1);

        // Reset the first and second variables to continue the loop
        *(intPtr) = *(intPtr + 1);
        *(intPtr + 1) = *(intPtr + 2);

        // Print the next value
        if(i == n - 1)
            printf("%d\n", *(intPtr + 2));
        else 
            printf("%d -> ", *(intPtr + 2));
        fflush(stdout);
    }
    
    // Free the allocated memory slots
    response = brk(programBreak);    
    
    // Check if successful
    if (response != 0) {
        // Print error and exit
        printf("Couldn't deallocate memory!\n");
        return EXIT_FAILURE;
    }

    // Exit program
    return 0;
}