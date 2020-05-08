//Joshua Huynh

#include <stdio.h>
#include <stdlib.h> //For strtol()
#include <time.h> //For getrlimit()
#include <sys/types.h>
#include <unistd.h> //For setsid(), fork(), chdir(), and dup()
#include <sys/times.h>
#include <string.h>
#include <stdint.h> //For uint32_t
#include <ctype.h>
#include <sys/stat.h> //For umask()
#include <resource.h> //For getrlimit()
#include <signal.h> // For signal()

int main(int argc, char* const argv[])
{
    FILE *logfile = fopen("./lab6.log", "w+");

    fprintf(logfile, "Pop %s\n", argv[0]);

    return 0;
}
