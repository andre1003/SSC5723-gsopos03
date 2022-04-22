// I/O bound program

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {
    // Declaration of variables
    int num_files, i, j;
    FILE *prev_file, *curr_file;
    char ch, file_path[256];

    num_files = 10; // Number of files. 
    // Always greater than 1

    printf("###################################\n");
    printf("#            I/O bound            #\n");
    printf("###################################\n\n");
    printf(">> Building the files...\n");

    for(i = 2; i <= num_files; i++) { // Loop through the building of each file
        snprintf(file_path, sizeof(file_path), "file_%d.txt", i - 1); // Build previous file path name
        prev_file = fopen(file_path, "r"); // Open the previous file

        if(prev_file != NULL) { // Check if file exists
            snprintf(file_path, sizeof(file_path), "file_%d.txt", i); // Build current file path name
            curr_file = fopen(file_path, "w"); // Create the current file

            while((ch = fgetc(prev_file)) != EOF) // Copy content from previous file to current one  
                fputc(ch, curr_file); // Copying each char (ch)
        }
        else { // Error, return -1
            printf(">> Error opening file!\n");
            return -1;
        }

        fclose(prev_file); // Close the previous file
        fclose(curr_file); // Close the current file
    }

    printf(">> Removing the files...\n");

    for(i = 2; i <= num_files; i++) { // Loop through built files
        snprintf(file_path, sizeof(file_path), "file_%d.txt", i); // Build built file path name
        remove(file_path); // Remove the file
    }

    printf(">> Complete!\n");

    return 0;
}