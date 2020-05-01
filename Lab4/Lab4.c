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
sem_t mutex;
int main(int argc,char* const argv[])
{
    (void)argc;
    int status;
    pid_t processId = getpid();
    setpgid(processId,getpgid(processId));

    signal(SIGTERM,signalHandler);

    int count = 0; // count of the number of full eat-think cycles
    long num = strtol(argv[1],NULL,10); //Seats
    long num2 = strtol(argv[2],NULL,10); //Position

    int numChopsticks = num; // Number of chopsticks

    sem_t temp[numChopsticks];
    sem_t*  chopstick[numChopsticks]; //Chopsticks

    //sem_t* theSemaphore;

    //theSemaphore = sem_open("/semaphore1",O_CREAT|O_EXCL,0666, 1);
    sem_init(&mutex,1,1);



    int i = 0;
    while(i < numChopsticks){
        sem_init(&temp[i],1,1);
        i++;
    }
    i = 0;
    while(i < numChopsticks){
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

    while ((wait(&status)) > 0);

    //waitpid(getpgid(processId),&status,WUNTRACED | WCONTINUED);

    i = 0;
    while(i < numChopsticks){
        sem_destroy(chopstick[i]);
        i++;
    }


    sem_destroy(&mutex);
    //sem_close(theSemaphore);
    //sem_unlink("/semaphore1");

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

