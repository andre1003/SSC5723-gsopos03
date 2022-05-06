// I/O bound program

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    // Declaration of variables
    int numFiles, i, j;
    FILE *prevFile, *currFile;
    char ch, filePath[256];

    numFiles = 10; // Number of files. 
    // Always greater than 1

    printf("###################################\n");
    printf("#            I/O bound            #\n");
    printf("###################################\n\n");
    printf(">> Building the files...\n");

    for(i = 2; i <= numFiles; i++) { // Loop through the building of each file
        snprintf(filePath, sizeof(filePath), "file_%d.txt", i - 1); // Build previous file path name
        prevFile = fopen(filePath, "r"); // Open the previous file

        if(prevFile != NULL) { // Check if file exists
            snprintf(filePath, sizeof(filePath), "file_%d.txt", i); // Build current file path name
            currFile = fopen(filePath, "w"); // Create the current file

            while((ch = fgetc(prevFile)) != EOF) // Copy content from previous file to current one  
                fputc(ch, currFile); // Copying each char (ch)
        }
        else { // Error, return -1
            printf(">> Error opening file!\n");
            return -1;
        }

        fclose(prevFile); // Close the previous file
        fclose(currFile); // Close the current file
    }

    printf(">> Removing the files...\n");

    for(i = 2; i <= numFiles; i++) { // Loop through built files
        snprintf(filePath, sizeof(filePath), "file_%d.txt", i); // Build built file path name
        remove(filePath); // Remove the file
    }

    printf(">> Complete!\n");

    return 0;
}