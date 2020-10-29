/*
 Header file to expose the polynomial functions implemented
 in poly.c
 *********************************************
 ***************************************************************
 * Author         Dept.             Date          Notes
 ***************************************************************
 * Joseph D       Comp. Science. March 20 2020    Initial version.
*/

#ifndef __POLY_H__
#define __POLY_H__

// Add a term to the polynomial.
int addPolyTerm(int coeff, int expo);

// Display the polynomial as an expression.
void displayPolynomial();

// Evaluate the polynomial for a value of x, and return the value of expression.
int evaluatePolynomial(int x);

#endif // __POLY_H__
