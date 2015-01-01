#include "node.h"

/* Evaluates a ring primitive type */
int eval_primitive (ring_t *literal);

/* Evaluates expression nodes based on type */
int eval_expr (node_expr_t *exp, env_t *env);

/* Evaluator for arithmetic expressions */
int eval_arith (node_arith_t *node, env_t *env);

/* Evaluates a block of statements. Note that return statements are treated
 * differently than the others. */
void eval_statements (node_statement_t *node, env_t *env);
