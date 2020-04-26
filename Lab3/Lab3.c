//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid(),kill()
#include <unistd.h> //For getpid(), pause()
#include <sys/wait.h> // For waitpid
#include <sys/times.h> //For times()
#include <signal.h>
#include <string.h>

//Global variable
int loop_breaker = 0;

//Functions
void signalHandler(int y); //Handler for signals.
void register_handler(char *signals[],int signalNum, int argc); //Registers a handler for each argument twice.

int main(int argc, char* const argv[])
{
    char sigChar[5] = "SIG";
    char *signals[argc - 1];

    int signalNum = 0;

    fprintf(stderr,"catcher: $$ = %d\n",getpid());
    int x = 0;
    int i = 1;
    while(i < argc){ //Concatenate "SIG" in the beginning of each string from the command line argument.
        strcat(sigChar,argv[i]);
        signals[x] = sigChar;
        strcpy(sigChar,"SIG");
        i++;
        x++;
    }


    register_handler(signals,signalNum,argc);

    while(1){

        pause();

        if(loop_breaker == 1)
            break;



    }



    return 0;

}

void signalHandler(int y)
{
    static int count = 0; //This variable is for counting the total number of signals caught
    static int count3 = 0; //This variable is used to count how many successive SIGTERM signals has happened

    if(y == 15) //This branch adds 1 to the variable count3 if the signal is SIGTERM.
        count3++;
    else // This branch sets count3 to 0 if the signal is not SIGTERM
        count3 = 0;


    count++;
    printf("%s caught at %ld\n",strsignal(y),time(NULL));

    if(y != 0)
        count++;

    fprintf(stderr,"catcher: Total signals count = %d",count);

    if(count3 == 3)
        loop_breaker = 1; //Return or go back to the main function
    return;
}

void register_handler(char *signals[],int signalNum, int argc) //Registers a handler for each argument twice.
{
    int i = 0;
    while(i < (argc - 1)){ //This loop registers a handler for each argument
        if(strcmp(signals[i],"SIGHUP") == 0)
            signalNum = 1;
        else if(strcmp(signals[i],"SIGINT") == 0)
            signalNum = 2;
        else if(strcmp(signals[i],"SIGQUIT") == 0)
            signalNum = 3;
        else if(strcmp(signals[i],"SIGILL") == 0)
            signalNum = 4;
        else if(strcmp(signals[i],"SIGTRAP") == 0)
            signalNum = 5;
        else if(strcmp(signals[i],"SIGGABRT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"SIGIOT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"SIGBUS") == 0)
            signalNum = 7;
        else if(strcmp(signals[i],"SIGFPE") == 0)
            signalNum = 8;
        else if(strcmp(signals[i],"SIGUSR1") == 0)
            signalNum = 10;
        else if(strcmp(signals[i],"SIGSEGV") == 0)
            signalNum = 11;
        else if(strcmp(signals[i],"SIGUSR2") == 0)
            signalNum = 12;
        else if(strcmp(signals[i],"SIGPIPE") == 0)
            signalNum = 13;
        else if(strcmp(signals[i],"SIGALRM") == 0)
            signalNum = 14;
        else if(strcmp(signals[i],"SIGTERM") == 0)
            signalNum = 15;
        else if(strcmp(signals[i],"SIGSTKFLT") == 0)
            signalNum = 16;
        else if(strcmp(signals[i],"SIGCHLD") == 0)
            signalNum = 17;
        else if(strcmp(signals[i],"SIGCONT") == 0)
            signalNum = 18;
        else if(strcmp(signals[i],"SIGTSTP") == 0)
            signalNum = 20;
        else if(strcmp(signals[i],"SIGTTIN") == 0)
            signalNum = 21;
        else if(strcmp(signals[i],"SIGTTOU") == 0)
            signalNum = 22;
        else if(strcmp(signals[i],"SIGURG") == 0)
            signalNum = 23;
        else if(strcmp(signals[i],"SIGXCPU") == 0)
            signalNum = 24;
        else if(strcmp(signals[i],"SIGXFSZ") == 0)
            signalNum = 25;
        else if(strcmp(signals[i],"SIGVTALRM") == 0)
            signalNum = 26;
        else if(strcmp(signals[i],"SIGPROF") == 0)
            signalNum = 27;
        else if(strcmp(signals[i],"SIGWINCH") == 0)
            signalNum = 28;
        else
            signalNum = 0;

        signal(signalNum,signalHandler);

        i++;

    }


    i = 0;
    while(i < (argc - 1)){ ////Register a handler for each argument again.
        if(strcmp(signals[i],"SIGHUP") == 0)
            signalNum = 1;
        else if(strcmp(signals[i],"SIGINT") == 0)
            signalNum = 2;
        else if(strcmp(signals[i],"SIGQUIT") == 0)
            signalNum = 3;
        else if(strcmp(signals[i],"SIGILL") == 0)
            signalNum = 4;
        else if(strcmp(signals[i],"SIGTRAP") == 0)
            signalNum = 5;
        else if(strcmp(signals[i],"SIGGABRT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"SIGIOT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"SIGBUS") == 0)
            signalNum = 7;
        else if(strcmp(signals[i],"SIGFPE") == 0)
            signalNum = 8;
        else if(strcmp(signals[i],"SIGUSR1") == 0)
            signalNum = 10;
        else if(strcmp(signals[i],"SIGSEGV") == 0)
            signalNum = 11;
        else if(strcmp(signals[i],"SIGUSR2") == 0)
            signalNum = 12;
        else if(strcmp(signals[i],"SIGPIPE") == 0)
            signalNum = 13;
        else if(strcmp(signals[i],"SIGALRM") == 0)
            signalNum = 14;
        else if(strcmp(signals[i],"SIGTERM") == 0)
            signalNum = 15;
        else if(strcmp(signals[i],"SIGSTKFLT") == 0)
            signalNum = 16;
        else if(strcmp(signals[i],"SIGCHLD") == 0)
            signalNum = 17;
        else if(strcmp(signals[i],"SIGCONT") == 0)
            signalNum = 18;
        else if(strcmp(signals[i],"SIGTSTP") == 0)
            signalNum = 20;
        else if(strcmp(signals[i],"SIGTTIN") == 0)
            signalNum = 21;
        else if(strcmp(signals[i],"SIGTTOU") == 0)
            signalNum = 22;
        else if(strcmp(signals[i],"SIGURG") == 0)
            signalNum = 23;
        else if(strcmp(signals[i],"SIGXCPU") == 0)
            signalNum = 24;
        else if(strcmp(signals[i],"SIGXFSZ") == 0)
            signalNum = 25;
        else if(strcmp(signals[i],"SIGVTALRM") == 0)
            signalNum = 26;
        else if(strcmp(signals[i],"SIGPROF") == 0)
            signalNum = 27;
        else if(strcmp(signals[i],"SIGWINCH") == 0)
            signalNum = 28;
        else
            signalNum = 0;

        signal(signalNum,signalHandler);

        i++;

    }
}

