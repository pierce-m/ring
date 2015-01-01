#include <stdlib.h>
#include "parser_utils.h"

char*
copy_lexeme (char *lexeme) {
    char *copy = malloc (sizeof (lexeme));
    strcpy (copy, lexeme);
    return copy;
}

void
interpret_file (FILE *f) {
    in = 0;
    yyin = f;
    yyparse ();
    interpret ();
}

void
run_interpretive () {
    int res = 1;
    in = 1;
    yyin = stdin;
    printf ("%s ", (char *) "ring>");
    while (res) { res = yyparse (); }
}

void
execute_or_append (node_statement_t *s) {
    add_statement (s);
    if (in) {
        interpret ();
        printf ("%s ", (char *) "ring>");
    }
}
