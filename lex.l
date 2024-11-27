%{
#include "tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
int lineno;
void yyerror(const char* s);

/*void print_token(const char* token_name, const char* token_value) {
    printf("Token: %s, Value: %s\n", token_name, token_value);
}*/
%}



%%
"//"|"/*"([^*]|\*+[^*/])*\*+"/"  ; /* Ignorer les commentaires de type C */
"static"        {return STATIC; }
"int"           { return TYPE; }
"char"          {return TYPE;}
"void"          { return VOID; }
"if"            { return IF; }
"else"          {  return ELSE; }
"while"         {  return WHILE; }
"return"        {  return RETURN; }
"("             { return '(';}
")"             { return ')';}
"{"             { return '{';}
"}"             { return '}';}

[a-zA-Z_][a-zA-Z0-9_]* {  return IDENT; } // Identificateurs
[0-9]+                 {  return NUM; }   // Nombres entiers

"="             {  return '='; }
";"             { return ';'; }
"+"|"-"         {  return ADDSUB; }
"*"|"/"         {  return DIVSTAR; }
"&&"            {  return AND; }
"||"            {  return OR; }
\'[^\']\'       {return CHARACTER;}
\n              { yylineno++; } // Incrément du numéro de ligne
[ \t]+          { /* Ignore espaces et tabulations */ }
.               { 
                    yyerror("Caractère invalide détecté");
                    return 0;  // Retourner 0 pour signaler l'erreur
                }

%%

int yywrap(void) {
    return 1; // Indique la fin de l'analyse
}
