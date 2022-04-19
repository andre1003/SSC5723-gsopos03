/* INCLUDES */
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


/* MAIN CODE */
int main(int argc, char const* argv[]) {
    void *programBreak = sbrk(0);
    int *intPtr = (int *) programBreak;
    int response = brk(intPtr + 3);

    if (response != 0)
    {
        printf("Couldn't allocate memory!\n");
        return EXIT_FAILURE;
    }

    printf("Insert the first number: ");
    scanf("%d", intPtr);
    printf("Insert the second number: ");
    scanf("%d", (intPtr + 1));

    *(intPtr + 2) = *(intPtr) + *(intPtr + 1);
    
    printf("\nThe somatory is: %d\n", *(intPtr + 2));
    
    response = brk(programBreak);    
    
    if (response != 0)
    {
        printf("Couldn't deallocate memory!\n");
        return EXIT_FAILURE;
    }
    return 0;
}