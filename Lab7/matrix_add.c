//Name: Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <aio.h>


int main()
{

    int status;
    int theSign = rand() % 2;
    int oneOrZero = rand() % 2;
    int block_size = 0;
    int blocks = 0;
    int size1 = argv[1]
    int scalar = (rand() % 100) + oneOrZero;
    int x;
    int y;
    struct aiocb aio;
    aio.aio_fildes = argv[3];

    if (theSign == 0)
        scalar = scalar * 1;
    else if(theSign == 1)
        scalar = scalar * -1;

    long num = strtol(argv[1],NULL,10); //Changes argv[1] from string to number.
    size1 = (int)num;

    long num2 = strtol(argv[2],NULL,10); //Changes argv[2] from string to number.
    blocks = (int)num2;

    block_size = size1/blocks;


    printf("START: %ld\n",time(NULL)); //prints the number of seconds since the Epoch (00:00:00 UTC, January 1, 1970).

    for(x = 1; x < blocks; x++){
        for(y = 1; y < blocks; y++){

        }
    }
    printf("STOP: %ld\n",time(NULL));

    return 0;
}




