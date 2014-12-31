%{
#include <stdio.h>
#include "node.h"
%}

%token <val>T_Int
%type <node_expr>E
%type<node_statement>S
%type<root>P

%left '-' '+'
%left '*' '/'

%union {
    int val;
    struct node_expr_t *node_expr;
    struct node_statement_t *node_statement;
    struct root_t *root;
}

%%

P  : P S       { add_statement ($2); }
   |
   ;

S  : E '\n'    { $$ = node_statement_from_expr ($1); }
   |
   ;
   

E  :  E '+' E  { $$ = node_expr_from_arith (make_node_arith (ADD, $1, $3)); }
   |  E '-' E  { $$ = node_expr_from_arith (make_node_arith (SUB, $1, $3)); }
   |  E '*' E  { $$ = node_expr_from_arith (make_node_arith (MUL, $1, $3)); }
   |  E '/' E  { $$ = node_expr_from_arith (make_node_arith (DIV, $1, $3)); }
   |  T_Int    { $$ = node_expr_from_int ($1); }
   ; 

%%

int main (int argc, char *argv[]) {
    FILE *out;
    if (argc > 1) {
        extern FILE *yyin;
        yyin = fopen (argv[1], "r");
        out = fopen("out.ring", "w");
    } else {
        out = stdout;
    }
    initialize_program ();
    int res = yyparse ();
    fprintf (out, "%d\n", interpret ());
    return res;
}
