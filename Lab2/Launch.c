//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid() and getppid()
#include <unistd.h> //For execve()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()


//Descriptions for the functions are on README file.
void execve_func(int argc, char* const argv[]);

int main(int argc, char* const argv[])
{
    int status; //This int variable will be used to find the return status or value of the child process.

    pid_t fork_val = fork(); //Create child process

    if(fork_val > 0) //On the parent process, print the child process ID on stderr
        fprintf(stderr,"%s: $$ = %d\n",argv[1], fork_val);

    if(fork_val == 0){//If child process, then......

        execve_func(argc,argv); //Executes the supplied command

        if(argc < 2 || argc > 6)
        {
            printf("Invalid input.\n");
            return 0;
        }
    }

    waitpid(fork_val,&status,WUNTRACED | WCONTINUED); //Parent process waits for child process to finish

    if(WIFEXITED(status)) //Get the return value of the child and print it on stderr.
        fprintf(stderr,"%s: $? = %d\n",argv[1], WEXITSTATUS(status));

    printf("$\n\n");

    return 0;

}

void execve_func(int argc, char* const argv[])
{
        char *newargv1[] = {argv[1],NULL}; //This array is used if there is only two command line argument
        char *newargv2[] = {argv[1],argv[2],NULL}; //This array is used if there is only three command line argument
        char *newargv3[] = {argv[1],argv[2],argv[3],NULL}; //This array is used if there is only four command line argument
        char *newargv4[] = {argv[1],argv[2],argv[3],argv[4],NULL}; //This array is used if there is only five command line argument
        char *newargv5[] = {argv[1],argv[2],argv[3],argv[4],argv[5],NULL}; //This array is used if there is only six command line argument

        char *newenviron[] = {NULL};

        if (argc == 2) //Executes the supplied command when there are two command line arguments
            execve(argv[1],newargv1, newenviron);
        else if(argc == 3) //Executes the supplied command when there are three command line arguments
            execve(argv[1],newargv2, newenviron);
        else if (argc == 4)//Executes the supplied command when there are four command line arguments
            execve(argv[1],newargv3, newenviron);
        else if(argc == 5)
            execve(argv[1],newargv4, newenviron);
        else if(argc == 6)
            execve(argv[1],newargv5, newenviron);


        perror("execve"); //Error checking.
        exit(EXIT_FAILURE);
        return;
}
