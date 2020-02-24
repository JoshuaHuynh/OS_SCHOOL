Activity Log for Lab 0 by Joshua Huynh:

* Use of built-in functions or library functions for C. (Excluding read(), isascii(), open(), and printf()).
	
	*I used the strcpy() function for Lab 0.  The reason I used this function in this lab was simply because I needed an efficient way to assign a string to a char array.
	 For example, in the lab, I used this function to assign a mnemonic of an ASCII value to a char array. An example of how to use strcpy(): Suppose there is a variable char x[6]. Then strcpy(x, "Hello") will generally assign
	 "Hello" to x. 
	
	*I used the isspace() function for Lab 0 in order to separate the binary numbers being read in the text file. Function isspace() checkes for white-space characters. An example of how to use isspace(): Suppose x is an 
	 int variable. If x = ' ', then x would be assigned 32, which would be the decimal that represents the ASCII character SPACE. The function then returns 1 if x is a white-space, and 0 if x is not a white-space.  In this example, the
	 function returns 1.
	
	*I used the pow() function in order to calculate the decimal value from a binary number. This function takes in numbers, not characters. An example of how to use pow: The function pow(2,0) returns 1. In math pow(2,0) is 2^0.
	 This function is helpful because it is easier, faster and more efficient than using a loop or recursion to calculate a number to the power of another number.
	
	*I used strlen() to find the number of bits or chars for each binary number set. Each binary number is a string of bits. This function would help me find out if there are less than 8 bits in a binary number.
	
* Quick details or summary of what I did to write the program for Lab 0. (Order goes from top to bottom.  I worked on the lab generally from February 7,2020 to February 23,2020)
	
	*First, in order to deal with the '-' that may appear as the text file's name or the beginning of stdin, I created branches in the program with if-else statements. For example, if the first character read is '-', then
	 the program will go to that branch that deals with such a situation.
	 
	*Similarly, I created branches in order to deal with the possibilities of the users reading from a file or using stdin. For example, one branch deals with a user reading from a file, while the other branch deals with stdin.
	
	*To check for the possibilities of an error, I used a while-loop to find characters that are neither '1' nor '0'
	
	* Then for each of the branches that deal with reading from a file or stdin, I print the binary numbers from the text file or stdin, then I calculate the ASCII character, decimal value, and parity for each binary number. 
	  Then I print what I found in a table-like display.
	
	* To find the ASCII character, I simply created a char variable.  Then I assigned the char variable with the integer that represents the ASCII character.
	
	* To find the decimal value, I simply find the positions of the '1' characters in the binary number. Each time a '1' character appears, add 2^x to an int variable.  The integer x is the position or place of 
	  the '1' character in the binary number
	
	* To find the parity of each binary number, I create an int variable that equals zero for each binary number. Then for each binary number, I add 1 to the int variable each time a '1' character appears in the binary number.  
	  Then I find the remainder of the variable after dividing it by 2.  If the result is 0, then the parity is even.  If not, the parity is odd.
	 
	*Then, I put the code in K&R style, added some comments, and checked for errors.
	
	*Finally, I polished up the code by making it shorter. I also made a function called getMnemonic(), which takes in a decimal and a char array.  The function then returns the char array with the mnemonic assigned to the array.
	
	
	


