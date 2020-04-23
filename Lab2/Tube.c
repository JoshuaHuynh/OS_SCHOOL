#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid() and getppid()
#include <unistd.h> //For execve()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()
#include <string.h>


//Descriptions for the functions are on README file.


int main(int argc, char* const argv[])
{
    int pipefd[2];
    int status;
    int status2;


    if(pipe(pipefd) == -1){ //If there is an error with the pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //
    int i = 0;
    int vIndex = 1;
    int comma_pos = 0;
    int last_argv = argc - 1;
    while (vIndex < argc){ //This loop is to find the comma position

        while(i < strlen(argv[vIndex])){

            if(argv[vIndex][i] == ',' &&  strlen(argv[vIndex]) == 1)
                comma_pos = vIndex;
            i++;
        }
        i = 0;
        vIndex++;
    }


    char *buf1[comma_pos];
    char *buf2[last_argv - comma_pos + 1];
    char *newenviron[] = {NULL};

    int x = 0;
    int y = 1;

     while(x < (comma_pos - 1)) // Put the first half (before comma) into array
     {
         buf1[x] = argv[y];
         x++;
         y++;
     }

     buf1[x] = NULL;

     x = 0;
     y = comma_pos + 1;
     while(x < (argc - comma_pos - 1)){ // Put the second half (after comma) into array
        buf2[x] = argv[y];
        x++;
        y++;
     }

     buf2[x] = NULL;

    //

    pid_t fork_val = fork();

    if(fork_val > 0){ //Parent
        fprintf(stderr,"%s: $$ = %d\n",argv[1], fork_val); // Print PID of first child on stderr
        close(pipefd[0]); //Close access to read end of pipe
        close(pipefd[1]); //Close access to write end of pipe

        pid_t fork_val2 = fork();



        if(fork_val2 > 0){
            fprintf(stderr,"%s: $$ = %d\n",argv[4], fork_val2); //Print PID of second child on stderr
            waitpid(fork_val,&status,WUNTRACED | WCONTINUED);
            waitpid(fork_val2,&status2,WUNTRACED | WCONTINUED);
        }
        else if(fork_val2 == 0){ //Child
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[0]);
            close(pipefd[1]);
            execve(argv[comma_pos + 1],buf2,newenviron);

            perror("execve");
            exit(EXIT_FAILURE);


        }

        //write(pipefd[1],);

    }
    else if(fork_val == 0){ //Child
         dup2(pipefd[0],STDIN_FILENO);


        //
         close(pipefd[0]);
         close(pipefd[1]);
         execve(argv[1],buf1,newenviron);

         perror("execve"); //Error checking.
         exit(EXIT_FAILURE);





        //

    }



    return 0;

}
