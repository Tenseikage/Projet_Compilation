%{
#include "../inc/tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
#include <string.h>
int lineno;
void yyerror(const char* s);

/*void print_token(const char* token_name, const char* token_value) {
    printf("Token: %s, Value: %s\n", token_name, token_value);
}*/
%}


%x COMMENT

%%
"//".*          ; /* Ignorer les commentaires de type C */
"/*"            { BEGIN(COMMENT); } /* Commencer un commentaire de type C */
<COMMENT>"*/"   { BEGIN(INITIAL); } /* Finir un commentaire de type C */
<COMMENT>\n     { yylineno++; } /* Incrémenter le compteur de lignes pour chaque nouvelle ligne dans un commentaire */
<COMMENT>.      ; /* Ignorer les autres caractères dans un commentaire */

"static"        {strcpy(yylval.ident,yytext);return STATIC; }
"int"           {strcpy(yylval.ident,yytext);return TYPE; }
"char"          {strcpy(yylval.ident,yytext);return TYPE;}
"void"          {strcpy(yylval.ident,yytext);return VOID; }
"if"            {strcpy(yylval.ident,yytext);return IF; }
"else"          { return ELSE; }
"while"         {  return WHILE; }
"return"        {  return RETURN; }
"("             { return '(';}
")"             { return ')';}
"{"             { return '{';}
"}"             { return '}';}

[a-zA-Z_][a-zA-Z0-9_]* { strcpy(yylval.ident,yytext); return IDENT; } // Identificateurs
[0-9]+                 {yylval.num = atoi(yytext);return NUM; }   // Nombres entiers

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

