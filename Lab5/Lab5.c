//Joshua Huynh

#include <stdio.h>
#include <stdlib.h> //For strtol()
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <stdint.h> //For uint32_t
#include <ctype.h>


//Functions
void findPageNum(uint32_t virtualAddress); //This function calculates the page number and prints it.
void findOffset(uint32_t virtualAddress); //This function calculates the page offset and prints it.

int main(int argc, char* const argv[])
{
    if (argc == 0){ //If user did not input any numbers in the command line, then end the program.
        printf("Please enter a virtual address.\n");
        return 0;
    }
    unsigned int i = 0;

    while(i < strlen(argv[1])){ // This loop ensures that the user enters only numbers in the command line.
        if(isdigit(argv[1][0]) == 0){ // isdigit() checks if the character is a digit or not.
            printf("Please enter a virtual address in decimal. No characters that are not numbers are allowed.\n");
            return 0;
        }
        i++;
    }

    long num = strtol(argv[1],NULL,10); //Changes argv[1] from string to number.

    uint32_t virtualAddress = (uint32_t)num; // Changes the virtual address from long to uint32_t.

    printf("The address %d contains:\n",virtualAddress); //Prints virtual address through stdout.

    findPageNum(virtualAddress); //Calculates and prints page number through stdout.
    findOffset(virtualAddress); //Calculates and prints page offset through stdout.

    return 0;

}

void findPageNum(uint32_t virtualAddress)
{
    uint32_t pageNum = virtualAddress / (1024 * 4); //One kilobyte is 1024 bytes. The page size is four kilobytes.

    printf("page number = %d\n", pageNum);

    return;

}
void findOffset(uint32_t virtualAddress)
{
    uint32_t offSet = virtualAddress % (1024 * 4);

    printf("offset = %d\n", offSet);

    return;

}

