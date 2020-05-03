//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

//Global variable
int loop_breaker = 0; //For breaking out of infinite loop


//Functions
void eat(int philPosition);//Philosopher eats for a random amount of time after successfully acquiring two chopsticks
void think(int philPosition);//Philosopher thinking and consuming a random amount of time after putting down two chopsticks.
void signalHandler(int y); //User made function for handling signals.  Breaks the infinite loop.

sem_t * returnVal;

int main(int argc,char* const argv[])
{
    (void)argc;
    int status; //For wait()
    int errorNum = 0; //To check if a problem occured with sem_open(), sem_close(), etc.
    size_t numOfDigits = 0; //Number of digits in the number of seats
    int count = 0; // count of the number of full eat-think cycles

    pid_t processId = getpid();
    setpgid(processId,getpgid(processId)); //Create a new process group

    signal(SIGTERM,signalHandler); //Registers a handler for SIGTERM
    signal(SIGTERM,signalHandler); //Registers a handler for SIGTERM

    long num = strtol(argv[1],NULL,10); //Seats
    long num2 = strtol(argv[2],NULL,10); //Position

    int numChopsticks = (int)num; // Number of chopsticks
    int philPosition = (int)num2; //Seat number of philosopher
    sem_t*  chopstick[numChopsticks]; //Chopsticks

    numOfDigits = strlen(argv[1]);

    char semNames[num][10 + ((int)numOfDigits)];// This array is for holding semaphore names.
    char name[10 + ((int)numOfDigits)]; //Name of semaphore
    char temp[10 + ((int)numOfDigits)];
    strcpy(temp,"/");

    int i = 0;
    while(i < numChopsticks){// This loop creates a name for each semaphore. This loop also allocates a named semaphore for each chopstick.
        sprintf(name,"semaphore%d", i);
        strcpy(semNames[i],name);
        strcat(temp,semNames[i]);
        returnVal = sem_open(temp,O_CREAT|O_EXCL,0666,1);
        strcpy(temp,"/");
        chopstick[i] = returnVal;
        if (returnVal == SEM_FAILED) {

            returnVal = sem_open(semNames[i], 0);
            chopstick[i] = returnVal;
        }

        i++;
    }


    //In the following do-while loop, an odd-numbered philosopher picks up first her left chopstick and then her right chopstick,
    //whereas an even numbered philosopher picks up her right chopstick and then her left chopstick.
    do {

        /////////////////// Entering Critical section
        if((philPosition % 2) == 0){
            sem_wait(chopstick[(philPosition+1) % numChopsticks]); //Pick up second chopstick
            sem_wait(chopstick[philPosition]);//Pick up first chopstick
        }
        else if((philPosition % 2) != 0){
            sem_wait(chopstick[philPosition]);//Pick up first chopstick
            sem_wait(chopstick[(philPosition+1) % numChopsticks]); //Pick up second chopstick
        }

        eat(philPosition); //Philosopher eats for a random amount of time.


        if((philPosition % 2) == 0){
            sem_post(chopstick[(philPosition+1) % numChopsticks]); //Release second chopstick
            sem_post(chopstick[philPosition]);//Release first chopstick
        }
        else if((philPosition % 2) != 0){
            sem_post(chopstick[philPosition]);//Release first chopstick
            sem_post(chopstick[(philPosition+1) % numChopsticks]); //Release second chopstick
        }


        think(philPosition); //Philosopher thinks for a random amount of time.

        //////////////////// Exiting critical section

        if(loop_breaker == 1) //For breaking out of loop.
            break;

        count++;
    } while (1);


    while ((wait(&status)) > 0); //Waits for all children.


    i = 0;
    while(i < numChopsticks){
        errorNum = sem_close(chopstick[i]);
        if(errorNum == -1){ //Checking to see if there were any problems closing the semaphore.
            perror("sem_close");
        }

        errorNum = 0;
        strcat(temp,semNames[i]);
        errorNum = sem_unlink(semNames[i]);
        strcpy(temp,"/");

        i++;
    }

    fprintf(stderr,"Philosopher #%d completed %d cycles\n",(int)philPosition,count);

    return 0;

}

void eat(int philPosition)
{
    printf("Philosopher #%d is eating\n", philPosition);
    unsigned int x = rand();
    useconds_t sec = (useconds_t)x;
    useconds_t lim = 999999;
    useconds_t usec1 = (sec % (useconds_t)lim);
    usleep((usec1));
}

void think(int philPosition)
{
    printf("Philosopher #%d is thinking\n",philPosition);
    unsigned int x = rand();
    useconds_t sec = (useconds_t)x;
    useconds_t lim = 999999;
    useconds_t usec1 = (sec % (useconds_t)lim);
    usleep((usec1));

}

void signalHandler(int y) //User made function for handling signals
{
    if(y == 15)
        loop_breaker = 1;

}

