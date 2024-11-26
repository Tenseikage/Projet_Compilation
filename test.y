%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
%}

%token TYPE IDENT NUM EQ ORDER ADDSUB DIVSTAR STATIC

%%
program:
    global_declarations /*Programme contenant les déclarations globales*/
    ;

global_declarations:
    global_declaration
    | global_declarations global_declaration
    ;

global_declaration:
    TYPE IDENT ';'  /* Déclaration globale autorisée */
    | function_definition
    ;

function_definition:
    TYPE IDENT '(' ')' '{' local_declarations statements '}'
    ;

local_declarations:
    /* Déclarations locales, y compris les variables statiques */
    local_declaration
    | local_declarations local_declaration
    ;

local_declaration:
    TYPE IDENT ';'
    | STATIC TYPE IDENT ';'
    ;

statements:
    statement
    | statements statement
    ;

statement:
    /* Ajoutez ici les règles pour les différentes instructions */
    ;

%%

int main(int argc, char **argv) {
    ++argv, --argc;  /* Ignorer le nom du programme */
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erreur: %s\n", s);
}

