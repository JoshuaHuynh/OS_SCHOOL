//Name: Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid() and getppid()
#include <unistd.h> //For getpid() and getppid()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()

void getInfo(pid_t fork_val,int status); //Both the parent and the child use this function to report its process information.
void getTimes(pid_t fork_val,struct tms buf); //Finds and print the user time and system time for both the parent and child processes.  Also prints time(NULL) afterwards.

int main()
{
    struct tms buf;
    times(&buf); //This function gives the user time and system time for each the parent process and child process

    int status;
    printf("START: %ld\n",time(NULL)); //prints the number of seconds since the Epoch (00:00:00 UTC, January 1, 1970).

    pid_t fork_val = fork(); // fork() creates a child process.  On the parent process, the child's process ID is returned.  On the child process, a 0 is returned.

    if(fork_val == -1){ // If fork() returns -1, then a failure to create a child object has occurred
        printf("Failed to create child process.");
        return 0;
    }

    if(fork_val > 0){ // If a PID was assigned to fork_val
        printf("PPID: %d,  ", getpid()); //Print the parent process's ID
        printf("PID: %d,  \n", fork_val); //Print the child's process's ID
    }

    waitpid(fork_val,&status,WUNTRACED | WCONTINUED); // The parent process stops right here, and waits until the child process has finished running.  The parent then continues.

    getInfo(fork_val,status);
    getTimes(fork_val,buf);

    return 0;
}

void getInfo(pid_t fork_val, int status) //Both the parent and the child use this function to report its process information.
{
    if(fork_val > 0){
        printf("PPID: %d,  ", getppid());
        printf("PID: %d,  ", getpid());
        printf("CPID: %d,  ", fork_val);
        if(WIFEXITED(status))
            printf("RETVAL: %d\n",WEXITSTATUS(status));
    }

    return;


}
void getTimes(pid_t fork_val,struct tms buf) //Finds and print the user time and system time for both the parent and child processes.  Also prints time(NULL) afterwards.
{

    if(fork_val > 0){ //If a PID was assigned to fork_val, then print the user time and system time for each processes.
        printf("USER:  %ld,  ", buf.tms_utime);
        printf(" SYS: %ld\n", buf.tms_stime);
        printf("CUSER: %ld,  ", buf.tms_cutime);
        printf("CSYS: %ld\n", buf.tms_cstime);
        printf("STOP: %ld\n",time(NULL));
    }
    return;
}


