%{
#include <stdio.h>
#include <assert.h>
#include "interpreter.h"
%}

%token T_Int

%%

S  :  S E '\n' { printf ("%d\n", $2); }
   |
   ;

E  :  E '+' E  { $$ = $1 + $3; }
   |  E '-' E  { $$ = $1 - $3; }
   |  E '*' E  { $$ = $1 * $3; }
   |  E '/' E  { $$ = $1 / $3; }
   |  T_Int    { $$ = $1; }
   ; 

%%

int main () {
    int result = yyparse ();
    return result;
}
