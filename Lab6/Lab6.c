//Joshua Huynh

#include <stdio.h>
#include <stdlib.h> //For strtol()
#include <time.h> //For getrlimit()
#include <sys/types.h>
#include <unistd.h> //For setsid(), fork(), chdir(), and dup()
#include <sys/time.h>
#include <string.h>
#include <stdint.h> //For uint32_t
#include <ctype.h>
#include <sys/stat.h> //For umask()
#include <sys/resource.h> //For getrlimit()
#include <signal.h> // For signal()
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

struct rlimit rlim;
int loop_breaker = 0; //For breaking out of infinite loop.
int createMole = 0; //If equal to 1, then create mole in the infinite loop in main.
int moleExisting = 0; //For checking if mole1 or mole2 is existing. If 1, then mole1 exists. If 2, then mole2 exists. If 0, then no mole exists.
pid_t molePid; //Process Id of mole.

//Functions
void registerHandler(); //Registers handler for each signal.  The signals are SIGTERM,SIGUSR1, and SIGUSR2.
void signalHandler(int y);


int main(int argc, char* const argv[])
{
    (void)argc;
    (void) argv;
    mode_t mask = 0;
    int errorNum = 0; //For checking for errors.
    unsigned int i = 0;
    int moleNum = 0; //The mole's number.
    int status;  //For wait()
    char* buf1[2]; //For execv()
    buf1[1] = NULL;
    char oldDirectory[4000]; //For storing the directory before changing the process's directory to "/".

    getcwd(oldDirectory, sizeof(oldDirectory)); //Get current directory.


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

    errorNum = chdir("/"); //Change process's directory to "/".
    if(errorNum == -1){
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    errorNum = getrlimit(RLIMIT_NOFILE, &rlim);
    if(errorNum == -1){
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    if(rlim.rlim_max == RLIM_INFINITY) //If rlim_max is RLIM_INFINITY, then set rlim_max to 1024. (As shown from the Unix programming book.)
        rlim.rlim_max = 1024;

    while(i < rlim.rlim_max){ //Close all unneeded file descriptors. (Similar to what was shown in the Unix programming book. )
        close(i);
        i++;
    }

    open("/dev/null",O_RDWR); //Reopen the standard file descriptors to map to /dev/null. (Similar to what was shown from the Unix programming book.)
    dup(0);
    dup(0);


    registerHandler(); //Registers handler for each signal.  The signals are SIGTERM,SIGUSR1, and SIGUSR2.

    while(1){
        pause();

        if(loop_breaker == 1) //For breaking out of infinite loop
            break;
        if(createMole == 1){ //This section of code is to create mole1 or mole2.
            createMole = 0;
            moleNum = rand();
            moleNum = moleNum % 2;
            moleNum = moleNum + 1;
            if(moleExisting == 0){ //If no mole currently exists....
                molePid = fork();
                moleExisting = moleNum;
                if(molePid > 0){

                }
                else if(molePid == 0){ //Child process.
                    chdir(oldDirectory); //Change process directory back to current working directory.
                    if(errorNum == -1){
                        perror("chdir");
                        exit(EXIT_FAILURE);
                    }
                    if(moleNum == 1){
                        buf1[0] = "mole1";
                    }
                    else if(moleNum == 2){
                        buf1[0] = "mole2";
                    }

                    errorNum = execv("./mole",buf1); //Exec the program mole
                    if(errorNum == -1){
                        perror("execv"); //Error checking.
                        exit(EXIT_FAILURE);
                    }
                    chdir("/"); //Change directory back to "/"
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
        if(moleExisting == 1){
            kill(molePid,SIGTERM); //Kill child process 1
            moleExisting = 0; //No mole currently existing

        }
        createMole = 1; //In the infinite loop in main, create a mole.

    }

    if(y == SIGUSR2){
        if(moleExisting == 2){
            kill(molePid,SIGTERM); //Kill child process 2
            moleExisting = 0; //No mole currently existing
        }
        createMole = 1; //In the infinite loop in main, create a mole.

    }

    return;

}



