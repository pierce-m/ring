%{
#include <stdio.h>
#include "node.h"
%}

%token <val>T_Int
%type <node_expr>E

%left '-' '+'
%left '*' '/'

%union {
    int val;
    struct node_expr_t *node_expr;
}

%%

S  :  S E '\n' { 
                   printf ("%d\n", interpret());
               }
   |
   ;

E  :  E '+' E  { $$ = node_expr_from_arith (make_node_arith (ADD, $1, $3)); }
   |  E '-' E  { $$ = node_expr_from_arith (make_node_arith (SUB, $1, $3)); }
   |  E '*' E  { $$ = node_expr_from_arith (make_node_arith (MUL, $1, $3)); }
   |  E '/' E  { $$ = node_expr_from_arith (make_node_arith (DIV, $1, $3)); }
   |  T_Int    { $$ = node_expr_from_int ($1); }
   ; 

%%

int main () {
    int result = yyparse ();
    return result;
}
