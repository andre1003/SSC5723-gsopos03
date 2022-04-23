#include <stdio.h>

//Standard parameters: number of arguments and vector of arguments
int main(int argc, char const *argv[])
{

    // Prints to show in the console that this program was executed
    printf(" ------------------------------ \n");
    printf(" The new program was executed! \n");

    // If there is only 1 argument,
    //print that no parameters were informed to the new program
    if (argc != 2){
        printf(" No parameter informed! \n");
    }
    // If in addition to the program name parameter (argv[0]), a second parameter was informed
    //print second content in the console
    else{
        printf(" Informed parameter contains: %s \n", argv[1]);
    }

    printf(" ----------------------------- \n");

    return 0;
}


