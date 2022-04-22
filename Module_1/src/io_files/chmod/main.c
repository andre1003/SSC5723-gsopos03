/*
    Reference: https://man7.org/linux/man-pages/man2/chmod.2.html
*/

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    // Declaration of variables
    const char *ls_command, *path_name;
    mode_t mode;
    int ans;
    
    ls_command = "ls -l file.txt"; // ls command
    path_name = "./file.txt"; // Path name
    mode = S_IRWXU | S_IRWXG | S_IRWXO;

    printf(">> Permissions before CHMOD:\n");
    system(ls_command);

    ans = chmod(path_name, mode);

    if (ans != 0)
        printf(">> Error in CHMOD!\n");
    else {
        printf(">> Permissions after CHMOD:\n");
        system(ls_command);
    }

    return 0;
}