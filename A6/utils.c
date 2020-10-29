/*
 Basic util functions
 *********************************************
 ***************************************************************
 * Author         Dept.             Date          Notes
 ***************************************************************
 * Joseph D       Comp. Science. March 20 2020    Initial version.
*/

#include <stdio.h>

// Parse a polynomial term from a character string/array.
void parse(char *str, int *coeff, int *expo)
{
	sscanf(str, "%d %d", coeff, expo);
}

// Compute the power of an integer number (+ve powers only)
int powi(int x, int expo)
{
	int res=1;
	for(; expo>0; expo--,res*=x);
	return res;
}
