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
        The "num" is to illustrate that the new process is a copy of the father (they share the same address, for example),
        but changing the value by the son does not affect the value of the father.
    */
    int sec = 3;
    int num = 10;
    
    printf("-------------------- \n");
    printf(" Starting execution  \n");
    printf("-------------------- \n");
    sleep(sec);

    // Create a new process (fork) and return the pid_t of the system call
    id = fork();

    // If the ID returned is GREATER than zero (0), then we are in the FATHER process.
    if (id > 0){
        /*
            This is the code that is executed by the FATHER process.
            Some information that identifies this is displayed on the console, such as:
            FATHER PID, address space used by "num" value and your value.
        */
        printf(" [FATHER]: My PID is -> %i \n", getpid());
        printf(" [FATHER]: I have the number %i that was in address space '%p' \n", num, &num);
        printf(" [FATHER]: Now I will wait for execution of my son \n");
        
        /*
            "wait()" is also a system call primitive.
            Although the focus is on illustrating fork(),
            it was used here to block the father process execution until the son terminates.
        */
        wait(NULL);

        /*
            After the son process ends, the father can terminate.
            But before finish, the value of "num" that the father contains in the address space is displayed.
            Note that the value does not change, because it is not affected by the son's manipulation value.
        */
        printf(" [FATHER]: My num value still is -> %i \n", num);
        printf(" [FATHER]: My son finished, now I will finish too! \n");
        sleep(sec);
    }

    // If the ID returned is EQUAL to zero (0), then we are in the SON process.
    else if (id == 0){
        /*
            This code is executed by the SON process.
            Some information that identifies this is displayed on the console, such as:
            SON PID, FATHER PID, address space used when handle "num" and your value after manipulation.
        */
        printf(" [SON]: My PID is -> %i \n", getpid());
        printf(" [SON]: My father's PID is -> %i \n", getppid());

        /* 
            Sum performed to change value of "num" by the SON process.
            Even using the same address space, 
            this manipulation should not affect the value of "num" being processed in the FATHER process.
        */
        num += 10;
        printf(" [SON]: I used the address space '%p', but my num is: %i \n", &num, num);

        // Wait a few seconds and print in the console the termination of the SON process
        printf(" [SON]: I will sleep for %i seconds before I finish. \n", sec);
        sleep(sec);
        printf(" [SON]: Finishing... \n");
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
