#include "interpreter.h"
#include <stdio.h>

int
eval_primitive (ring_t *literal) {
    switch (literal->type) {
        case INT:
            return literal->value.int_val;
    }
}

int
eval_arith (node_arith_t *node, env_t* env) {
    int op1 = eval_expr (node->op1, env);
    int op2 = eval_expr (node->op2, env);
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

int
eval_expr (node_expr_t *exp, env_t *env) {
    switch (exp->type) {
        case RING:
            return eval_primitive (exp->body.literal); 
        case ARITH:
            return eval_arith (exp->body.arith_val, env);
        case ID:
            return eval_primitive (env_lookup (exp->body.id->name, env));
    }
}

void
eval_statements (node_statement_t *node, env_t *env) {
    for (; node != NULL; node = node->next) {
        switch (node->type) {
            case EXPR:
                eval_expr (node->expr, env);
                break;
            case PRINT:
                fprintf(RING_OUT, "%d\n", eval_expr (node->expr, env));
                break;
            case ASSGN:
                env_add_binding (node->id->name,
                    ring_int (eval_expr (node->expr, env)), env);
                break;
        }
    }
}

void
interpret () {
    eval_statements (program_start->st_list, program_start->env);
    program_start->st_list = NULL;
}
