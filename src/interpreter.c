#include <stdio.h>
#include <stdlib.h>
#include "interpreter.h"

int
eval_ring (ring_t *literal) {
    switch (literal->type) {
        case INT:
            return literal->value.int_val;
    }
}

ring_t*
eval_arith (node_arith_t *node, env_t* env) {
    ring_t *op1 = eval_expr (node->op1, env);
    ring_t *op2 = eval_expr (node->op2, env);
    switch (node->type) {
        case ADD:
            return ring_int (eval_ring (op1) + eval_ring (op2));
        case SUB:
            return ring_int (eval_ring (op1) - eval_ring (op2));
        case MUL:
            return ring_int (eval_ring (op1) * eval_ring (op2));
        case DIV:
            return ring_int (eval_ring (op1) / eval_ring (op2));
    }
}

ring_t*
eval_expr (node_expr_t *exp, env_t *env) {
    ring_t *prim;
    switch (exp->type) {
        case RING:
            return exp->body.literal; 
        case ARITH:
            return eval_arith (exp->body.arith_val, env);
        case ID:
            prim = env_lookup (exp->body.id->name, env);
            if (prim == NULL) {
                sprintf (ERROR, (char *) "var '%s' not assigned",
                         exp->body.id->name);
                error ();
                exit (1);
            }
            return prim;
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
                rprintf(eval_expr (node->expr, env));
                break;
            case ASSGN:
                env_add_binding (node->id->name, eval_expr (node->expr, env), env);
                break;
        }
    }
}

void
interpret () {
    eval_statements (program_start->st_list, program_start->env);
    program_start->st_list = NULL;
}
