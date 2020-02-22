#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv)
{

    //
    int numc = 1;
    int x = 0;
    int way = 0;
    char temp[8];

    if(argv[1][0] != '-'){ // If argv starts does not start with -

        numc = 1;
        while (numc < argc){ //Iterate through the binary numbers

            while(x < strlen(argv[numc])){ //Iterate through the binary number set

                if(argv[numc][x] != '1' && argv[numc][x] != '0') //Check if there is anything that is not one or zero
                    way = 1;
                x++;
            }
            x = 0;
            numc++;
        }
    }
    else if(argv[1][0] == '-'){ //If argv starts with -

        numc = 2;
        while (numc < argc){ //Iterate through the binary numbers

            while(x < strlen(argv[numc])){ //Iterate through the binary number set

                if(argv[numc][x] != '1' && argv[numc][x] != '0') //Check if there is anything that is not one or zero
                    way = 1;
                x++;
            }
            x = 0;
            numc++;
        }
    }

    if(argc == 0 || argc == 1){ // Checking for command line arguments

        printf("%s","Error. Invalid input.\n");
        return 0;
    }
    else if(argc == 2 && argv[1][0] == '-' && strlen(argv[1]) < 2){ //Checking for command line arguments after -

        printf("%s","Error. Invalid input.\n");
        return 0;
    }



    if(way == 0){  // If there are only ones and zeros.


        if(argv[1][0] == '-'){ //If there only ones and zeros, but the beginning has a -

            numc = 2;
            int par_check = 0;
            int parity[argc];
            int dec[argc];
            char asc[argc];
            char asc_beg[6];
            int po = 7;
            int sum = 0;
            x = 0;
            int z  = 0;
            while (numc < argc){ //Iterate through the binary numbers

                while(x < strlen(argv[numc])){ // iterate through binary number set and calculate the decimal for that set

                    if(argv[numc][x] == '1'){

                        if(x == 0){

                           par_check++;
                        }
                        else{

                            sum = sum + pow(2,po);
                            par_check++;
                        }
                    }
                    x++;
                    po--;
                }

                asc[numc] = sum;
                if(isascii(sum) != 1){

                    printf("Error. Please input ASCII values only.\n");
                    return 0;
                }

                dec[numc] = sum;
                parity[numc] = par_check % 2;
                par_check = 0;
                sum = 0;
                po = 7;
                x = 0;
                numc++;

            }

            printf("Original     ASCII       Decimal   Parity\n");
            printf("--------     --------    --------  --------\n");
            char even[5] = "EVEN";
            char odd[4] = "ODD";
            x = 0;
            numc = 2;
            int remain = 0;

            while(numc < argc){ //Iterate through the binary numbers

                printf("%s",argv[numc]); //Print the binary number set

                if(strlen(argv[numc]) < 8) // Calculates how much digits are missing from the 8 digit set
                    remain = 8 - strlen(argv[numc]);

                while(x < remain){ //Pad with zeros if binary number set is less than 8 digits

                    printf("%d",0);
                    x++;
                }


                if(parity[numc] == 0){

                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], even);
                    else{

                        if(dec[numc] >= 0 && dec[numc] <= 32){

                            if(dec[numc] == 0)
                                strcpy(asc_beg,"NUL");
                            else if(dec[numc] == 1)
                                strcpy(asc_beg,"SOH");
                            else if(dec[numc] == 2)
                                strcpy(asc_beg,"STX");
                            else if(dec[numc] == 3)
                                strcpy(asc_beg,"ETX");
                            else if(dec[numc] == 4)
                                strcpy(asc_beg,"EOT");
                            else if(dec[numc] == 5)
                                strcpy(asc_beg,"ENQ");
                            else if(dec[numc] == 6)
                                strcpy(asc_beg,"ACK");
                            else if(dec[numc] == 7)
                                strcpy(asc_beg,"BEL");
                            else if(dec[numc] == 8)
                                strcpy(asc_beg,"BS");
                            else if(dec[numc] == 9)
                                strcpy(asc_beg,"HT");
                            else if(dec[numc] == 10)
                                strcpy(asc_beg,"LF");
                            else if(dec[numc] == 11)
                                strcpy(asc_beg,"VT");
                            else if(dec[numc] == 12)
                                strcpy(asc_beg,"FF");
                            else if(dec[numc] == 13)
                                strcpy(asc_beg,"CR");
                            else if(dec[numc] == 14)
                                strcpy(asc_beg,"SO");
                            else if(dec[numc] == 15)
                                strcpy(asc_beg,"SI");
                            else if(dec[numc] == 16)
                                strcpy(asc_beg,"DLE");
                            else if(dec[numc] == 17)
                                strcpy(asc_beg,"DC1");
                            else if(dec[numc] == 18)
                                strcpy(asc_beg,"DC2");
                            else if(dec[numc] == 19)
                                strcpy(asc_beg,"DC3");
                            else if(dec[numc] == 20)
                                strcpy(asc_beg,"DC4");
                            else if(dec[numc] == 21)
                                strcpy(asc_beg,"NAK");
                            else if(dec[numc] == 22)
                                strcpy(asc_beg,"SYN");
                            else if(dec[numc] == 23)
                                strcpy(asc_beg,"ETB");
                            else if(dec[numc] == 24)
                                strcpy(asc_beg,"CAN");
                            else if(dec[numc] == 25)
                                strcpy(asc_beg,"EM");
                            else if(dec[numc] == 26)
                                strcpy(asc_beg,"SUB");
                            else if(dec[numc] == 27)
                                strcpy(asc_beg,"ESC");
                            else if(dec[numc] == 28)
                                strcpy(asc_beg,"FS");
                            else if(dec[numc] == 29)
                                strcpy(asc_beg,"GS");
                            else if(dec[numc] == 30)
                                strcpy(asc_beg,"RS");
                            else if(dec[numc] == 31)
                                strcpy(asc_beg,"US");
                            else if(dec[numc] == 32)
                                strcpy(asc_beg,"SPACE");
                            else if(isascii(dec[numc]) != 1){

                                printf("Error. Please input ASCII values only.\n");
                                return 0;
                            }
                        }
                        printf("        %5s      %4d    %4s",asc_beg, dec[numc], even);
                    }
                }
                else if (parity[numc] != 0){

                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], odd);
                    else{

                        if(dec[numc] >= 0 && dec[numc] <= 32){

                            if(dec[numc] == 0)
                                strcpy(asc_beg,"NUL");
                            else if(dec[numc] == 1)
                                strcpy(asc_beg,"SOH");
                            else if(dec[numc] == 2)
                                strcpy(asc_beg,"STX");
                            else if(dec[numc] == 3)
                                strcpy(asc_beg,"ETX");
                            else if(dec[numc] == 4)
                                strcpy(asc_beg,"EOT");
                            else if(dec[numc] == 5)
                                strcpy(asc_beg,"ENQ");
                            else if(dec[numc] == 6)
                                strcpy(asc_beg,"ACK");
                            else if(dec[numc] == 7)
                                strcpy(asc_beg,"BEL");
                            else if(dec[numc] == 8)
                                strcpy(asc_beg,"BS");
                            else if(dec[numc] == 9)
                                strcpy(asc_beg,"HT");
                            else if(dec[numc] == 10)
                                strcpy(asc_beg,"LF");
                            else if(dec[numc] == 11)
                                strcpy(asc_beg,"VT");
                            else if(dec[numc] == 12)
                                strcpy(asc_beg,"FF");
                            else if(dec[numc] == 13)
                                strcpy(asc_beg,"CR");
                            else if(dec[numc] == 14)
                                strcpy(asc_beg,"SO");
                            else if(dec[numc] == 15)
                                strcpy(asc_beg,"SI");
                            else if(dec[numc] == 16)
                                strcpy(asc_beg,"DLE");
                            else if(dec[numc] == 17)
                                strcpy(asc_beg,"DC1");
                            else if(dec[numc] == 18)
                                strcpy(asc_beg,"DC2");
                            else if(dec[numc] == 19)
                                strcpy(asc_beg,"DC3");
                            else if(dec[numc] == 20)
                                strcpy(asc_beg,"DC4");
                            else if(dec[numc] == 21)
                                strcpy(asc_beg,"NAK");
                            else if(dec[numc] == 22)
                                strcpy(asc_beg,"SYN");
                            else if(dec[numc] == 23)
                                strcpy(asc_beg,"ETB");
                            else if(dec[numc] == 24)
                                strcpy(asc_beg,"CAN");
                            else if(dec[numc] == 25)
                                strcpy(asc_beg,"EM");
                            else if(dec[numc] == 26)
                                strcpy(asc_beg,"SUB");
                            else if(dec[numc] == 27)
                                strcpy(asc_beg,"ESC");
                            else if(dec[numc] == 28)
                                strcpy(asc_beg,"FS");
                            else if(dec[numc] == 29)
                                strcpy(asc_beg,"GS");
                            else if(dec[numc] == 30)
                                strcpy(asc_beg,"RS");
                            else if(dec[numc] == 31)
                                strcpy(asc_beg,"US");
                            else if(dec[numc] == 32)
                                strcpy(asc_beg,"SPACE");
                            else if(isascii(dec[numc]) != 1){

                                printf("Error. Please input ASCII values only.\n");
                                return 0;
                            }
                        }
                        printf("        %5s      %4d    %4s",asc_beg, dec[numc], odd);
                    }

                }

                printf("\n");

                x = 0;
                remain = 0;
                numc++;

            }

        }
        else if(argv[1][0] != '-'){

            numc = 1;
            int par_check = 0;
            int parity[argc];
            int dec[argc];
            char asc[argc];
            char asc_beg[6];
            int po = 7;
            int sum = 0;
            x = 0;
            int z  = 0;
            while (numc < argc){ // Iterate through the binary numbers

                while(x < strlen(argv[numc])){ // iterate through binary number set and calculate the decimal for that set

                    if(argv[numc][x] == '1'){

                        if(x == 0){

                           par_check++;
                        }
                        else{

                            sum = sum + pow(2,po);
                            par_check++;
                        }
                    }
                    x++;
                    po--;
                }

                asc[numc] = sum;
                if(isascii(sum) != 1){

                    printf("Error. Please input ASCII values only.\n");
                    return 0;
                }

                dec[numc] = sum;
                parity[numc] = par_check % 2;
                par_check = 0;
                sum = 0;
                po = 7;
                x = 0;
                numc++;
                strcpy(asc_beg,"");

            }

            printf("Original    ASCII       Decimal   Parity\n");
            printf("--------    --------    --------  --------\n");
            char even[5] = "EVEN";
            char odd[4] = "ODD";
            x = 0;
            numc = 1;
            int remain = 0;

            while(numc < argc){ //Iterate through the binary numbers

                printf("%s",argv[numc]); //Print the binary number set

                if(strlen(argv[numc]) < 8) // Calculates how much digits are missing from the 8 digit set
                    remain = 8 - strlen(argv[numc]);

                while(x < remain){ //Pad with zeros if binary number set is less than 8 digits

                    printf("%d",0);
                    x++;
                }


                if(parity[numc] == 0){

                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], even);
                    else{

                        if(dec[numc] >= 0 && dec[numc] <= 32){

                            if(dec[numc] == 0)
                                strcpy(asc_beg,"NUL");
                            else if(dec[numc] == 1)
                                strcpy(asc_beg,"SOH");
                            else if(dec[numc] == 2)
                                strcpy(asc_beg,"STX");
                            else if(dec[numc] == 3)
                                strcpy(asc_beg,"ETX");
                            else if(dec[numc] == 4)
                                strcpy(asc_beg,"EOT");
                            else if(dec[numc] == 5)
                                strcpy(asc_beg,"ENQ");
                            else if(dec[numc] == 6)
                                strcpy(asc_beg,"ACK");
                            else if(dec[numc] == 7)
                                strcpy(asc_beg,"BEL");
                            else if(dec[numc] == 8)
                                strcpy(asc_beg,"BS");
                            else if(dec[numc] == 9)
                                strcpy(asc_beg,"HT");
                            else if(dec[numc] == 10)
                                strcpy(asc_beg,"LF");
                            else if(dec[numc] == 11)
                                strcpy(asc_beg,"VT");
                            else if(dec[numc] == 12)
                                strcpy(asc_beg,"FF");
                            else if(dec[numc] == 13)
                                strcpy(asc_beg,"CR");
                            else if(dec[numc] == 14)
                                strcpy(asc_beg,"SO");
                            else if(dec[numc] == 15)
                                strcpy(asc_beg,"SI");
                            else if(dec[numc] == 16)
                                strcpy(asc_beg,"DLE");
                            else if(dec[numc] == 17)
                                strcpy(asc_beg,"DC1");
                            else if(dec[numc] == 18)
                                strcpy(asc_beg,"DC2");
                            else if(dec[numc] == 19)
                                strcpy(asc_beg,"DC3");
                            else if(dec[numc] == 20)
                                strcpy(asc_beg,"DC4");
                            else if(dec[numc] == 21)
                                strcpy(asc_beg,"NAK");
                            else if(dec[numc] == 22)
                                strcpy(asc_beg,"SYN");
                            else if(dec[numc] == 23)
                                strcpy(asc_beg,"ETB");
                            else if(dec[numc] == 24)
                                strcpy(asc_beg,"CAN");
                            else if(dec[numc] == 25)
                                strcpy(asc_beg,"EM");
                            else if(dec[numc] == 26)
                                strcpy(asc_beg,"SUB");
                            else if(dec[numc] == 27)
                                strcpy(asc_beg,"ESC");
                            else if(dec[numc] == 28)
                                strcpy(asc_beg,"FS");
                            else if(dec[numc] == 29)
                                strcpy(asc_beg,"GS");
                            else if(dec[numc] == 30)
                                strcpy(asc_beg,"RS");
                            else if(dec[numc] == 31)
                                strcpy(asc_beg,"US");
                            else if(dec[numc] == 32)
                                strcpy(asc_beg,"SPACE");

                            else if(isascii(dec[numc]) != 1){

                                printf("Error. Please input ASCII values only.\n");
                                return 0;
                            }
                        }
                        printf("        %5s      %4d    %4s",asc_beg, dec[numc], even);
                    }
                }
                else if (parity[numc] != 0){

                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], odd);
                    else{

                        if(dec[numc] >= 0 && dec[numc] <= 32){

                            if(dec[numc] == 0)
                                strcpy(asc_beg,"NUL");
                            else if(dec[numc] == 1)
                                strcpy(asc_beg,"SOH");
                            else if(dec[numc] == 2)
                                strcpy(asc_beg,"STX");
                            else if(dec[numc] == 3)
                                strcpy(asc_beg,"ETX");
                            else if(dec[numc] == 4)
                                strcpy(asc_beg,"EOT");
                            else if(dec[numc] == 5)
                                strcpy(asc_beg,"ENQ");
                            else if(dec[numc] == 6)
                                strcpy(asc_beg,"ACK");
                            else if(dec[numc] == 7)
                                strcpy(asc_beg,"BEL");
                            else if(dec[numc] == 8)
                                strcpy(asc_beg,"BS");
                            else if(dec[numc] == 9)
                                strcpy(asc_beg,"HT");
                            else if(dec[numc] == 10)
                                strcpy(asc_beg,"LF");
                            else if(dec[numc] == 11)
                                strcpy(asc_beg,"VT");
                            else if(dec[numc] == 12)
                                strcpy(asc_beg,"FF");
                            else if(dec[numc] == 13)
                                strcpy(asc_beg,"CR");
                            else if(dec[numc] == 14)
                                strcpy(asc_beg,"SO");
                            else if(dec[numc] == 15)
                                strcpy(asc_beg,"SI");
                            else if(dec[numc] == 16)
                                strcpy(asc_beg,"DLE");
                            else if(dec[numc] == 17)
                                strcpy(asc_beg,"DC1");
                            else if(dec[numc] == 18)
                                strcpy(asc_beg,"DC2");
                            else if(dec[numc] == 19)
                                strcpy(asc_beg,"DC3");
                            else if(dec[numc] == 20)
                                strcpy(asc_beg,"DC4");
                            else if(dec[numc] == 21)
                                strcpy(asc_beg,"NAK");
                            else if(dec[numc] == 22)
                                strcpy(asc_beg,"SYN");
                            else if(dec[numc] == 23)
                                strcpy(asc_beg,"ETB");
                            else if(dec[numc] == 24)
                                strcpy(asc_beg,"CAN");
                            else if(dec[numc] == 25)
                                strcpy(asc_beg,"EM");
                            else if(dec[numc] == 26)
                                strcpy(asc_beg,"SUB");
                            else if(dec[numc] == 27)
                                strcpy(asc_beg,"ESC");
                            else if(dec[numc] == 28)
                                strcpy(asc_beg,"FS");
                            else if(dec[numc] == 29)
                                strcpy(asc_beg,"GS");
                            else if(dec[numc] == 30)
                                strcpy(asc_beg,"RS");
                            else if(dec[numc] == 31)
                                strcpy(asc_beg,"US");
                            else if(dec[numc] == 32)
                                strcpy(asc_beg,"SPACE");

                            else if(isascii(dec[numc]) != 1){

                                printf("Error. Please input ASCII values only.\n");
                                return 0;
                            }
                        }
                        printf("        %5s      %4d    %4s",asc_beg, dec[numc], odd);
                    }

                }

                printf("\n");

                x = 0;
                remain = 0;
                numc++;

            }


        }
    }


    ///////////////

    else if(way == 1){

        int BUFFER_SIZE = 100;
        int i = 0;
        char bufr[BUFFER_SIZE];
        char bufset[100];

        int fd = open(argv[1], O_RDONLY);

        if(fd == -1){

            printf("Error. Invalid input.\n");
            return 0;
        }

        printf("Original    ASCII       Decimal   Parity\n");
        printf("--------    --------    --------  --------\n");

        int sum1 = 0;
        int y = 0;
        int exp = 7;
        int bit_i = 0;
        int par_check1 = 0;
        int remain1 = 0;
        char even1[5] = "EVEN";
        char odd1[5] = "ODD";
        char asc_val[6];
        char asc_char;

        int n;
        n = read(fd, bufr, BUFFER_SIZE);
        i = 0;


        while(n == BUFFER_SIZE){ //If file size is bigger than buffer size, read again

            while(i <BUFFER_SIZE){ //Scan through bufr for spaces

                if(!isspace(bufr[i])){ // Print set when a space is found

                    bufset[bit_i] = bufr[i];
                    printf("%c",bufset[bit_i]);
                    bit_i++;
                    i++;
                }
                else{ // When isspace

                    if(bit_i < 7){

                        remain1 = 8 - (bit_i);

                        while(y < remain1){ //If binary number is less than 8 digits, pad with zeros.

                            printf("%c",'0');
                            y++;
                        }

                    }

                    y = 0;
                    while(y < bit_i){

                        if(bufset[y] == '1'){

                            if(y == 0){

                                par_check1++;
                            }
                            else{

                                sum1 = sum1 + pow(2,exp);
                                par_check1++;
                            }
                        }

                        y++;
                        exp--;
                    }


                    if(isascii(sum1) != 1){

                        printf("Error. Please input ASCII values only.\n");
                        return 0;
                    }

                    asc_char = sum1;

                    if(sum1 >= 0 && sum1 <= 32){

                        if(sum1 == 0)
                            strcpy(asc_val,"NUL");
                        else if(sum1 == 1)
                            strcpy(asc_val,"SOH");
                        else if(sum1 == 2)
                            strcpy(asc_val,"STX");
                        else if(sum1 == 3)
                            strcpy(asc_val,"ETX");
                        else if(sum1 == 4)
                            strcpy(asc_val,"EOT");
                        else if(sum1 == 5)
                            strcpy(asc_val,"ENQ");
                        else if(sum1 == 6)
                            strcpy(asc_val,"ACK");
                        else if(sum1 == 7)
                            strcpy(asc_val,"BEL");
                        else if(sum1 == 8)
                            strcpy(asc_val,"BS");
                        else if(sum1 == 9)
                            strcpy(asc_val,"HT");
                        else if(sum1 == 10)
                            strcpy(asc_val,"LF");
                        else if(sum1 == 11)
                            strcpy(asc_val,"VT");
                        else if(sum1 == 12)
                            strcpy(asc_val,"FF");
                        else if(sum1 == 13)
                            strcpy(asc_val,"CR");
                        else if(sum1 == 14)
                            strcpy(asc_val,"SO");
                        else if(sum1 == 15)
                            strcpy(asc_val,"SI");
                        else if(sum1 == 16)
                            strcpy(asc_val,"DLE");
                        else if(sum1 == 17)
                            strcpy(asc_val,"DC1");
                        else if(sum1 == 18)
                            strcpy(asc_val,"DC2");
                        else if(sum1 == 19)
                            strcpy(asc_val,"DC3");
                        else if(sum1 == 20)
                            strcpy(asc_val,"DC4");
                        else if(sum1 == 21)
                            strcpy(asc_val,"NAK");
                        else if(sum1 == 22)
                            strcpy(asc_val,"SYN");
                        else if(sum1 == 23)
                            strcpy(asc_val,"ETB");
                        else if(sum1 == 24)
                            strcpy(asc_val,"CAN");
                        else if(sum1 == 25)
                            strcpy(asc_val,"EM");
                        else if(sum1 == 26)
                            strcpy(asc_val,"SUB");
                        else if(sum1 == 27)
                            strcpy(asc_val,"ESC");
                        else if(sum1 == 28)
                            strcpy(asc_val,"FS");
                        else if(sum1 == 29)
                            strcpy(asc_val,"GS");
                        else if(sum1 == 30)
                            strcpy(asc_val,"RS");
                        else if(sum1 == 31)
                            strcpy(asc_val,"US");
                        else if(sum1 == 32)
                            strcpy(asc_val,"SPACE");
                    }

                    if((par_check1 % 2) == 0){


                        if(sum1 >= 0 && sum1 <= 32)
                            printf("        %5s      %4d    %4s", asc_val, sum1, even1);
                        else
                            printf("        %5c      %4d    %4s", asc_char, sum1, even1);
                    }
                    else{

                        if(sum1 >= 0 && sum1 <= 32)
                            printf("        %5s      %4d    %4s",asc_val , sum1, odd1);
                        else
                            printf("        %5c      %4d    %4s",asc_char , sum1, odd1);
                    }

                    printf("\n");

                    par_check1 = 0;
                    sum1 = 0;
                    exp = 7;
                    y = 0;
                    bit_i = 0;
                    remain1 = 0;
                    i++;

                }

            }


            n = read(fd, bufr, BUFFER_SIZE);
        }

        ////////////
        /*
        int a = 0;
        par_check1 = 0;
        sum1 = 0;
        exp = 7;
        y = 0;
        bit_i = 0;
        remain1 = 0;
        */
        i = 0;

        while(i < n){ // If n >0 and < BUFFER_SIZE, then...

            //a++;

            if(!isspace(bufr[i])){ // Scan through bufr for spaces

                bufset[bit_i] = bufr[i];
                printf("%c",bufset[bit_i]);
                bit_i++;
                i++;

            }

            else{

                    if(bit_i < 7){ // If there is less than 8 bits in the binary number...

                        remain1 = 8 - (bit_i);

                        while(y < remain1){ //If binary number is less than 8 digits, pad with zeros.

                            printf("%c",'0');
                            y++;
                        }
                        printf("pie");

                    }

                    y = 0;
                    while(y < bit_i){

                        if(bufset[y] == '1'){

                            if(y == 0){

                                par_check1++;
                            }
                            else {

                                sum1 = sum1 + pow(2,exp);
                                par_check1++;
                            }
                        }

                            y++;
                            exp--;
                    }


                    if(isascii(sum1) != 1){

                        printf("Error. Please input ASCII values only.\n");
                        return 0;
                    }

                    asc_char = sum1;

                    if(sum1 >= 0 && sum1 <= 32){

                        if(sum1 == 0)
                            strcpy(asc_val,"NUL");
                        else if(sum1 == 1)
                            strcpy(asc_val,"SOH");
                        else if(sum1 == 2)
                            strcpy(asc_val,"STX");
                        else if(sum1 == 3)
                            strcpy(asc_val,"ETX");
                        else if(sum1 == 4)
                            strcpy(asc_val,"EOT");
                        else if(sum1 == 5)
                            strcpy(asc_val,"ENQ");
                        else if(sum1 == 6)
                            strcpy(asc_val,"ACK");
                        else if(sum1 == 7)
                            strcpy(asc_val,"BEL");
                        else if(sum1 == 8)
                            strcpy(asc_val,"BS");
                        else if(sum1 == 9)
                            strcpy(asc_val,"HT");
                        else if(sum1 == 10)
                            strcpy(asc_val,"LF");
                        else if(sum1 == 11)
                            strcpy(asc_val,"VT");
                        else if(sum1 == 12)
                            strcpy(asc_val,"FF");
                        else if(sum1 == 13)
                            strcpy(asc_val,"CR");
                        else if(sum1 == 14)
                            strcpy(asc_val,"SO");
                        else if(sum1 == 15)
                            strcpy(asc_val,"SI");
                        else if(sum1 == 16)
                            strcpy(asc_val,"DLE");
                        else if(sum1 == 17)
                            strcpy(asc_val,"DC1");
                        else if(sum1 == 18)
                            strcpy(asc_val,"DC2");
                        else if(sum1 == 19)
                            strcpy(asc_val,"DC3");
                        else if(sum1 == 20)
                            strcpy(asc_val,"DC4");
                        else if(sum1 == 21)
                            strcpy(asc_val,"NAK");
                        else if(sum1 == 22)
                            strcpy(asc_val,"SYN");
                        else if(sum1 == 23)
                            strcpy(asc_val,"ETB");
                        else if(sum1 == 24)
                            strcpy(asc_val,"CAN");
                        else if(sum1 == 25)
                            strcpy(asc_val,"EM");
                        else if(sum1 == 26)
                            strcpy(asc_val,"SUB");
                        else if(sum1 == 27)
                            strcpy(asc_val,"ESC");
                        else if(sum1 == 28)
                            strcpy(asc_val,"FS");
                        else if(sum1 == 29)
                            strcpy(asc_val,"GS");
                        else if(sum1 == 30)
                            strcpy(asc_val,"RS");
                        else if(sum1 == 31)
                            strcpy(asc_val,"US");
                        else if(sum1 == 32)
                            strcpy(asc_val,"SPACE");
                    }

                    if((par_check1 % 2) == 0){

                        if(sum1 >= 0 && sum1 <= 32)
                            printf("        %5s      %4d    %4s", asc_val, sum1, even1);
                        else
                            printf("        %5c      %4d    %4s", asc_char, sum1, even1);
                    }
                    else {

                        if(sum1 >= 0 && sum1 <= 32)
                            printf("        %5s      %4d    %4s",asc_val , sum1, odd1);
                        else
                            printf("        %5c      %4d    %4s",asc_char , sum1, odd1);
                    }

                    printf("\n");

                    par_check1 = 0;
                    sum1 = 0;
                    exp = 7;
                    y = 0;
                    bit_i = 0;
                    i++;
            }

        }

        //*****************************

        if(bit_i < 7){ // If there is less than 8 bits in the binary number...

            remain1 = 8 - (bit_i);

            while(y < remain1){ //If binary number is less than 8 digits, pad with zeros.

                printf("%c",'0');
                y++;
            }

        }

        y = 0;
        while(y < bit_i){

            if(bufset[y] == '1'){

                if(y == 0){

                    par_check1++;
                }
                else{

                    sum1 = sum1 + pow(2,exp);
                    par_check1++;
                }
            }

            y++;
            exp--;
        }

                    //asc[numc] = sum;
        if(isascii(sum1) != 1){

            printf("Error. Please input ASCII values only.\n");
            return 0;
        }

        asc_char = sum1;

        if(sum1 >= 0 && sum1 <= 32){

            if(sum1 == 0)
                strcpy(asc_val,"NUL");
            else if(sum1 == 1)
                strcpy(asc_val,"SOH");
            else if(sum1 == 2)
                strcpy(asc_val,"STX");
            else if(sum1 == 3)
                strcpy(asc_val,"ETX");
            else if(sum1 == 4)
                strcpy(asc_val,"EOT");
            else if(sum1 == 5)
                strcpy(asc_val,"ENQ");
            else if(sum1 == 6)
                strcpy(asc_val,"ACK");
            else if(sum1 == 7)
                strcpy(asc_val,"BEL");
            else if(sum1 == 8)
                strcpy(asc_val,"BS");
            else if(sum1 == 9)
                strcpy(asc_val,"HT");
            else if(sum1 == 10)
                strcpy(asc_val,"LF");
            else if(sum1 == 11)
                strcpy(asc_val,"VT");
            else if(sum1 == 12)
                strcpy(asc_val,"FF");
            else if(sum1 == 13)
                strcpy(asc_val,"CR");
            else if(sum1 == 14)
                strcpy(asc_val,"SO");
            else if(sum1 == 15)
                strcpy(asc_val,"SI");
            else if(sum1 == 16)
                strcpy(asc_val,"DLE");
            else if(sum1 == 17)
                strcpy(asc_val,"DC1");
            else if(sum1 == 18)
                strcpy(asc_val,"DC2");
            else if(sum1 == 19)
                strcpy(asc_val,"DC3");
            else if(sum1 == 20)
                strcpy(asc_val,"DC4");
            else if(sum1 == 21)
                strcpy(asc_val,"NAK");
            else if(sum1 == 22)
                strcpy(asc_val,"SYN");
            else if(sum1 == 23)
                strcpy(asc_val,"ETB");
            else if(sum1 == 24)
                strcpy(asc_val,"CAN");
            else if(sum1 == 25)
                strcpy(asc_val,"EM");
            else if(sum1 == 26)
                strcpy(asc_val,"SUB");
            else if(sum1 == 27)
                strcpy(asc_val,"ESC");
            else if(sum1 == 28)
                strcpy(asc_val,"FS");
            else if(sum1 == 29)
                strcpy(asc_val,"GS");
            else if(sum1 == 30)
                strcpy(asc_val,"RS");
            else if(sum1 == 31)
                strcpy(asc_val,"US");
            else if(sum1 == 32)
                strcpy(asc_val,"SPACE");
        }

        if((par_check1 % 2) == 0){


            if(sum1 >= 0 && sum1 <= 32)
                printf("        %5s      %4d    %4s", asc_val, sum1, even1);
            else
                printf("        %5c      %4d    %4s", asc_char, sum1, even1);
        }
        else{

            if(sum1 >= 0 && sum1 <= 32)
                printf("        %5s      %4d    %4s",asc_val , sum1, odd1);
            else
                printf("        %5c      %4d    %4s",asc_char , sum1, odd1);
        }

        printf("\n");

        par_check1 = 0;
        sum1 = 0;
        exp = 7;
        y = 0;
        bit_i = 0;
        i++;



    }

    return 0;

}
