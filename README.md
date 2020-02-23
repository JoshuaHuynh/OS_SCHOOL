Activity Log for Lab 0 by Joshua Huynh:

* Use of built-in functions or library functions for C. (Excluding read(), isascii(), open(), and printf()).
	
	*I used the strcpy() function for Lab 0.  The reason I used this function in this lab was simply because I needed an efficient way to assign a string to a char array.
	 For example, in the lab, I used this function to assign a mnemonic of an ASCII value to a char array.
	
	*I used the isspace() function for Lab 0 in order separate the binary numbers being read in the text file.
	
	*I used the pow() function in order to calculate the decimal value from a binary number.  
	
	*I used strlen() to find the number of bits for each binary number.  This function would help me find out if there are less than 8 bits in a binary number.
	
* Quick details or summary of what I did to write the program for Lab 0. (Order goes from top to bottom.  I worked on the lab generally from February 7 - February 21)
	
	*First, in order to deal with the '-' that may appear as the text file's name or the beginning of stdin, I created branches in the program with if-else statements. For example, if the first character read is '-', then
	 the program will go to that branch that deals with such a situation.
	 
	*Similarly, I created branches in order to deal with the possibilities of the users reading from a file or using stdin. For example, one branch deals with a user reading from a file, while the other branch deals with stdin.
	
	*To check for the possibilities of an error, I used a while-loop to find characters that are neither '1' nor '0'
	
	* Then for the branches that deal with reading from a file or stdin, I found the ASCII character, decimal value, and parity for each binary number. Then I print what I found in a table-like display.
	
	* To find the ASCII character, I simply created a char variable.  Then I assigned the char variable with the integer that represents the ASCII character.
	
	* To find the decimal value, I simply find the positions of the '1' characters in the binary number. Each time a '1' character appears, add 2^x to an int variable.  The integer that x is depends on the 
	  position of the '1' character in the binary number
	
	* To find the parity of each binary number, I add 1 to an int variable each time a '1' character appears in the binary number.  Then I find the remainder of the variable after dividing it by 2.  If the result is 0, then 
	  the parity is even.  If not, the parity is odd.
	 
	*Finally, I put the code in K&R style, added some comments, and checked for errors.
	
	
	


