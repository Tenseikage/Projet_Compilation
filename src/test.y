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
// Addsiblings declvars
// Add siblings decFonction
//Faire des makenodes au début et addChild
// Grammaire modifiée

%}
%union { 
    int num;
    char *str;
}

%token <str> TYPE STATIC VOID IF ELSE WHILE CHARACTER AND OR RETURN
%token <str> IDENT
%token <num> NUM
%token EQ ORDER ADDSUB DIVSTAR

%left OR AND
%left ADDSUB
%left NOT
%left DIVSTAR
%left EQ ORDER

%%
//Programme pricipal
Prog:  DeclVars 
    |DeclFoncts
    ;
//Déclarations de variables(globales et statiques)
DeclVars:
       DeclVars TYPE Declarateurs ';'
    |  TYPE Declarateurs ';'
    |  DeclVars STATIC TYPE Declarateurs';' {printf("variable locale statique \n");}
    |  STATIC TYPE Declarateurs';' {yyerror("Variable globale statique");};
    ;
// Liste des déclarateurs
Declarateurs:
       Declarateurs ',' IDENT
    |  IDENT '=' CHARACTER {printf("Affectation caractère \n");}
    |  IDENT '=' NUM    {printf("Affectation numérque \n");}
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
       TYPE IDENT '(' Parametres ')' { printf("Fonction typée: %s\n", $2); }
    |  VOID IDENT '(' Parametres ')' { printf("Fonction void: %s\n", $2); }
    ;
// Paramètres d'une fonction
Parametres:
       VOID
    |  ListTypVar
    |
    ;
// Liste déclarations de variables typées
ListTypVar:
       ListTypVar ',' TYPE IDENT
    |  TYPE IDENT
    ;
//Corps d'une fonction
Corps: '{'DeclVars SuiteInstr '}' {printf("Corps de fonction \n");}
    ;
// Liste d'instructions
SuiteInstr:
       SuiteInstr Instr
    |
    ;
// Instruction
Instr:
       IDENT '=' Exp ';' {printf("identificateur %s",$1);}
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