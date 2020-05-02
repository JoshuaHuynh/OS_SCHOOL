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
sem_t mutex;// A semaphore that acts as a mutex.

int main(int argc,char* const argv[])
{
    (void)argc;
    int status;
    int errorNum;
    pid_t processId = getpid();
    setpgid(processId,getpgid(processId));

    signal(SIGTERM,signalHandler); //Registers a handler for SIGTERM
    signal(SIGTERM,signalHandler); //Registers a handler for SIGTERM

    int count = 0; // count of the number of full eat-think cycles
    long num = strtol(argv[1],NULL,10); //Seats
    long num2 = strtol(argv[2],NULL,10); //Position

    int numChopsticks = num; // Number of chopsticks

    sem_t temp[numChopsticks];
    sem_t*  chopstick[numChopsticks]; //Chopsticks

    errorNum = sem_init(&mutex,1,1);
    if(errorNum == -1){ //Checking to see if there were any problems creating the semaphore.
        perror("sem_init");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while(i < numChopsticks){
        errorNum = sem_init(&temp[i],1,1);
        if(errorNum == -1){ //Checking to see if there were any problems creating the semaphore.
            perror("sem_init");
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    while(i < numChopsticks){ //Allocate a semaphore for each chopstick
        chopstick[i] = &temp[i];
        i++;
    }


    do {

        sem_wait(&mutex);
        /////////////////// Entering Critical section
        sem_wait(chopstick[num2]);//Pick up first chopstick
        sem_wait(chopstick[(num2+1) % numChopsticks]); //Pick up second chopstick


        eat(num2);


        sem_post(chopstick[num2]); //Release first chopstick
        sem_post(chopstick[(num2+1) % numChopsticks]); //Release second chopstick


        think(num2);

        //////////////////// Exiting critical section
        sem_post(&mutex);

        if(loop_breaker == 1)
            break;

        count++;
    } while (1);

    while ((wait(&status)) > 0); //Waits for all children.

    i = 0;
    while(i < numChopsticks){
        errorNum = sem_destroy(chopstick[i]);
        if(errorNum == -1){ //Checking to see if there were any problems destroying the semaphore.
            perror("sem_destroy");
        }
        i++;
    }

    errorNum = sem_destroy(&mutex);
    if(errorNum == -1){ //Checking to see if there were any problems destroying the semaphore.
        perror("sem_destroy");

    }

    fprintf(stderr,"Philosopher #%d completed %d cycles\n",(int)num2,count);


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

