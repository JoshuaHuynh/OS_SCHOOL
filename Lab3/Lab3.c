//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h> //For time()
#include <sys/types.h> //For getpid(),kill()
#include <unistd.h> //For getpid(), pause()
#include <sys/wait.h>
#include <sys/times.h>
#include <signal.h> //For signal()
#include <string.h>
#include <ctype.h>

//Global variable
int loop_breaker = 0;

//Functions
void signalHandler(int y); //User made function for handling signals
void register_handler(char *signals[],int signalNum, int argc); //Registers a handler for each argument twice.
char* getSigName(int signalNum,char name[]); //Returns name of signal number


int main(int argc, char* const argv[])
{
    if (argc == 1){ //If user did not input anything for the command line arguments, then end the program.
        printf("There are no command line arguments.\n");
        return 0;
    }

    char* signals[argc - 1];


    int signalNum = 0;

    fprintf(stderr,"catcher: $$ = %d\n",getpid());
    int x = 0;
    int i = 1;
    while(i < argc){ // Putting the list of signals into the signals array.


        signals[x] = argv[i];

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



//******************************************
void signalHandler(int y) //User made function for handling signals
{
    static int count = 0; //This variable is for counting the total number of signals caught
    static int count3 = 0; //This variable is used to count how many successive SIGTERM signals has happened
    char name[100];

    if(y == 15) //This branch adds 1 to the variable count3 if the signal is SIGTERM.
        count3++;
    else // This branch sets count3 to 0 if the signal is not SIGTERM
        count3 = 0;


    count++;
    printf("%s caught at %ld\n", getSigName(y,name),time(NULL));

    if(y != 0)
        count++;


    if(count3 == 3){
        fprintf(stderr,"catcher: Total signals count = %d\n",(count/2));
        loop_breaker = 1; //Return or go back to the main function
    }


}
//***************************************************

void register_handler(char *signals[],int signalNum, int argc) //Registers a handler for each argument twice.
{
    int i = 0;
    while(i < (argc - 1)){ //This loop registers a handler for each argument
        if(strcmp(signals[i],"HUP") == 0)
            signalNum = 1;
        else if(strcmp(signals[i],"INT") == 0)
            signalNum = 2;
        else if(strcmp(signals[i],"QUIT") == 0)
            signalNum = 3;
        else if(strcmp(signals[i],"ILL") == 0)
            signalNum = 4;
        else if(strcmp(signals[i],"TRAP") == 0)
            signalNum = 5;
        else if(strcmp(signals[i],"ABRT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"IOT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"BUS") == 0)
            signalNum = 7;
        else if(strcmp(signals[i],"FPE") == 0)
            signalNum = 8;
        else if(strcmp(signals[i],"USR1") == 0)
            signalNum = 10;
        else if(strcmp(signals[i],"SEGV") == 0)
            signalNum = 11;
        else if(strcmp(signals[i],"USR2") == 0)
            signalNum = 12;
        else if(strcmp(signals[i],"PIPE") == 0)
            signalNum = 13;
        else if(strcmp(signals[i],"ALRM") == 0)
            signalNum = 14;
        else if(strcmp(signals[i],"TERM") == 0)
            signalNum = 15;
        else if(strcmp(signals[i],"STKFLT") == 0)
            signalNum = 16;
        else if(strcmp(signals[i],"CHLD") == 0)
            signalNum = 17;
        else if(strcmp(signals[i],"CONT") == 0)
            signalNum = 18;
        else if(strcmp(signals[i],"TSTP") == 0)
            signalNum = 20;
        else if(strcmp(signals[i],"TTIN") == 0)
            signalNum = 21;
        else if(strcmp(signals[i],"TTOU") == 0)
            signalNum = 22;
        else if(strcmp(signals[i],"URG") == 0)
            signalNum = 23;
        else if(strcmp(signals[i],"XCPU") == 0)
            signalNum = 24;
        else if(strcmp(signals[i],"XFSZ") == 0)
            signalNum = 25;
        else if(strcmp(signals[i],"VTALRM") == 0)
            signalNum = 26;
        else if(strcmp(signals[i],"PROF") == 0)
            signalNum = 27;
        else if(strcmp(signals[i],"WINCH") == 0)
            signalNum = 28;
        else
            signalNum = 0;

        signal(signalNum,signalHandler);
        i++;
    }


    i = 0;
    while(i < (argc - 1)){ //Register a handler for each argument again.
        if(strcmp(signals[i],"HUP") == 0)
            signalNum = 1;
        else if(strcmp(signals[i],"INT") == 0)
            signalNum = 2;
        else if(strcmp(signals[i],"QUIT") == 0)
            signalNum = 3;
        else if(strcmp(signals[i],"ILL") == 0)
            signalNum = 4;
        else if(strcmp(signals[i],"TRAP") == 0)
            signalNum = 5;
        else if(strcmp(signals[i],"ABRT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"IOT") == 0)
            signalNum = 6;
        else if(strcmp(signals[i],"BUS") == 0)
            signalNum = 7;
        else if(strcmp(signals[i],"FPE") == 0)
            signalNum = 8;
        else if(strcmp(signals[i],"USR1") == 0)
            signalNum = 10;
        else if(strcmp(signals[i],"SEGV") == 0)
            signalNum = 11;
        else if(strcmp(signals[i],"USR2") == 0)
            signalNum = 12;
        else if(strcmp(signals[i],"PIPE") == 0)
            signalNum = 13;
        else if(strcmp(signals[i],"ALRM") == 0)
            signalNum = 14;
        else if(strcmp(signals[i],"TERM") == 0)
            signalNum = 15;
        else if(strcmp(signals[i],"STKFLT") == 0)
            signalNum = 16;
        else if(strcmp(signals[i],"CHLD") == 0)
            signalNum = 17;
        else if(strcmp(signals[i],"CONT") == 0)
            signalNum = 18;
        else if(strcmp(signals[i],"TSTP") == 0)
            signalNum = 20;
        else if(strcmp(signals[i],"TTIN") == 0)
            signalNum = 21;
        else if(strcmp(signals[i],"TTOU") == 0)
            signalNum = 22;
        else if(strcmp(signals[i],"URG") == 0)
            signalNum = 23;
        else if(strcmp(signals[i],"XCPU") == 0)
            signalNum = 24;
        else if(strcmp(signals[i],"XFSZ") == 0)
            signalNum = 25;
        else if(strcmp(signals[i],"VTALRM") == 0)
            signalNum = 26;
        else if(strcmp(signals[i],"PROF") == 0)
            signalNum = 27;
        else if(strcmp(signals[i],"WINCH") == 0)
            signalNum = 28;
        else
            signalNum = 0;

        signal(signalNum,signalHandler);
        i++;
    }



}
//**********************************************

char* getSigName(int signalNum, char name[])
{


        if(signalNum == 1)
            strcpy(name,"SIGHUP");
        else if(signalNum == 2)
            strcpy(name,"SIGINT");
        else if(signalNum == 3)
            strcpy(name,"SIGQUIT");
        else if(signalNum == 4)
            strcpy(name,"SIGILL");
        else if(signalNum == 5)
            strcpy(name,"SIGTRAP");
        else if(signalNum == 6)
            strcpy(name,"SIGABRT");
        else if(signalNum == 6)
            strcpy(name,"SIGIOT");
        else if(signalNum == 7)
            strcpy(name,"SIGBUS");
        else if(signalNum == 8)
            strcpy(name,"SIGFPE");
        else if(signalNum == 10)
            strcpy(name,"SIGUSR1");
        else if(signalNum == 11)
            strcpy(name,"SIGSEGV");
        else if(signalNum == 12)
            strcpy(name,"SIGUSR2");
        else if(signalNum == 13)
            strcpy(name,"SIGPIPE");
        else if(signalNum == 14)
            strcpy(name,"SIGALRM");
        else if(signalNum == 15)
            strcpy(name,"SIGTERM");
        else if(signalNum == 16)
            strcpy(name,"SIGSTKFLT");
        else if(signalNum == 17)
            strcpy(name,"SIGCHLD");
        else if(signalNum == 18)
            strcpy(name,"SIGCONT");
        else if(signalNum == 20)
            strcpy(name,"SIGTSTP");
        else if(signalNum == 21)
            strcpy(name,"SIGTTIN");
        else if(signalNum == 22)
            strcpy(name,"SIGTTOU");
        else if(signalNum == 23)
            strcpy(name,"SIGURG");
        else if(signalNum == 24)
            strcpy(name,"SIGXCPU");
        else if(signalNum == 25)
            strcpy(name,"SIGXFSZ");
        else if(signalNum == 26)
            strcpy(name,"SIGVTALRM");
        else if(signalNum == 27)
            strcpy(name,"SIGPROF");
        else if(signalNum == 28)
            strcpy(name,"SIGWINCH");
        else
            strcpy(name,"");

        return name;

}

