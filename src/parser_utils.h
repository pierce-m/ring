#include <string.h>
#include "node.h"

/* Interpretive mode */
int in;

extern FILE *yyin;

/* Returns a copy of a lexeme. */
char *copy_lexeme (char *lexeme);

/* Interprets the file pointed to by f */
void interpret_file (FILE *f);

/* Runs the REPL */
void run_interpretive ();

/* Depending on if we're in the REPL, executes a statement or adds
 * in to the AST */ 
void execute_or_append (node_statement_t *s);

