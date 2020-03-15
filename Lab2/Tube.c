#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid() and getppid()
#include <unistd.h> //For execve()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()


//Descriptions for the functions are on README file.


int main(int argc, char* const argv[])
{
    int pipefd[2];


    if(pipe(pipefd) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t fork_val = fork();


    if(fork_val > 0){
        fprintf(stderr,"%s: $$ = %d\n",argv[1], fork_val);
        pid_t fork_val2 = fork();

        if(fork_val2 > 0){
            fprintf(stderr,"%s: $$ = %d\n",argv[3], fork_val2);
        }

        else if(fork_val2 == 0)

        write(pipefd[1],)

    }
    else if(fork_val == 0)




}
