%{ 
#include "y.tab.h"
%}

%%

print     { return *yytext;                          }
[a-zA-Z]  { yylval.name = yytext; return T_Id;       }
[0-9]+    { yylval.val = atoi(yytext); return T_Int; }
[-+*/\n=]  { return *yytext;                          }
.         {       /* ignore all other chars */       }

