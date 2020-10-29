/*
 Program to parse, construct and evaluate a polynomial
 *********************************************
 ***************************************************************
 * Author         Dept.             Date          Notes
 ***************************************************************
 * Joseph D       Comp. Science. March 20 2020    Initial version.
*/

#include <stdio.h>
#include "poly.h"
#include "utils.h"

int main(int argc, char* argv[])
{
	int status, coeff, expo;
	char polyData[51];
	FILE* dataFile = fopen(argv[1], "r");
	
	if(dataFile == NULL)
	{
		fprintf(stderr, "Error, unable to read file %s\n", argv[1]);
		return 1;
	}

	while(fgets(polyData, 50, dataFile)) // read one line at a time from file.
	{
		parse(polyData, &coeff, &expo); // parse the line
		status = addPolyTerm(coeff, expo);
		if(status != 0) // out of memory error?
		{
			fprintf(stderr, "Error, unable to keep building the polynomial\n");
			return 2;
		}
	}
	displayPolynomial(); // display the polynomial expression

	// evaluate and print the values for the polynomial expression
	for(int i=-2; i<3; i++)
		printf("for x=%d, y=%d\n", i, evaluatePolynomial(i));

	return 0;
}

