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


struct aiocb aio;
struct aiocb aiow;
char one[5];
int rows;
int cols;

void matrix_add(int curBlock[rows][cols],int block_size,int scalar);

int main(int argc, char* const argv[])
{
    (void)argc;
    int theSign = rand() % 2;
    int oneOrZero = rand() % 2;
    int block_size = 0;
    int blocks = 0;
    int size1 = 0;
    int scalar = (rand() % 100) + oneOrZero; //Scalar can be any number in the range -100 to 100.
    int x,y,i,j;
    int curSize = 0;
    size_t n;
    char current[200];
    char one[5];
    time_t startTime,endTime,timeFinish;
    int offNum = 0;
    int stop = 0;
    int blockRow = 0, blockCol = 0;
    char numPrint[200] = "";


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
    aiow.aio_buf = numPrint;

    aiow.aio_offset = 0;

    startTime = time(NULL); //Get the current time.

    for(x = 0; x < blocks; x++){
        for(y = 0; y < blocks; y++){
            strcpy(current,"");
            while(aio_read(&aio) == 0){ //This loop breaks after current block is filled up.
                aio_return(&aio);

                if (strcmp(one,"0") == 0 || strcmp(one,"1") == 0|| strcmp(one,"2") == 0|| strcmp(one,"3") == 0|| strcmp(one,"4") == 0|| strcmp(one,"5") == 0|| strcmp(one,"6") == 0|| strcmp(one,"7") == 0|| strcmp(one,"8") == 0|| strcmp(one,"9") == 0|| strcmp(one,"-") == 0){
                    strcat(current,one);
                }
                else if(strcmp(one,"\n") == 0 || strcmp(one," ") == 0){
                    long temp = strtol(current,NULL,10);
                    curBlock[blockRow][blockCol] = (int)temp;
                    if(blockCol == block_size - 1){
                        //if(blockRow != (block_size - 1))
                        blockRow++;
                        blockCol = 0;
                    }

                    blockCol++;
                    stop++;
                }

                aio.aio_offset = offNum + 1;

                if(stop == (block_size *block_size)){
                    blockRow = 0;
                    stop = 0;
                    break;

                }
            }

            matrix_add(curBlock,block_size,scalar);

            for(i = 0; i < block_size; i++){
                for(j = 0; j < block_size; j++){
                    //itoa(curBlock[i][j],numPrint,10);
                    sprintf(numPrint,"%d",curBlock[i][i]);
                    n = strlen(numPrint);
                    aiow.aio_nbytes = (int)n;
                    aio_write(&aiow);
                    aio_return(&aiow);
                    curSize++;

                    printf(" ");
                    if(curSize == size1){
                        curSize = 0;
                        printf("\n");
                    }
                }
            }

        }

    }

    endTime = time(NULL);

    timeFinish = endTime - startTime;

    fprintf(stderr,"%ld",timeFinish);

    return 0;
}



void matrix_add(int curBlock[rows][cols],int block_size,int scalar)
{
    int i = 0;
    int j = 0;

    for(i = 0; i < block_size; i++){
        for(j = 0; j < block_size; j++){
            curBlock[i][j] = curBlock[i][j] + scalar;
        }
    }
}


