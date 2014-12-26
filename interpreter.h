#include "node.h"

/* Evaluates expression nodes based on type */
int eval_expr (expr *exp);

/* Evaluator for arithmetic expressions */
int eval_arith (node_arith_t *node);

/* The main interpreter function, to be called from within the parser after
 * the input has finished parsing. */
void interpret ();
