#include <stdlib.h>
#include "node.h"

void initialize_AST () {
    program_start = malloc (sizeof (program_state_t));
    program_start->st_list = NULL;
    env_t *e = malloc (sizeof (env_t));
    e->parent = NULL;
    e->bindings = hashtable_init (10);
    program_start->env = e;
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
node_expr_from_ring (ring_t *r) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->body.literal= r;
    e->type = RING;
    return e;
}

node_expr_t*
node_expr_from_arith (node_arith_t *node) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->type = ARITH;
    e->body.arith_val = node;
    return e;
}

node_expr_t*
node_expr_from_id (node_id *id) {
    node_expr_t *e = malloc (sizeof (node_expr_t));
    e->type = ID;
    e->body.id = id;
    return e;
}


node_statement_t*
node_statement_expr (node_expr_t *expr) {
    node_statement_t *s = malloc (sizeof (node_statement_t));
    s->type = EXPR;
    s->expr = expr;
    s->next = NULL;
    return s;
}

node_statement_t*
node_statement_print (node_expr_t *expr) {
    node_statement_t *s = malloc (sizeof (node_statement_t));
    s->type = PRINT;
    s->expr = expr;
    s->next = NULL;
    return s;
}

node_statement_t*
node_statement_assgn (node_id *name, node_expr_t *expr) {
    node_statement_t *s = malloc (sizeof (node_statement_t));
    s->type = ASSGN;
    s->id = name;
    s->expr = expr;
    s->next = NULL;
    return s;
}

node_id*
node_id_init (char *name) {
    node_id *n = malloc (sizeof (node_id));
    n->name = name;
    return n;
}
