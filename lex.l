%{
#include "tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
int lineno;
void yyerror(const char* s);

void print_token(const char* token_name, const char* token_value) {
    printf("Token: %s, Value: %s\n", token_name, token_value);
}
%}



%%
"/*"([^*]|\*+[^*/])*\*+"/"  ; /* Ignorer les commentaires de type C */
"static"        {print_token("STATIC", yytext); return STATIC; }
"int"           { print_token("TYPE", yytext);return TYPE; }
"void"          { print_token("VOID", yytext); return VOID; }
"if"            { print_token("IF", yytext);return IF; }
"else"          {  print_token("ELSE", yytext); return ELSE; }
"while"         {  print_token("WHILE", yytext);return WHILE; }
"return"        {  print_token("RETURN", yytext); return RETURN; }
"char"          {  print_token("CHARACTER", yytext); return CHARACTER; }

[a-zA-Z_][a-zA-Z0-9_]* {  print_token("IDENT", yytext) ;return IDENT; } // Identificateurs
[0-9]+                 {  print_token("NUM", yytext); return NUM; }   // Nombres entiers

"="             {  print_token("EQ", yytext);return EQ; }
";"             { return ';'; }
"+"|"-"         {  print_token("ADDSUB", yytext);return ADDSUB; }
"*"|"/"         {  print_token("DIVSTAR", yytext); return DIVSTAR; }
"&&"            {  print_token("AND", yytext); return AND; }
"||"            {  print_token("OR", yytext);return OR; }

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
