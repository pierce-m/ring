#include <stdio.h>
#include "node.h"

/* There is absolutely no reason why this needs to be the case */
#define MAX_ERROR_STRING 256

/* File descriptor for program output */
FILE *RING_OUT;

/* Error string, set when an error has occured */
char ERROR[MAX_ERROR_STRING];

/* Prints an ERROR to stderr */
void error ();

/* Prints a ring_t type */
void rprintf (ring_t *r);
