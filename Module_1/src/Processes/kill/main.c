#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    // Declaration of variable that will receive the return ID of fork() on creation of the new process
    pid_t id;

    /* 
        Declaration of variables used. Change the values if you like.
        The "sec" is to sleep some seconds and monitor the executions on the console.
    */
    int sec = 3;
    
    printf("-------------------- \n");
    printf(" Starting execution  \n");
    printf("-------------------- \n");
    sleep(sec);

    // Create a new process (fork) and return the pid_t of the system call
    id = fork();

    // If the ID returned is EQUAL to zero (0), then we are in the SON process.
    if (id == 0){
        /*
            This code is executed by the SON process.
            Some information that identifies this is displayed on the console, such as:
            SON PID and FATHER PID.
        */
        printf(" [SON]: My PID is -> %i \n", getpid());
        printf(" [SON]: My father's PID is -> %i \n", getppid());

        /*
            Display in the console the print that indicates the infinite loop implemented
            to keep the SON process always running (unless it is forced to terminate)
        */
        printf(" [SON]: I will execute forever (infinite loop) ! \n");
        for (;;);

    }

    // If the ID returned is GREATER than zero (0), then we are in the FATHER process.
    else if (id > 0){
        /*
            This code is executed by the FATHER process.
            Some information that identifies this is displayed on the console, such as: FATHER PID
        */
        printf(" [FATHER]: My PID is -> %i \n", getpid());
        printf(" [FATHER]: I will wait %i seconds for the execution of my son. \n", sec);
        sleep(sec);

        // Display in the console that the FATHER process will terminate the SON process
        printf(" [FATHER]: Now I will finish my son! \n");

        /* 
            Terminates the SON process by sending a "-9" signal
            and waits to move on.
        */
        kill(id, SIGKILL);
        wait(NULL);
        
        // Display in the console that the FATHER process wil also terminate
        printf(" [FATHER]: My son was finished, now I will too ! \n");
        sleep(sec);

    }

     /* 
        If the ID returned is different from anything (for example, SMALLER than zero (0)),
        so it was not possible to execute fork() and the new (son) process was not created.
    */
    else{
        printf("Error: could not execute fork() ! \n");
        exit(1);
    }

    return 0;
}
