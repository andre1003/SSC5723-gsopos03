// EXECVE system call program
// Reference: https://man7.org/linux/man-pages/man2/execve.2.html

// Imports
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    char pathName[] = "./new"; // This is the path where is the "new" program

    /* This is the parameter that was passed to the execution of the new process
       "Hello World" was fixed, but it could be any string
       If you don't want to pass a parameter to the new process, you can leave NULL in arguments */
    char param[] = "Hello World";
    
    /* This is the definition of the arguments that will be passed to the new process
       If you don't want to pass a parameter to the new process, you can leave it NULL
       The NULL at the end of the vector is necessary because it indicates the moment when the end was reached */
    char *arg[] = {pathName, param, NULL};

    printf("###################################\n");
    printf("#        EXECVE system call       #\n");
    printf("###################################\n\n");

    // Print to illustrate the attempt to execute the new process (wait for 3 seconds to continue)
    printf(">> Trying to run: %s\n", pathName);
    sleep(3);

    /* Executes the "execve" system call to swap the running process with the new one
       No returns are normally expected. If it exists (value -1) is because something went wrong
       "__environ" defines a NULL-terminated array of environment variables
       "execve" parameters:
            path of new program;
            list of possible arguments for the new program;
            user environment where the new process will run. */
    if(execve(pathName, arg, __environ) == -1)
        printf(">> Something went wrong with 'execve'!\n");
    
    /* If no return, the new process has been executed and terminated
       If everything went well (as expected) the running process was replaced by the new one and the prints below will not be shown on the screen (because they will not be executed) */;
    printf(">> If all goes well, this print should not appear!\n");

    return 0;
}