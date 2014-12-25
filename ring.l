%{ 
  #include "y.tab.h"
%}

%%
[0-9]+    { yylval = atoi(yytext); return T_Int; }

[-+*/\n]  { return *yytext; }
.         { /* ignore all other chars */ }

