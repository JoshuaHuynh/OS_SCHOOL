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
#include <string.h>
#include <fcntl.h>
#include<errno.h>


struct aiocb aio;
struct aiocb aiow;
char one[5];
int rows;
int cols;

void matrix_add(int curBlock[rows][cols],int block_size,int scalar); //This function adds a scalar to the block passed to this function.

int main(int argc, char* const argv[])
{
    (void)argc;
    srand(time(NULL));
    int theSign = rand() % 2; //This variable is to determine whether the integer in the matrix is to be negative or posiitive.
    int oneOrZero = rand() % 2; //Since the way I create random numbers only generate numbers between 0 to 99, I need to add 1 to be able to reach 100.
    int block_size = 0;
    int blocks = 0;
    int size1 = 0; //Size of matrix, as in size by size.
    int scalar = (rand() % 100) + oneOrZero; //Scalar can be any number in the range -100 to 100.
    int x,y,i,j;
    int curSize = 0; //The current number of elements in the block. Also, used to determining when to go to a new line in the matrix.
    size_t n;
    char current[200]; //The current number or element that the while-loop is on.
    char one[5]; //Used to hold one character. (The loop reads on character at a time, so this char array holds the current character the loop is on.
    time_t startTime,endTime,timeFinish;
    int offNum = 0; //Used for iterating or traversing through the file being read from.  This is the offset number.
    int stop = 0; //Indicates when the loop finished forming a block.
    int blockRow = 0, blockCol = 0;
    char numPrint[200] = ""; //Used to hold a string or number to be printed on a file.
    long temp;
    off_t offW = 0; //Offset for aio_write.


    if (theSign == 0)
        scalar = scalar * 1;
    else if(theSign == 1)
        scalar = scalar * -1;

    long num = strtol(argv[1],NULL,10); //Changes argv[1] from string to number.
    size1 = (int)num;

    long num2 = strtol(argv[2],NULL,10); //Changes argv[2] from string to number.
    blocks = (int)num2;

    block_size = size1/blocks;

    rows = block_size;
    cols = block_size;

    int curBlock[block_size][block_size];

    memset(&aio,0,sizeof(struct aiocb));
    aio.aio_fildes = STDIN_FILENO;
    aio.aio_buf = one;
    aio.aio_nbytes = 1;
    aio.aio_offset = 0;

    memset(&aiow,0,sizeof(struct aiocb));
    aiow.aio_fildes = STDOUT_FILENO;

    aiow.aio_offset = 0;

    startTime = time(NULL); //Get the current time.

    for(x = 0; x < blocks; x++){ //These two for-loops iterate or traverse through each block in the matrix read from the file.
        for(y = 0; y < blocks; y++){
            strcpy(current,"");
            while(aio_read(&aio) == 0){ //This loop reads the matrix from the file. Inside this loop, the current block is being formed by being put into a two dimensional array.
                aio_return(&aio);
                while(aio_error(&aio) == EINPROGRESS){ //Waiting until the read request is done.

                }
                if (strcmp(one,"0") == 0 || strcmp(one,"1") == 0|| strcmp(one,"2") == 0|| strcmp(one,"3") == 0|| strcmp(one,"4") == 0|| strcmp(one,"5") == 0|| strcmp(one,"6") == 0|| strcmp(one,"7") == 0|| strcmp(one,"8") == 0|| strcmp(one,"9") == 0|| strcmp(one,"-") == 0){
                    strcat(current,one);
                }
                else if(strcmp(one,"\n") == 0 || strcmp(one," ") == 0){
                    temp = strtol(current,NULL,10);
                    curBlock[blockRow][blockCol] = (int)temp;

                    blockCol++;
                    if(blockCol == block_size){
                        blockRow++;
                        blockCol = 0;
                    }
                    strcpy(current,"");

                    stop++;
                }

                offNum++;
                aio.aio_offset = (off_t)offNum;

                if(stop == (block_size *block_size)){
                    blockRow = 0;
                    blockCol = 0;
                    stop = 0;
                    break;

                }
            }

            matrix_add(curBlock,block_size,scalar);

            for(i = 0; i < block_size; i++){ //These two for-loops ultimately prints the current block onto a file.
                for(j = 0; j < block_size; j++){
                    curSize++;
                    if(curSize == size1){
                        curSize = 0;
                        sprintf(numPrint,"%d\n",curBlock[i][j]);
                    }
                    else{
                        sprintf(numPrint,"%d ",curBlock[i][j]);
                    }
                    aiow.aio_buf = numPrint;
                    n = strlen(numPrint);
                    aiow.aio_nbytes = n + ((size_t)block_size * (size_t)block_size);

                    offW = offW + (off_t)strlen(numPrint);
                    aio_write(&aiow);
                    aio_return(&aiow);
                    while(aio_error(&aiow) == EINPROGRESS){

                    }


                    aiow.aio_offset = offW;

                }
            }

        }

    }

    endTime = time(NULL);

    timeFinish = endTime - startTime;

    fprintf(stderr,"Amount of time to perform operation: %ld\n",timeFinish); //Emits the time taken to complete the process.
    return 0;
}



void matrix_add(int curBlock[rows][cols],int block_size,int scalar)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < block_size ; i++){
        for(j = 0; j < block_size ; j++){
            curBlock[i][j] = curBlock[i][j] + scalar;
        }
    }
}


