//Joshua Huynh

#include <stdio.h>
#include <stdlib.h> //For strtol()
#include <time.h> //For getrlimit()
#include <sys/types.h>
#include <unistd.h> //For setsid(), fork(), chdir(), and dup()
#include <sys/time.h>
#include <string.h>
#include <stdint.h> //For uint32_t
#include <ctype.h>
#include <sys/stat.h> //For umask()
#include <sys/resource.h> //For getrlimit()
#include <signal.h> // For signal()
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char* const argv[])
{
    (void) argc;
    char directory1[5000];
    strcat(strcpy(directory1,getenv("HOME")), "/lab6.log");
    FILE *logfile = fopen(directory1, "w+"); //Create lab6.log if it doesn't exists. If lab6.log exists, then it will be overwritten.

    fprintf(logfile, "Pop %s\n", argv[0]); //Write in lab6.log.

    return 0;
}
