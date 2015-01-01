%{
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "src/node.h"
%}

%token <val>T_Int

%type<state>P
%type<node_statement>S
%type <node_expr>E
%type <rt>T

%left '-' '+'
%left '*' '/'

%union {
    int val;
    struct ring_t *rt;
    struct node_expr_t *node_expr;
    struct node_statement_t *node_statement;
}

%%

P  : P S       { add_statement ($2); }
   | S         { add_statement ($1); }
   ;

S  : 'print' E '\n' { $$ = node_statement_from_print ($2); }
   | E '\n'         { $$ = node_statement_from_expr ($1);  }
   ;
   

E  :  E '+' E  { $$ = node_expr_from_arith (make_node_arith (ADD, $1, $3)); }
   |  E '-' E  { $$ = node_expr_from_arith (make_node_arith (SUB, $1, $3)); }
   |  E '*' E  { $$ = node_expr_from_arith (make_node_arith (MUL, $1, $3)); }
   |  E '/' E  { $$ = node_expr_from_arith (make_node_arith (DIV, $1, $3)); }
   |  T        { $$ = node_expr_from_ring ($1); }
   ; 

T  :  T_Int    { $$ = ring_int ($1); }
   ;

%%

int
main (int argc, char **argv) {
    assert (argc > 1);
    RING_OUT = stdout;

    int i;
    for (i = 1; i < argc; ++i) {
        if (!strcmp (argv[i], (char *) "-o")) {
            RING_OUT = fopen (argv[i + 1], "w");
            break;
        } else {
            extern FILE *yyin;
            yyin = fopen (argv[i], "r");
        }
    }

    initialize_AST ();
    int res = yyparse ();
    interpret ();
    return res;
}
