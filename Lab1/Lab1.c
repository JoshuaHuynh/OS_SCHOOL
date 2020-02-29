//Name: Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid() and getppid()
#include <unistd.h> //For getpid() and getppid()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()

void getInfo(pid_t fork_val,int status);

int main()
{
    struct tms buf;
    times(&buf);
    int status;
    printf("START: %ld\n",time(NULL));

    pid_t fork_val = fork();
    if(fork_val == -1)
    {
        printf("Failed to create child process.");
        return 0;
    }

    waitpid(fork_val,&status,0);

    if(fork_val > 0){
        printf("PPID: %d,  ", getpid());
        printf("PID: %d,  \n", fork_val);
    }

    getInfo(fork_val,status);

    if(fork_val > 0){
        printf("USER:  %ld,  ", buf.tms_utime);
        printf(" SYS: %ld\n", buf.tms_stime);
        printf("CUSER: %ld,  ", buf.tms_cutime);
        printf("CSYS: %ld,\n",buf.tms_cstime);
        printf("STOP: %ld\n",time(NULL));
    }

    return 0;
}

void getInfo(pid_t fork_val, int status)
{


    if(fork_val > 0){
        printf("PPID: %d,  ", getppid());
        printf("PID: %d,  ", getpid());
        printf("CPID: %d,", fork_val);
        printf("RETVAL: %d\n",status);
    }

    return;


}


