#include <stdlib.h>
#include "node.h"

/* Initializes the first program root. Called before parsing. */
void initialize_program () {
    program_start = malloc (sizeof (root_t));
    program_start->next = NULL;
    last_successor = program_start;
}

/* Adds an expression tree to the current root, and creates a
 * new successor root. */
void
add_subtree (node_expr_t *block) {
    last_successor->block = block;
    root_t *r = malloc (sizeof (root_t));
    last_successor->next = r;
    last_successor = r;
}

/* Constructs arithmetic node from two expressions and a type */
node_arith_t*
make_arith_node (arith_type type, node_expr_t *op1, node_expr_t *op2) {
    node_arith_t *node = malloc (sizeof (node_arith_t));
    node->type = type;
    node->op1 = op1;
    node->op2 = op2;
    return node;
}

/* Constructs expressions with int literals */
node_expr_t*
node_expr_from_int (int val) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->body.val = val;
    e->type = INT;
    return e;
}

/* Constructs expressions with arithmetic nodes */
node_expr_t*
node_expr_from_arith (node_arith_t *node) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->type = ARITH;
    e->body.arith_val = node;
    return e;
}
