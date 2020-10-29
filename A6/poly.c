/*
 Helper C module that implements a linklist data structure to store
   and manipulate a polynomial.
 *********************************************
 ***************************************************************
 * Author         Dept.             Date          Notes
 ***************************************************************
 * Joseph D       Comp. Science. March 20 2020    Initial version.
*/

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Data structure to store each polynomial term
struct PolyTerm
{
	int coeff;
	int expo;
	struct PolyTerm *next;
};

// Pointer to the start of the polynomial.
struct PolyTerm* head = NULL;

// Helper function to create a new polynomial structure.
struct PolyTerm* makePolyTerm(int coeff, int expo)
{
	struct PolyTerm *newP = (struct PolyTerm*) malloc(sizeof(struct PolyTerm));
	if(newP != NULL)
	{
		newP->coeff = coeff;
		newP->expo = expo;
		newP->next  = NULL;
	}
	else // out of memory
	{
		fprintf(stderr, "Error!, unable to allocate any memory\n");
	}
	return newP;
}

// Function to be called to "add" a new term to the polynomial.
int addPolyTerm(int coeff, int expo)
{
	struct PolyTerm *current, *previous = NULL, *newP = NULL;
	current = head;

	// Check if we already have a term for the same exponent.
	while((current != NULL) && (current->expo < expo))  
	{
		previous = current;
		current = current->next;
	}
	
	if(current != NULL)
	{
		if(current->expo == expo) // Add coefficient to existing term
		{
			current->coeff += coeff;
			return 0;
		}
		else	// we need to add a new term to the polynomial
		{
			newP = makePolyTerm(coeff, expo);
			if(newP == NULL) return -1; //Ran out of memory?
			if(previous == NULL) // New term is going to be the first term.
				head = newP; 
			else 								 // New term is not to be the first term.
				previous->next = newP; // Make sure the previous term is pointing to the new one.
			newP->next     = current; // The new term is before the "current" term.
		}
	}
	else // A new term that needs to go to the end of the polynomial
	{
		newP = makePolyTerm(coeff, expo);
		if(newP == NULL) return -1; //Ran out of memory?
		if(previous == NULL) // New term is going to be the first term.
			head = newP; 
		else 								 // New term is not to be the first term.
			previous->next = newP; // Make sure the previous term is pointing to the new one.
	}
	
	return 0;
}

// Function that traverses the polynomial and displays it.
void displayPolynomial()
{
	struct PolyTerm *current = head;
	while(current != NULL)
	{
		printf(current==head?"%dx%d":"%+dx%d", current->coeff, current->expo);
		current = current->next;
	}
	putchar('\n');
}

// Function that evaluates the polynomial for different values.
int evaluatePolynomial(int x)
{
	struct PolyTerm *current = head;
	int y = 0;
	while(current != NULL)
	{
		y += (int)(current->coeff*powi(x,current->expo));
		current = current->next;
	}
	return y;
}

