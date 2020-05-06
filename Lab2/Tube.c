//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> //For waitpid()
#include <unistd.h> //For execve()
#include <sys/wait.h> // For waitpid()
#include <sys/times.h>
#include <string.h>

//Functions
int find_comma(int argc, char* const argv[]);
void fill_up(char *buf1[],char *buf2[],int comma_pos,int argc, char* const argv[]); //Assign the elements of the first half of argv to an array.  Assign the elements of the 2nd half of argv to another array.

int main(int argc, char* const argv[])
{
    int pipefd[2];
    int status;
    int status2;
    int comma_pos = 0; //The index of where the comma is located in argv.
    int last_argv = argc - 1;

    if (argc == 1){ //If user did not input anything for the command line arguments, then end the program.
        printf("There are no command line arguments. Please input them.\n");
        return 0;
    }

    if(pipe(pipefd) == -1){ //If there is an error with the pipe
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    comma_pos = find_comma(argc,argv);

    char *buf1[comma_pos];
    char *buf2[last_argv - comma_pos + 1];
    char *newenviron[] = {NULL};

    fill_up(buf1,buf2,comma_pos,argc,argv);


    pid_t fork_val = fork();

    if(fork_val > 0){ //Parent
        fprintf(stderr,"%s: $$ = %d\n",argv[1], fork_val); // Print PID of first child on stderr
        close(pipefd[0]); //Close access to read end of pipe
        close(pipefd[1]); //Close access to write end of pipe

        pid_t fork_val2 = fork();



        if(fork_val2 > 0){
            fprintf(stderr,"%s: $$ = %d\n",argv[4], fork_val2); //Print PID of second child on stderr
            waitpid(fork_val,&status,WUNTRACED | WCONTINUED);
            printf("\n");
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
        else if(fork_val2 == -1){
            perror("fork");
            exit(EXIT_FAILURE);
        }


    }
    else if(fork_val == 0){ //Child
        dup2(pipefd[0],STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execve(argv[1],buf1,newenviron);
        perror("execve"); //Error checking.
        exit(EXIT_FAILURE);

    }
    else if(fork_val == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(WIFEXITED(status))
        fprintf(stderr,"\n%s:  $? = %d\n",argv[1], WEXITSTATUS(status));
    if(WIFEXITED(status2))
        fprintf(stderr,"%s:  $? = %d\n",argv[comma_pos + 1], WEXITSTATUS(status2));


    printf("\n");

    return 0;

}

int find_comma(int argc, char* const argv[])
{
    unsigned int i = 0;
    int vIndex = 1;
    int comma_pos = 0;
    while (vIndex < argc){ //This loop is to find the comma position

        while(i < strlen(argv[vIndex])){

            if(argv[vIndex][i] == ',' &&  strlen(argv[vIndex]) == 1)
                comma_pos = vIndex;
            i++;
        }
        i = 0;
        vIndex++;
    }
    return comma_pos;
}

void fill_up(char *buf1[],char *buf2[],int comma_pos,int argc, char* const argv[])
{
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
}
