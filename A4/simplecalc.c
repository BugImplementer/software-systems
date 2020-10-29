#include <stdio.h>
#include <stdlib.h>

/*
 Program to implement a simple calculator
 **********************************************************
 * Author      Dept.          Date         Notes
 **********************************************************
 * Xinyi Zhu   Comp.Science   Feb 15 2020  Initial version.
 * Xinyi Zhu   Comp.Science   Feb 15 2020  Added error handling.

*/

int main(int argc, char* argv[])
{
//check if three arguments are passed by user
if (argc != 4) {
       puts("Error: usage is simplecalc <x> <op> <y>");
       exit (1);	       
}

//convert input string to int
int x = atoi(argv[1]);
char op = *argv[2];
int y = atoi(argv[3]);

switch(op) {
	case '+': printf("%d\n",x+y);
		  break;
	case '-': printf("%d\n",x-y);
		  break;
	case '*': printf("%d\n",x*y);
		  break;
	case '/': printf("%d\n",x/y);
		  break;
	default: printf("%c not a valid operator\n",op);
		 exit (2);
}



}
