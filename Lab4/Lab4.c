//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h> //For waitpid
#include <unistd.h> //For execve() and fork()
#include <sys/wait.h> // For waitpid
#include <string.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>



int loop_breaker = 0;



//Functions
void eat(int philPosition);//Philosopher eat after successfully acquiring two chopsticks
void think(int philPosition);//Philosopher thinking and consuming time when not holding any chopsticks
void signalHandler(int y); //User made function for handling signals

int main(int argc, char* const argv[])
{
    int count = 0; // count of the number of full eat-think cycles
    long num = strtol(argv[1],NULL,10); //Seats
    long num2 = strtol(argv[2],NULL,10) //Position

    int numChopsticks = ((num - 1) *2) + 1; // Number of chopsticks (enough for n - 1 philosophers when there are n philosophers

    sem_t * chopstick[numChopsticks]; //Chopsticks

    sem_t* theSemaphore;
    theSemaphore = sem_open("/semaphore1",O_CREAT|O_EXCL,0666, 1);

    int i = 0;
    while(i < numChopsticks){
        sem_init(chopstick[i],0,1);
        i++;
    }

    do {


        sem_wait(theSemaphore);
        /////////////////// Entering Critical section
        sem_wait(chopstick[num2]);//Pick up first chopstick
        sem_wait(chopstick[(num2+1) % numChopsticks]); //Pick up second chopstick

        /* eat for awhile */
        eat(num2);


        sem_post(chopstick[num2]); //Release first chopstick
        sem_post(chopstick[(num2+1) % numChopsticks]); //Release second chopstick

        /* think for awhile */
        think(num2);

        //////////////////// Exiting critical section
        sem_post(theSemaphore);

        if(loop_breaker == 1)
            break;

        count++;
    } while (true);

    i = 0;
    while(i < numChopsticks){
        sem_init(chopstick[i]);
        i++;
    }

    sem_close(theSemaphore);
    sem_unlink("/semaphore1");

    fprintf(stderr,"Philosopher #%d completed %d cycles",num2,count);


    return 0;


}

void eat(int philPosition)
{

    printf("Philosopher #%d is eating", philPosition);
    unsigned int x = rand();
    usleep(x);
}
void think(int philPosition)
{
    printf("Philosopher #%d is thinking",philPosition);
    unsigned int x = rand();
    usleep(x);

}
void signalHandler(int y) //User made function for handling signals
{
    if(y == 15)
        loop_breaker = 1;



}

