//Joshua Huynh

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //For open()
#include <sys/stat.h>//For open()
#include <fcntl.h> //For open()
#include <unistd.h> //For read() and close()
#include <math.h> //For pow()
#include <string.h> //For strlen() and strcpy()
#include <ctype.h> //For isascii() and isspace()

//Descriptions for the functions are on README file.

char* getMnemonic(int number, char* asc_val); //Takes in a decimal and a char array.  The function then returns the char array with the mnemonic assigned to the array.


int main(int argc, char** argv)
{
    int numc = 1;
    unsigned int x = 0;
    int way = 0;

    if(argc == 1){ // Checking for command line arguments
        printf("%s","Error. Invalid input.\n");
        return 0;
    }

    if(argv[1][0] == '-' &&  strlen(argv[1]) == 1){ //If argv starts with -
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
    else{
        numc = 1;
        while (numc < argc){ //Iterate through the binary numbers
            while(x < strlen(argv[numc])){ //Iterate through the binary number set
                if(argv[numc][x] != '1' && argv[numc][x] != '0') //Check if there is anything that is not one or zero
                    way = 1; //If a char is neither '1' nor '0', then assign 1 to the variable way.
                x++;
            }
            x = 0;
            numc++;
        }
    }


    if(argc == 2 && argv[1][0] == '-' && strlen(argv[1]) == 5){ //Checking if text file is named as -
        printf("%s","Error. Invalid input.\n");
        return 0;
    }
    else if(argc == 2 && argv[1][0] == '-' && strlen(argv[1]) < 2){ //Checking if input is only -
        printf("%s","Error. Invalid input.\n");
        return 0;
    }

    if(way == 0){  //The command line arguments does not contain any files, just binary numbers.
        if(argv[1][0] == '-' &&  strlen(argv[1]) == 1){ //If there only ones and zeros, but the beginning has a -
            numc = 2;
            int par_check = 0;
            int parity[argc];
            int dec[argc];
            char asc[argc];
            char asc_beg[6];
            char temp[6];
            int po = 7; //The exponent.
            int sum = 0;
            x = 0;

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
                if(isascii(sum) != 1){ //If value is not ASCII, then ....
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
            unsigned int remain = 0;

            while(numc < argc){ //Iterate through the binary numbers
                printf("%s",argv[numc]); //Print the binary number set

                if(strlen(argv[numc]) < 8) // Calculates how much digits are missing from the 8 digit set
                    remain = 8 - strlen(argv[numc]);

                while(x < remain){ //Pad with zeros if binary number set is less than 8 digits
                    printf("%d",0);
                    x++;
                }


                if(parity[numc] == 0){ //If parity of the binary number is even
                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], even);
                    else{
                        if(dec[numc] >= 0 && dec[numc] <= 32){  // Assigning mnemonics to the decimal values that don't have ASCII characters
                            strcpy(asc_beg, getMnemonic(dec[numc],temp));

                            if(isascii(dec[numc]) != 1){
                                printf("Error. Please input ASCII values only.\n");
                                return 0;
                            }
                        }
                        printf("        %5s      %4d    %4s",asc_beg, dec[numc], even);
                    }
                }
                else if (parity[numc] != 0){ //If parity is odd then.....
                    if(dec[numc] > 32)
                        printf("        %5c      %4d    %4s",asc[numc], dec[numc], odd);
                    else{
                        if(dec[numc] >= 0 && dec[numc] <= 32){ // Assigning mnemonics to the decimal values that don't have ASCII characters
                            strcpy(asc_beg, getMnemonic(dec[numc],temp));

                            if(isascii(dec[numc]) != 1){
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
            char temp[6];
            int po = 7;
            int sum = 0;
            x = 0;

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
                if(isascii(sum) != 1){ //If value is not ASCII, then...
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

            printf("Original    ASCII       Decimal   Parity\n");
            printf("--------    --------    --------  --------\n");
            char even[5] = "EVEN";
            char odd[4] = "ODD";
            x = 0;
            numc = 1;
            unsigned int remain = 0;

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
                        if(dec[numc] >= 0 && dec[numc] <= 32){  // Assigning mnemonics to the decimal values that don't have ASCII characters
                            strcpy(asc_beg, getMnemonic(dec[numc],temp));

                            if(isascii(dec[numc]) != 1){
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
                        if(dec[numc] >= 0 && dec[numc] <= 32){  // Assigning mnemonics to the decimal values that don't have ASCII characters
                            strcpy(asc_beg, getMnemonic(dec[numc],temp));

                            if(isascii(dec[numc]) != 1){
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

    else if(way == 1){//When the command line argument has a file.

        int BUFFER_SIZE = 100;
        int i = 0;
        char bufr[BUFFER_SIZE];
        char bufset[100];

        int fd = open(argv[1], O_RDONLY);

        if(fd == -1){ //If file cannot open
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
        char temp1[6];
        char asc_char;

        int n;
        n = read(fd, bufr, BUFFER_SIZE);
        i = 0;


        while(n == BUFFER_SIZE){ //If file size is bigger than buffer size, read again
            while(i <BUFFER_SIZE){ //Scan through bufr for spaces
                if(!isspace(bufr[i])){ // Print set if space is not found
                    bufset[bit_i] = bufr[i];
                    printf("%c",bufset[bit_i]);
                    bit_i++;
                    i++;
                }

                else{ // When isspace
                    if(bit_i <= 7){
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

                    if(sum1 >= 0 && sum1 <= 32){  // Assign mnemonic to the decimal value that don't have ASCII characters
                        strcpy(asc_val, getMnemonic(sum1,temp1));
                    }


                    if((par_check1 % 2) == 0){ //If parity is even.
                        if(sum1 >= 0 && sum1 <= 32)
                            printf("        %5s      %4d    %4s", asc_val, sum1, even1);
                        else
                            printf("        %5c      %4d    %4s", asc_char, sum1, even1);
                    }
                    else{ //If parity is odd.
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

        i = 0;

        while(i < n){ // If n >0 and < BUFFER_SIZE, then...
            if(!isspace(bufr[i])){ // Scan through bufr for spaces. Print binary number set if there is no space yet
                bufset[bit_i] = bufr[i];
                printf("%c",bufset[bit_i]);
                bit_i++;
                i++;

            }

            else{ //Space is found
                    if(bit_i <= 7){ // If there is less than 8 bits in the binary number...
                        remain1 = 8 - (bit_i);

                        while(y < remain1){ //If binary number is less than 8 digits, pad with zeros.
                            printf("%c",'0');
                            y++;
                        }
                    }

                    y = 0;
                    while(y < bit_i){ //Loop to find parity and decimal of binary number
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


                    if(isascii(sum1) != 1){ //If the value is not an ASCII.
                        printf("Error. Please input ASCII values only.\n");
                        return 0;
                    }

                    asc_char = sum1;

                    if(sum1 >= 0 && sum1 <= 32){
                        strcpy(asc_val, getMnemonic(sum1,temp1));
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

        //*****************************The code below is to find the ASCII character, decimal, and parity of the last binary number in the file

        if(bufr[n - 1] == 32){

        }
        else{
            if(bit_i <= 7){ // If there is less than 8 bits in the binary number...
                remain1 = 8 - (bit_i);

                while(y < remain1){ //If binary number is less than 8 digits, pad with zeros.
                    printf("%c",'0');
                    y++;
                }
            }

            y = 0;
            while(y < bit_i){ //This loop is to find the parity and decimal of the binary number
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

            if(sum1 >= 0 && sum1 <= 32){  // Assigning mnemonics to the decimal values that don't have ASCII characters
                strcpy(asc_val, getMnemonic(sum1,temp1));
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

        close(fd);

    }

    return 0;

}

char* getMnemonic(int number, char* asc_val)
{

    if(number >= 0 && number <= 32){  // Assigning mnemonics to the decimal values that don't have ASCII characters
        if(number == 0)
            strcpy(asc_val,"NUL");
        else if(number == 1)
            strcpy(asc_val,"SOH");
        else if(number == 2)
            strcpy(asc_val,"STX");
        else if(number == 3)
            strcpy(asc_val,"ETX");
        else if(number == 4)
            strcpy(asc_val,"EOT");
        else if(number == 5)
            strcpy(asc_val,"ENQ");
        else if(number == 6)
            strcpy(asc_val,"ACK");
        else if(number == 7)
            strcpy(asc_val,"BEL");
        else if(number == 8)
            strcpy(asc_val,"BS");
        else if(number == 9)
            strcpy(asc_val,"HT");
        else if(number == 10)
            strcpy(asc_val,"LF");
        else if(number == 11)
            strcpy(asc_val,"VT");
        else if(number == 12)
            strcpy(asc_val,"FF");
        else if(number == 13)
            strcpy(asc_val,"CR");
        else if(number == 14)
            strcpy(asc_val,"SO");
        else if(number == 15)
            strcpy(asc_val,"SI");
        else if(number == 16)
            strcpy(asc_val,"DLE");
        else if(number == 17)
            strcpy(asc_val,"DC1");
        else if(number == 18)
            strcpy(asc_val,"DC2");
        else if(number == 19)
            strcpy(asc_val,"DC3");
        else if(number == 20)
            strcpy(asc_val,"DC4");
        else if(number == 21)
            strcpy(asc_val,"NAK");
        else if(number == 22)
            strcpy(asc_val,"SYN");
        else if(number == 23)
            strcpy(asc_val,"ETB");
        else if(number == 24)
            strcpy(asc_val,"CAN");
        else if(number == 25)
            strcpy(asc_val,"EM");
        else if(number == 26)
            strcpy(asc_val,"SUB");
        else if(number == 27)
            strcpy(asc_val,"ESC");
        else if(number == 28)
            strcpy(asc_val,"FS");
        else if(number == 29)
            strcpy(asc_val,"GS");
        else if(number == 30)
            strcpy(asc_val,"RS");
        else if(number == 31)
            strcpy(asc_val,"US");
        else if(number == 32)
            strcpy(asc_val,"SPACE");
    }

    return asc_val;
}

