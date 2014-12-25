#include <stdlib.h>
#include "node.h"


/* Constructor for arithmetic AST node */
node_arith_t*
make_arith_node (char *type, expr *op1, expr *op2) {
    node_arith_t *node = malloc (sizeof (node_arith_t));
    node->type = type;
    node->op1 = op1;
    node->op2 = op2;
    return node;
}

/* Constructor for integer literal AST nodes */
node_int_t*
make_node_int (int val) {
    node_int_t *node = malloc (sizeof (node_int_t));
    node->val = val;
    return node;
}
