#include "node.h"

/* Evaluates a ring primitive type */
int eval_primitive (ring_t *literal);

/* Evaluates expression nodes based on type */
int eval_expr (node_expr_t *exp, env_t *env);

/* Evaluator for arithmetic expressions */
int eval_arith (node_arith_t *node, env_t *env);

/* Evaluates a statement node */
void eval_statement (node_statement_t *node, env_t *env);
