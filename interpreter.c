#include <stdio.h>
#include "interpreter.h"

int eval_expr (expr *exp) {
    switch (exp->type) {
        case INT:
           return exp->body.val; 
        case ARITH:
           return eval_arith (exp->body.arith_val);
    }
}

int eval_arith (node_arith_t *node) {
    int op1 = eval_expr (node->op1);
    int op2 = eval_expr (node->op2);
    switch (node->type) {
        case ADD:
            return op1 + op2;
        case SUB:
            return op1 - op2;
        case MUL:
            return op1 * op2;
        case DIV:
            return op1 / op2;
    }
}

void interpret () {
    root_t *currnode = program_start;
    while (currnode != NULL) {
        eval_expr (currnode->block);
    }
}
