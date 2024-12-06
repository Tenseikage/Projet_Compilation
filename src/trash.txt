%{
#include <stdio.h>
#include <stdlib.h>
#include "../inc/tree.h"

// Déclaration explicite de yyin
// IDENT '=' CHARACTER { $$ = makeNode(Declarateurs); addChild($$, makeNode(ident)); addChild($$, makeNode(Character)); }
// |  IDENT '=' NUM       { $$ = makeNode(Declarateurs); addChild($$, makeNode(ident)); addChild($$, makeNode(Num)); }
extern FILE *yyin;

void yyerror(const char *s);

Node* root;
extern char *yytext;
extern int lineno;
extern int yylineno;
int yylex(void);
%}

%union {
  Node *node;
  char ident[64];
  int num;
}
%left OR AND
%left ADDSUB
%left NOT
%left DIVSTAR
%left EQ ORDER

%token TYPE VOID IF ELSE WHILE RETURN OR AND EQ ORDER ADDSUB DIVSTAR NUM CHARACTER STATIC
%token <ident> IDENT
%type <node> Prog DeclVars Declarateurs DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp

%%

Prog:  DeclVars DeclFoncts { $$ = makeNode(Prog); addChild($$, $1); addChild($$, $2); root = $$;}
    ;

DeclVars:
       DeclVars TYPE Declarateurs ';' { $$=$1; addChild($$, makeNode(type)); addChild($$, $3); }
    |  { $$ = makeNode(DeclVars); }
    ;

Declarateurs:
       Declarateurs ',' IDENT { $$ = $1; addSibling($$, makeNode(ident)); }
    |  IDENT               { $$ = makeNode(Declarateurs); addChild($$, makeNode(ident)); }
    ;

DeclFoncts:
       DeclFoncts DeclFonct { $$ = $1; addSibling($$, $2); }
    |  DeclFonct { $$ = $1; }
    ;

DeclFonct:
       EnTeteFonct Corps { $$ = makeNode(DeclFonct); addChild($$, $1); addChild($$, $2); }
    ;

EnTeteFonct:
       TYPE IDENT '(' Parametres ')' { 
        Node* typed_func = makeNode(EnTeteFonct); addChild(typed, makeNode(type)); addChild($$, makeNode(ident)); addChild($$, makeNode(Parametres)); }
    |  VOID IDENT '(' Parametres ')' { $$ = makeNode(EnTeteFonct); addChild($$, makeNode(Void)); addChild($$, makeNode(ident)); addChild($$, makeNode(Parametres)); }
    ;

Parametres:
       VOID { $$ = makeNode(Parametres); addChild($$, makeNode(VOID)); }
    |  ListTypVar { $$ = $1; }
    |  {$$ = NULL;}
    ;

ListTypVar:
       ListTypVar ',' TYPE IDENT { $$ = $1; addSibling($$, makeNode(TYPE)); addSibling($$, makeNode(IDENT)); }
    |  TYPE IDENT { $$ = makeNode(ListTypVar); addChild($$, makeNode(TYPE)); addChild($$, makeNode(IDENT)); }
    ;

Corps:
    '{' DeclVars SuiteInstr '}' { $$ = makeNode(Corps); addChild($$, $2); addChild($$, $3); }
    ;

SuiteInstr:
       SuiteInstr Instr { $$ = $1; addSibling($$, $2); }
    | /* vide */ { $$ = makeNode(SuiteInstr); }
    ;

Instr:
       IDENT '=' Exp ';' { $$ = makeNode(Instr); addChild($$, makeNode(IDENT)); addChild($$, $3); }
    |  IF '(' Exp ')' Instr { $$ = makeNode(Instr); addChild($$, makeNode(IF)); addChild($$, $3); addChild($$, $5); }
    |  IF '(' Exp ')' Instr ELSE Instr { $$ = makeNode(Instr); addChild($$, makeNode(IF)); addChild($$, $3); addChild($$, $5); addChild($$, makeNode(ELSE)); addChild($$, $7); }
    |  WHILE '(' Exp ')' Instr { $$ = makeNode(Instr); addChild($$, makeNode(WHILE)); addChild($$, $3); addChild($$, $5); }
    |  IDENT '(' Arguments ')' ';' { $$ = makeNode(Instr); addChild($$, makeNode(IDENT)); addChild($$, $3); }
    |  RETURN Exp ';' { $$ = makeNode(Instr); addChild($$, makeNode(Return)); addChild($$, $2); }
    |  RETURN ';' { $$ = makeNode(Instr); addChild($$, makeNode(Return)); }
    |  '{' SuiteInstr '}' { $$ = $2; }
    |  ';' { $$ = makeNode(Instr); }
    ;

Exp:
    Exp OR TB { $$ = makeNode(Exp); addChild($$, $1); addChild($$, makeNode(OR)); addChild($$, $3); }
    |  TB { $$ = $1; }
    ;

TB:
    TB AND FB { $$ = makeNode(TB); addChild($$, $1); addChild($$, makeNode(AND)); addChild($$, $3); }
    |  FB { $$ = $1; }
    ;

FB:
    FB EQ M { $$ = makeNode(FB); addChild($$, $1); addChild($$, makeNode(EQ)); addChild($$, $3); }
    |  M { $$ = $1; }
    ;

M:
    M ORDER E { $$ = makeNode(M); addChild($$, $1); addChild($$, makeNode(ORDER)); addChild($$, $3); }
    |  E { $$ = $1; }
    ;

E:
    E ADDSUB T { $$ = makeNode(E); addChild($$, $1); addChild($$, makeNode(ADDSUB)); addChild($$, $3); }
    |  T { $$ = $1; }
    ;

T:
    T DIVSTAR F { $$ = makeNode(T); addChild($$, $1); addChild($$, makeNode(DIVSTAR)); addChild($$, $3); }
    |  F { $$ = $1; }
    ;

F:
    ADDSUB F { $$ = makeNode(F); addChild($$, makeNode(ADDSUB)); addChild($$, $2); }
    |  '!' F { $$ = makeNode(F); addChild($$, makeNode('!')); addChild($$, $2); }
    |  '(' Exp ')' { $$ = $2; }
    |  NUM { $$ = makeNode(F); addChild($$, makeNode(Num)); }
    |  IDENT { $$ = makeNode(F); addChild($$, makeNode(ident)); }
    ;

Arguments:
    ListExp { $$ = $1; }
    | /* vide */ { $$ = makeNode(Arguments); }
    ;

ListExp:
    ListExp ',' Exp { $$ = $1; addSibling($$, $3); }
    |  Exp { $$ = $1; }
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
    yyparse();
    printTree(root);
    return 0;
}
