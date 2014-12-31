#include <stdlib.h>
#include "node.h"

void initialize_program () {
    program_start = malloc (sizeof (root_t));
    program_start->st_list = NULL;
}

void
add_statement (node_statement_t *s) {
    if (program_start->st_list == NULL) {
        program_start->st_list = s;
        last_added = s;
    } else {
        last_added->next = s;
        last_added = s;
    }
}

node_arith_t*
make_node_arith (arith_type type, node_expr_t *op1, node_expr_t *op2) {
    node_arith_t *node = malloc (sizeof (node_arith_t));
    node->type = type;
    node->op1 = op1;
    node->op2 = op2;
    return node;
}

node_expr_t*
node_expr_from_int (int val) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->body.val = val;
    e->type = INT;
    return e;
}

node_expr_t*
node_expr_from_arith (node_arith_t *node) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->type = ARITH;
    e->body.arith_val = node;
    return e;
}

node_statement_t*
node_statement_from_expr (node_expr_t *expr) {
    node_statement_t *s = malloc (sizeof (node_statement_t));
    s->type = EXPR;
    s->block.expr = expr;
    s->next = NULL;
    return s;
}

