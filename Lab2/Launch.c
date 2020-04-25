//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> //For waitpid
#include <unistd.h> //For execve() and fork()
#include <sys/wait.h> // For waitpid
#include <sys/times.h>
#include <string.h>


//Functions
void newargv_func(int argc, char* const argv[], char *newargv1[]);//Prepares the new argv structure
void execve_func(char* const argv[], char *newargv1[]);//Executes the supplied command

int main(int argc, char* const argv[])
{
    int status; //This int variable will be used to find the return status or value of the child process.
    char *newargv1[argc - 1];

    pid_t fork_val = fork(); //Create child process

    if(fork_val > 0){ //On the parent process, print the child process ID through stderr
        fprintf(stderr,"%s: $$ = %d\n",argv[1], fork_val);
    }
    else if(fork_val == 0){//If child process, then......

        newargv_func(argc,argv,newargv1); //Prepares the new argv structure
        execve_func(argv,newargv1); //Executes the supplied command
        if(argc < 2){

            printf("Invalid input.\n");
            return 0;
        }
    }
    else if(fork_val == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    waitpid(fork_val,&status,WUNTRACED | WCONTINUED); //Parent process waits for child process to finish

    if(WIFEXITED(status)) //Get the return value of the child and print it on stderr.
        fprintf(stderr,"%s: $? = %d\n",argv[1], WEXITSTATUS(status));

    fprintf(stderr,"$\n\n");

    return 0;

}

void newargv_func(int argc, char* const argv[], char *newargv1[])
{
    int x = 0;
    int y = 1;

    while(y < argc){
        newargv1[x] = argv[y];
        x++;
        y++;
    }
    newargv1[x] = NULL;

    return;
}
void execve_func(char* const argv[], char *newargv1[])
{
    char *newenviron[] = {NULL};
    execve(argv[1],newargv1,newenviron);

    perror("execve"); //Error checking.
    exit(EXIT_FAILURE);
    return;

}
