%{
#include <stdio.h>
#include <stdlib.h>
// 72,52/100

void yyerror(const char *s);


extern char *yytext;
extern int lineno;
extern int yylineno;
int yylex(void);
%}


%left OR AND
%left ADDSUB
%left NOT
%left DIVSTAR
%left EQ ORDER

%token TYPE VOID IF ELSE WHILE RETURN OR AND EQ ORDER ADDSUB DIVSTAR NUM CHARACTER STATIC IDENT
%expect 1
%%

//Programme principal
Prog:  DeclVars DeclFoncts 
    ;

//Déclaration de variables locales
DeclVars:
       DeclVars TYPE Declarateurs ';' //{ printf("Variable globale\n"); }
    |  DeclVars STATIC TYPE Declarateurs ';' {yyerror("Variable globale statique"); return 1;};
    |
    ;

Declarateurs:
       Declarateurs ',' IDENT 
    |  IDENT             
    ;

DeclFoncts:
       DeclFoncts DeclFonct 
    |  DeclFonct 
    ;

DeclFonct:
       EnTeteFonct Corps 
    ;

EnTeteFonct:
       TYPE IDENT '(' Parametres ')' 
    |  VOID IDENT '(' Parametres ')' 
    ;

Parametres:
       VOID 
    |  ListTypVar 
    ;

ListTypVar:
       ListTypVar ',' TYPE IDENT 
    |  TYPE IDENT 
    ;

Corps:
    '{' DeclVarsLocale SuiteInstr '}' 
    ;

//Déclaration de variable locales
DeclVarsLocale:
        DeclVarsLocale STATIC TYPE Declarateurs ';' //{ printf("Variable locale statique\\n"); }
    |   DeclVarsLocale TYPE Declarateurs ';'
    |
;

SuiteInstr:
       SuiteInstr Instr 
    | 
    ;

Instr:
       IDENT '=' Exp ';' 
    |  IF '(' Exp ')' Instr 
    |  IF '(' Exp ')' Instr ELSE Instr 
    |  WHILE '(' Exp ')' Instr 
    |  IDENT '(' Arguments ')' ';' 
    |  RETURN Exp ';' 
    |  RETURN ';' 
    |  '{' SuiteInstr '}' 
    |  ';' 
    ;

Exp:
    Exp OR TB 
    |  TB 
    ;

TB:
    TB AND FB 
    |  FB 
    ;

FB:
    FB EQ M 
    |  M 
    ;

M:
    M ORDER E 
    |  E 
    ;

E:
    E ADDSUB T 
    |  T 
    ;

T:
    T DIVSTAR F 
    |  F 
    ;

F:
    ADDSUB F 
    |  '!' F 
    |  '(' Exp ')' 
    |  NUM 
    |  IDENT 
    |  CHARACTER
    |  IDENT '(' Arguments ')'
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

int main(int argc, char **argv) {
    return yyparse();
}
