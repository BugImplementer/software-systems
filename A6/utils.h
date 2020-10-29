/*
 Header file to expose the functions in utils.c
 *********************************************
 ***************************************************************
 * Author         Dept.             Date          Notes
 ***************************************************************
 * Joseph D       Comp. Science. March 20 2020    Initial version.
*/

#ifndef __UTILS_H__
#define __UTILS_H__

// Parses a polynomial term from str and stores it to coeff and expo.
void parse(char *str, int *coeff, int *expo);

// Computes and returns the value of x^expo.
int powi(int x, int expo);

#endif // __UTILS_H__
