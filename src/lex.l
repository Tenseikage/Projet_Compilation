%{
#include "tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lineno = 1;
void yyerror(const char* s);

%}

%option noinput
%option nounput


%x COMMENT
%%

"//".*          ; /* Ignore les commentaires de type C */
"/*"            { BEGIN(COMMENT); } /* Commence un commentaire de type C */
<COMMENT>"*/"   { BEGIN(INITIAL); } /* Finit un commentaire de type C */
<COMMENT>\n     { lineno++; } /* Incrémente le compteur de lignes pour chaque nouvelle ligne dans un commentaire */
<COMMENT>.      ; /* Ignore les autres caractères dans un commentaire */
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
[0-9]+                 {yylval.num = atoi(yytext); return NUM; }   // Nombres entiers

"="             {  return '='; }
"!"             { return '!';} 
";"             { return ';'; }
","             { return ',';}
"+"|"-"         { strcpy(yylval.byte,yytext); return ADDSUB; }
"*"|"/"|"%"        {strcpy(yylval.byte,yytext);  return DIVSTAR; }
"&&"            {  return AND; }
"||"            {  return OR; }
"=="|"!="       { strcpy(yylval.byte,yytext); return EQ;}
"<"|">"|"<="|">=" {strcpy(yylval.order, yytext); return ORDER;}
'(\\[a-z]|[^\'])' {strcpy(yylval.letter,yytext); return CHARACTER;}
\n              { lineno++; } // Incrément du numéro de ligne
[ \t]+          { /* Ignore espaces et tabulations */ }
.               { 
                    yyerror("Caractère ou lexème invalide détecté à la ligne");
                    printf(": %d \n", lineno);
                    return 1;  // Retourne 1 pour signaler l'erreur
                }

%%


