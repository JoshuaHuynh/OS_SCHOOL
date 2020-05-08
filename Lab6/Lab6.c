//Joshua Huynh

#include <stdio.h>
#include <stdlib.h> //For strtol()
#include <time.h> //For getrlimit()
#include <sys/types.h>
#include <unistd.h> //For setsid(), fork(), chdir(), and dup()
#include <sys/times.h>
#include <string.h>
#include <stdint.h> //For uint32_t
#include <ctype.h>
#include <sys/stat.h> //For umask()
#include <resource.h> //For getrlimit()
#include <signal.h> // For signal()

struct rlimit rlim;
int loop_breaker = 0; //For breaking out of infinite loop.
int createMole = 0;
int moleExisting = 0;
pid_t molePid;

//Functions
void registerHandler(); ////Registers handler for each signal.  The signals are SIGTERM,SIGUSR1, and SIGUSR2.
void signalHandler(int y);


int main(int argc, char* const argv[])
{
    mode_t mask = 0;
    int errorNum = 0;
    int fd0,fd1,fd2; //File descriptors
    int i = 0;
    int moleNum = 0;
    int status;
    char mole[6];
    char* buf1[2];


    umask(mask); //Set the file creation mask to 0.

    pid_t fork_val = fork(); //Create child process


    if(fork_val > 0){ //Have the parent exit.
        return 0;
    }
    else if(fork_val == 0){

    }
    else{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    errorNum = setsid(); //Create a new session or process group
    if(errorNum == -1){
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    errorNum = chdir("/");
    if(errorNum == -1){
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    errorNum = getrlimit(RLIMIT_NOFILE, &rlim);
    if(errorNum == -1){
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    if(rlim.rlim_max == RLIM_INFINITY) //If rlim_max is RLIM_INFINITY, then set rlim_max to 1024. (This piece of code is from the Unix programming book.)
        rlim.rlim_max = 1024;

    while(i < rlim.rlim_max){ //Close all unneeded file descriptors. (This piece of code is from the Unix programming book.)
        close(i);
        i++;
    }

    fd0 = open("/dev/null",O_RDWR); //Reopen the standard file descriptors to map to /dev/null
    fd1 = dup(0);
    fd2 = dup(0);


    registerHandler();

    while(1){
        pause();

        if(loop_breaker == 1)
            break;
        if(createMole = 1){
            createMole = 0;
            moleNum = rand();
            moleNum = moleNum % 2;
            moleNum = moleNum + 1;
            if(moleExisting == 0){
                molePid = fork();
                moleExisting = moleNum;
                if(molePid > 0){

                }
                else if(molePid == 0){
                    sprintf(mole,"mole%d", moleNum);
                    strcpy(buf1[0],mole);
                    strcpy(buf1[1],NULL);
                    execv("./mole",buf1);
                }
                else if(molePid == -1){
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

            }


        }


    }

    while ((wait(&status)) > 0); //Waits for all children.


    return 0;

}

void registerHandler()
{
    signal(SIGTERM,signalHandler);
    signal(SIGTERM,signalHandler);

    signal(SIGUSR1,signalHandler);
    signal(SIGUSR1,signalHandler);

    signal(SIGUSR2,signalHandler);
    signal(SIGUSR2,signalHandler);

    return;

}
void signalHandler(int y)
{

    if(y == 15){
        loop_breaker = 1;
    }

    if(y == SIGUSR1){
        if(moleExisting = 1){
            kill(molePid,SIGTERM);
            moleExisting = 0;

        }
        createMole = 1;

    }

    if(y == SIGUSR2){
        if(moleExisting = 2){
            kill(molePid,SIGTERM);
            moleExisting = 0;
        }
        createMole = 1;

    }

    return;

}



