// CHMOD system call program
// Reference: https://man7.org/linux/man-pages/man2/chmod.2.html

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
    // Declaration of variables
    const char *lsCommand, *pathName;
    mode_t mode;
    int ans;
    
    lsCommand = "ls -l file.txt"; // ls command
    pathName = "./file.txt"; // Path name

    mode = S_IRWXU | S_IRWXG | S_IRWXO; // The file mode bits
    /* S_IRWXU: Read, write and execute permission bit for the owner of the file
       S_IRWXG: Read, write and execute permission bit for the group owner of the file
       S_IRWXO: Read, write and execute permission bit for other users */

    printf("###################################\n");
    printf("#        CHMOD system call        #\n");
    printf("###################################\n\n");

    printf(">> Permissions before CHMOD:\n");
    system(lsCommand); // Display permissions before CHMOD  

    ans = chmod(pathName, mode); // Change file permission

    if (ans != 0) // Error
        printf(">> Error in CHMOD!\n");
    else { // Success
        printf(">> Permissions after CHMOD:\n");
        system(lsCommand); // Display permissions after CHMOD 
    }

    return 0;
}