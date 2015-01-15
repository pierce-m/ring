%{
#include "src/parser_utils.h"
#include <assert.h>
void yyerror (char const *s);
%}

%type <state>P
%type <node_statement>S
%type <node_expr>E
%type <id> ID
%type <rt>T

%token <val>T_Int
%token <name>T_Id

%left '-' '+'
%left '*' '/'

%union {
    int val;
    char *name;
    struct node_id *id;
    struct ring_t *rt;
    struct node_expr_t *node_expr;
    struct node_statement_t *node_statement;
}

%%

P  : P S       { execute_or_append ($2); }
   | S         { execute_or_append ($1); }
   ;

S  : 'print' E NL   { $$ = node_statement_print ($2);     }
   | ID '=' E NL    { $$ = node_statement_assgn ($1, $3); }
   | E '\n'         { $$ = node_statement_expr ($1);      }
   ;
   
E  :  '(' E ')'  { $$ = $2; }
   |  E '+' E    { $$ = node_expr_from_arith (make_node_arith (ADD, $1, $3)); }
   |  E '-' E    { $$ = node_expr_from_arith (make_node_arith (SUB, $1, $3)); }
   |  E '*' E    { $$ = node_expr_from_arith (make_node_arith (MUL, $1, $3)); }
   |  E '/' E    { $$ = node_expr_from_arith (make_node_arith (DIV, $1, $3)); }
   |  T          { $$ = node_expr_from_ring ($1); }
   |  ID         { $$ = node_expr_from_id ($1); }
   ; 

ID :  T_Id     { $$ = node_id_init ($1); }
   ;

T  :  T_Int    { $$ = ring_int ($1); }
   ;

NL :  NL '\n'
   |  '\n'
   ;

%%

void yyerror (char const *s) {
    fprintf (stderr, "%s\n", s);
}

int
main (int argc, char **argv) {
    RING_OUT = stdout;

    FILE *fin, *fout;
    initialize_AST ();

    if (argc == 1) {
        run_interpretive ();
    } else if (argc == 2 && ((fin = fopen (argv[1], "r")) != NULL)) {
        interpret_file (fin);
    } else if (argc == 4
               && ((fin = fopen (argv[1], "r")) != NULL)
               && !strcmp (argv[2], (char *) "-o")
               && ((fout = fopen (argv[3], "w")) != NULL)) {
        RING_OUT = fout;
        interpret_file (fin);
    } else {
        printf ("%s\n", (char *) "Usage: [-i infile -o outfile]");
        exit(1);
    }

    return 0;
}
