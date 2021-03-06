//Name: Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <aio.h>


int main(int argc, char* const argv[])
{
    (void)argc;
    srand(time(NULL));
    int theSign = rand() % 2; //This variable is used to determine whether the integer is negative or not.
    int oneOrZero = rand() % 2;
    int size1 = 0;
    int randNum = 0;

    if (theSign == 0)
        randNum = randNum * 1;
    else if(theSign == 1)
        randNum = randNum * -1;

    long num = strtol(argv[1],NULL,10); //Changes argv[1] from string to number.
    size1 = (int)num;
    int i = 0;
    int y = 0;
    for(i = 0; i < size1; i++){ //These two for-loops will generate a matrix in a file.
        for(y = 0; y < size1; y++){
            randNum = (rand() % 100) + oneOrZero;
            theSign = rand() % 2;
            if (theSign == 0)
                randNum = randNum * 1;
            else if(theSign == 1)
                randNum = randNum * -1;

            printf("%d",randNum);

            if(y < size1 - 1)
                printf(" ");

            if(y == size1 -1)
                printf("\n");
        }
    }


    return 0;
}





