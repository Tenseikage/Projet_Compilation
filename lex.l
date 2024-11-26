%{
#include "tree.h"
#include "parser.tab.h"
#include <stdio.h>
int lineno;
%}


%%
"/*"([^*]|\*+[^*/])*\*+"/"  ; /* Ignorer les commentaires de type C */
\\b(int|char)\\b {return TYPE;} /*Type d'une variable en C*/
[0-9]+ {return NUM;} /*Constante numérique*/
[a-zA-Z_][a-zA-Z0-9_]* { return IDENT; } /*Identifacteur*/
"=="|"=" {return EQ;} /*Opérateurs d'égalité*/
">"|"<"|"<="|">=" {return ORDER;} /*Opérateurs de comparaison*/
"+"| "-" {return ADDSUB};
"*"|"/"|"%" {return DIVSTAR;}
"||" {return OR;} 
"&&" {return AND;}

%%