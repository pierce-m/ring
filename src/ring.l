%{ 
#include "y.tab.h"
#include "src/parser_utils.h"
%}

%%

print     { return *yytext; }
[()]      { return *yytext; }
[a-zA-Z]+ { yylval.name = copy_lexeme (yytext); return T_Id; }
-?[0-9]+  { yylval.val = atoi(yytext); return T_Int; }
[-+*/\n=] { return *yytext;                          }
.         {       /* ignore all other chars */       }

