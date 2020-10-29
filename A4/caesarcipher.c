#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 Program to implement a basic version of Caesar's cipher
 **********************************************************
 * Author      Dept.          Date         Notes
 **********************************************************
 * Xinyi Zhu   Comp.Science   Feb 15 2020  Initial version.
 * Xinyi Zhu   Comp.Science   Feb 15 2020  Added error handling.
*/

int main(int argc, char *argv[]) {

	//if the argument is not passed
	if (argc != 2) {
		puts("Error:usage is caesarcipher <offset>");
		exit (1);
	}

	//convert input argument to an int
	int offset = atoi(argv[1]);
	//assume the buffer size is no more than 100
	char msg[100];

	//execute repeatedly when success a POINTER to ARRAY 
	while (fgets(msg, 100, stdin) != NULL) {
		char c;
		int code;
		//iterate over the input string
		for (int i=0; i<strlen(msg); i++){
			if (islower(msg[i])) {
				//add up the ASCII code
				code = msg[i] + offset;
				// when the result is out of range(a-z)
				if (code < 97) code += 26;
				else if (code > 122) code -= 26;	
				c = code;
				printf("%c", c);
			} 
			//when the character is not lower case a-z
			else {
				printf("%c", msg[i]);
			}

		}
	}

}









