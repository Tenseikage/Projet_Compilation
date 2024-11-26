%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Déclaration des fonctions générées par Bison et Flex
int yyparse(void);
int yylex(void);
void yyerror(const char *s);
int yydebug = 1;
Node* root;
extern char *yytext;
extern int lineno;
extern int yylineno;


%}
%token TYPE IDENT NUM EQ ORDER ADDSUB DIVSTAR STATIC IF ELSE OR AND WHILE RETURN VOID CHARACTER


%%
//Programme pricipal
Prog:  DeclVars DeclFoncts
    ;
//Déclarations globales
DeclVars:
       DeclVars TYPE Declarateurs ';'
    |  STATIC TYPE Declarateurs';' 
    ;
// Liste des déclarateurs
Declarateurs:
       Declarateurs ',' IDENT
    |  IDENT
    ;
//Déclarations de fonctions
DeclFoncts:
       DeclFoncts DeclFonct
    |  DeclFonct
    ;
// Déclaration d'une fonction
DeclFonct:
       EnTeteFonct Corps
    ;
// En tête d'une fonction
EnTeteFonct:
       TYPE IDENT '(' Parametres ')'
    |  VOID IDENT '(' Parametres ')'
    ;
// Paramètres d'une fonction
Parametres:
       VOID
    |  ListTypVar
    ;
// Liste déclarations de variables typées
ListTypVar:
       ListTypVar ',' TYPE IDENT
    |  TYPE IDENT
    ;
//Corps d'une fonction
Corps: '{'DeclVars SuiteInstr '}' 
    ;
// Liste d'instructions
SuiteInstr:
       SuiteInstr Instr
    |
    ;
// Instruction
Instr:
       IDENT '=' Exp ';'
    |  IF '(' Exp ')' Instr
    |  IF '(' Exp ')' Instr ELSE Instr
    |  WHILE '(' Exp ')' Instr
    |  IDENT '(' Arguments  ')' ';'
    |  RETURN Exp ';'
    |  RETURN ';'
    |  '{' SuiteInstr '}'
    |  ';'
    ;
//Exprerssion
Exp :  Exp OR TB
    |  TB
    ;
TB  :  TB AND FB
    |  FB
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E
    |  E
    ;
E   :  E ADDSUB T
    |  T
    ;    
T   :  T DIVSTAR F 
    |  F
    ;
F   :  ADDSUB F
    |  '!' F
    |  '(' Exp ')'
    |  NUM
    |  CHARACTER
    |  IDENT
    |  IDENT '(' Arguments  ')'
    ;
Arguments:
       ListExp
    |
    ;
ListExp:
       ListExp ',' Exp
    |  Exp
    ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur de syntaxe à la ligne %d : %s", yylineno, s);
    // Afficher le caractère qui a provoqué l'erreur
    if (yytext[0] != '\0') {
        fprintf(stderr, " - Caractère : '%s'\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }
}

int main(){
    yyparse();
    return 0;
}