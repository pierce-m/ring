#include <stdlib.h>
#include "node.h"

/* Constructor for arithmetic AST node */
node_arith_t *make_arith_node (char *type, int op1, int op2) {
    node_arith_t *node = malloc(sizeof(node_arith_t));
    node->type = type;
    node->op1 = op1;
    node->op2 = op2;
    return node;
}
