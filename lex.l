%{
#include "tree.h"
#include "parser.tab.h"
#include <stdio.h>
int lineno;

void print_token(const char* token_name, const char* token_value) {
    printf("Token: %s, Value: %s\n", token_name, token_value);
}
%}

%%
"/*"([^*]|\*+[^*/])*\*+"/"  ; /* Ignorer les commentaires de type C */
"static" { print_token("STATIC", yytext); return STATIC; }
"int" { print_token("TYPE", yytext); return TYPE; }
"char" { print_token("TYPE", yytext); return TYPE; }
[0-9]+ { print_token("NUM", yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { print_token("IDENT", yytext); return IDENT; }
"==" { print_token("EQ", yytext); return EQ; }
"=" { print_token("EQ", yytext); return EQ; }
">"|"<"|"<="|">=" { print_token("ORDER", yytext); return ORDER; }
"+" { print_token("ADDSUB", yytext); return ADDSUB; }
"*"|"/"|"%" { print_token("DIVSTAR", yytext); return DIVSTAR; }
"||" { print_token("OR", yytext); return OR; }
"&&" { print_token("AND", yytext); return AND; }
";" ;
[ \t\n]+   {lineno ++;} /* Ignorer les espaces blancs */
. {return yytext[0]; }
%%

