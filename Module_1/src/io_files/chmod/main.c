// CHMOD system call program
// Reference: https://man7.org/linux/man-pages/man2/chmod.2.html

// Imports
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    // Declaration of variables
    const char *ls_command, *path_name;
    mode_t mode;
    int ans;
    
    ls_command = "ls -l file.txt"; // ls command
    path_name = "./file.txt"; // Path name

    mode = S_IRWXU | S_IRWXG | S_IRWXO; // The file mode bits
    /*
        S_IRWXU: Read, write and execute permission bit for the owner of the file
        S_IRWXG: Read, write and execute permission bit for the group owner of the file
        S_IRWXO: Read, write and execute permission bit for other users
    */

    printf("###################################\n");
    printf("#        CHMOD system call        #\n");
    printf("###################################\n\n");

    printf(">> Permissions before CHMOD:\n");
    system(ls_command); // Display permissions before CHMOD  

    ans = chmod(path_name, mode); // Change file permission

    if (ans != 0) // Error
        printf(">> Error in CHMOD!\n");
    else { // Success
        printf(">> Permissions after CHMOD:\n");
        system(ls_command); // Display permissions after CHMOD 
    }

    return 0;
}