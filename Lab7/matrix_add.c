//Name: Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <aio.h>
#include <ctype.h>

struct aiocb aio;
char one[1];
int offNum = 0;
int main(int argc, char* const argv[])
{

    int theSign = rand() % 2;
    int oneOrZero = rand() % 2;
    int block_size = 0;
    int blocks = 0;
    int size1 = 0;
    int scalar = (rand() % 100) + oneOrZero; //Scalar can be any number in the range -100 to 100.
    int x;
    int y;
    char number[200];
    time_t startTime,endTime,timeFinish;


    if (theSign == 0)
        scalar = scalar * 1;
    else if(theSign == 1)
        scalar = scalar * -1;

    long num = strtol(argv[1],NULL,10); //Changes argv[1] from string to number.
    size1 = (int)num;

    long num2 = strtol(argv[2],NULL,10); //Changes argv[2] from string to number.
    blocks = (int)num2;

    int elements[size1][size1];

    int totalBlocks = blocks * blocks;

    block_size = size1/blocks;


    char buf1[block_size * 2];
    memset(&aio,0,sizeof(struct aio));
    aio.aio_fildes = STDIN_FILENO;
    aio.aio_buf = one;
    aio.aio_nbytes = 1;
    aio.aio_offset = 0;



    startTime = time(NULL); //Get the current time.


    for(x = 1; x < blocks; x++){
        for(y = 1; y < blocks; y++){



        }
    }
    endTime = time(NULL);

    timeFinish = endTime - startTime;

    fprintf(stderr,"%ld",timeFinish);

    return 0;
}

void newLine()
{
    while(aio_read(&aio) == 0){
        if(one[0] == '\n'){
            aio.aio_offset = offNum + 1;//Stops at beginning of new line.
            aio_return(&aio);
            break;
        }
        aio.aio_offset = offNum++;
        aio_return(&aio);

    }
}

void nextBlock(int x, int block_size)
{
    int stop = 0;
    while(aio_read(&aio) == 0){
        if(one[0] == ' ' || one[0] == '\n'){
            stop++;
        }
        if(stop == block_size){//Stopped at the beginning of the number to read in the next block.
            aio_return(&aio);
            break;

        }
        aio.aio_offset = offNum++;
        aio_return(&aio);
    }
}




