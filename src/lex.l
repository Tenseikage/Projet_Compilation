%{
#include "tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lineno;
void yyerror(const char* s);

/*void print_token(const char* token_name, const char* token_value) {
    printf("Token: %s, Value: %s\n", token_name, token_value);
}*/
%}

%option noinput
%option nounput


%x COMMENT
%%

"//".*          ; /* Ignorer les commentaires de type C */
"/*"            { BEGIN(COMMENT); } /* Commencer un commentaire de type C */
<COMMENT>"*/"   { BEGIN(INITIAL); } /* Finir un commentaire de type C */
<COMMENT>\n     { yylineno++; } /* Incrémenter le compteur de lignes pour chaque nouvelle ligne dans un commentaire */
<COMMENT>.      ; /* Ignorer les autres caractères dans un commentaire */
"int"           {strcpy(yylval.type,yytext); return TYPE; }
"static"        { return STATIC;}
"char"          {strcpy(yylval.type,yytext); return TYPE ;}
"void"          {strcpy(yylval.type,yytext); return VOID; }
"if"            { return IF; }
"else"          {  return ELSE; }
"while"         {  return WHILE; }
"return"        {  return RETURN; }
"("             { return '(';}
")"             { return ')';}
"{"             { return '{';}
"}"             { return '}';}

[a-zA-Z_][a-zA-Z0-9_]* {strcpy(yylval.ident,yytext);  return IDENT; } // Identificateurs
[0-9]+                 {yylval.num = atoi(yytext); /*printf("valeur : %d \n",yylval.num);*/ return NUM; }   // Nombres entiers

"="             {  return '='; }
"!"             { return '!';} /*Pas sur*/
";"             { return ';'; }
","             { return ',';}
"+"|"-"         {  return ADDSUB; }
"*"|"/"|"%"        {  return DIVSTAR; }
"&&"            {  return AND; }
"||"            {  return OR; }
"=="|"!="       { return EQ;}
"<"|">"|"<="|">=" {return ORDER;}
'(\\[a-z]|[^\'])' {printf("oui\n");return CHARACTER;}
\n              { yylineno++; } // Incrément du numéro de ligne
[ \t]+          { /* Ignore espaces et tabulations */ }
.               { 
                    yyerror("Caractère invalide détecté");
                    return 1;  // Retourner 1 pour signaler l'erreur
                }

%%


