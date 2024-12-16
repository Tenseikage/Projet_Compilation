%{   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"


// Déclaration explicite de yyin
extern FILE *yyin;

void yyerror(const char *s);

Node* root;
extern char *yytext;
extern int lineno;
extern int yylineno;
int yylex(void);
void yyerror(const char *s);

// Ajout aux feuilles de l'arbre leur valeur
char *strdup(const char *s) {
    size_t len = strlen(s);
    char *dup = malloc(len + 1);
    if (dup != NULL) {
        strcpy(dup, s);
    }
    return dup;
}
%}

%union {
  Node *node;
  char type[10];
  char ident[64];
  char byte[1];
  char letter[1];
  char order[2];
  int num;
}
%precedence IF 
%precedence ELSE 
%left OR AND
%left ADDSUB
%left NOT
%left DIVSTAR
%left EQ ORDER


%token VOID IF ELSE WHILE RETURN OR AND EQ STATIC
%token<type> TYPE
%token<ident> IDENT
%token<num> NUM
%token <byte> ADDSUB DIVSTAR
%token<letter> CHARACTER
%token<order> ORDER 
%type <node> Prog DeclVars DeclVarsLocale Declarateurs DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%%

Prog:  DeclVars DeclFoncts { $$ = makeNode(Prog); 
    if($1->firstChild == NULL){
         addChild($$, NULL);
    } else {
        addChild($$, $1);
    }
    addChild($$, $2); root = $$;}
    ;

DeclVars:
       DeclVars TYPE Declarateurs ';' { 
       $$ = $1;
       // Vesion père unique, plusieurs fils
       Node* nodeType1 = makeNode(type);
       nodeType1->type = strdup($2);
       addChild($$, nodeType1); addChild($$, $3); }
    |  DeclVars STATIC TYPE Declarateurs {yyerror("Variable globale statique"); return 1;}
    |  { $$ = makeNode(DeclVars); }
    ;

Declarateurs:
       Declarateurs ',' IDENT { $$ = $1;
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($3);
       addSibling($$, nodeIdent); }
    |  IDENT  { $$ = makeNode(ident);
       $$->ident = strdup($1); }
    ;

DeclFoncts:
       DeclFoncts DeclFonct { $$ = makeNode(DeclFoncts); addChild($$,$1); addChild($$, $2); }
    |  DeclFonct { $$ = $1; }
    ;

DeclFonct:
       EnTeteFonct Corps { $$ = makeNode(DeclFonct); addChild($$, $1); addChild($$, $2); }
    ;

EnTeteFonct:
       TYPE IDENT '(' Parametres ')' { $$ = makeNode(EnTeteFonct); 
       Node* nodeType = makeNode(type);
       nodeType->type = strdup($1);
       addChild($$, nodeType); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($2);
       addChild($$, nodeIdent); 
       addChild($$, $4); }
    |  VOID IDENT '(' Parametres ')' { $$ = makeNode(EnTeteFonct); 
       addChild($$, makeNode(Void)); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($2);
       addChild($$,nodeIdent); 
       addChild($$, $4); }
    ;

Parametres:
       VOID {$$ = makeNode(Parametres); addChild($$, makeNode(Void)); }
    |  ListTypVar { $$ = makeNode(Parametres); addChild($$, $1); }
    ;

ListTypVar:
       ListTypVar ',' TYPE IDENT { $$ = $1;
       Node* nodeType = makeNode(type);
       nodeType->type = strdup($3); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($4);
       addChild($$, nodeType); addChild($$, nodeIdent); }
    |  TYPE IDENT { $$ = makeNode(ListTypVar); 
       Node* nodeType = makeNode(type);
       nodeType->type = strdup($1);
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($2);
       addChild($$, nodeType); addChild($$, nodeIdent); }
    ;

Corps:
    '{' DeclVarsLocale SuiteInstr '}' { $$ = makeNode(Corps); 
    if ($2->firstChild == NULL){
        addChild($$, NULL);
    } else {
         addChild($$, $2);
    }
    addChild($$, $3); }
    ;

DeclVarsLocale:
        DeclVarsLocale STATIC TYPE Declarateurs ';' { $$ = $1;
        Node* elem = makeNode(Static);
        Node* nodeType = makeNode(type);
        nodeType->type = strdup($3);
        addSibling(elem,nodeType);
        addChild($$,elem);
        addChild($$,$4);}
    |   DeclVarsLocale TYPE Declarateurs ';' { 
        $$ = $1;  
        Node* nodeType = makeNode(type);
        nodeType->type = strdup($2);
        addChild($$, nodeType); 
        addChild($$, $3); }
    |   {$$ = makeNode(DeclVarsLocale);}
;

SuiteInstr:
       SuiteInstr Instr { $$ = $1; addChild($$, $2); }
    | { $$ = makeNode(SuiteInstr); }
    ;

Instr:
       IDENT '=' Exp ';' { $$ = makeNode(Instr); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($1);
       addChild($$, nodeIdent); addChild($$, $3); }
    |  IF '(' Exp ')' Instr %prec IF { $$ = makeNode(Instr); addChild($$, makeNode(If)); addChild($$, $3); addChild($$, $5); }
    |  IF '(' Exp ')' Instr ELSE Instr %prec ELSE { $$ = makeNode(Instr); addChild($$, makeNode(If));
       //Node* exp = makeNode(Exp); 
       addChild($$, $3); addChild($$, $5); addChild($$, makeNode(Else)); addChild($$, $7); }
    |  WHILE '(' Exp ')' Instr { $$ = makeNode(Instr); addChild($$, makeNode(While)); addChild($$, $3); addChild($$, $5); }
    |  IDENT '(' Arguments ')' ';' { $$ = makeNode(Instr); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->ident = strdup($1);
       addChild($$, nodeIdent); addChild($$, $3); }
    |  RETURN Exp ';' {  $$ = makeNode(Instr); addChild($$, makeNode(Return)); addChild($$, $2); }
    |  RETURN ';' { $$ = makeNode(Instr); addChild($$, makeNode(Return)); }
    |  '{' SuiteInstr '}' { $$ = $2; }
    |  ';' { $$ = makeNode(Instr); }
    ;

Exp:
    Exp OR TB { $$ = makeNode(Exp); addChild($$,$1); addChild($$, makeNode(Or)); addChild($$, $3); }
    |  TB { $$ = $1; }
    ;

TB:
    TB AND FB { $$ = makeNode(TB); addChild($$, $1); addChild($$, makeNode(And)); addChild($$, $3); }
    |  FB { $$ = $1; }
    ;

FB:
    FB EQ M { $$ = makeNode(FB); addChild($$, $1); addChild($$, makeNode(Eq)); addChild($$, $3); }
    |  M { $$ = $1; }
    ;

M:
    M ORDER E { $$ = makeNode(M); addChild($$, $1); 
    Node* nodeOrder = makeNode(Order);
    nodeOrder->order = strdup($2);
    addChild($$, nodeOrder); addChild($$, $3); }
    |  E { $$ = $1; }
    ;

E:
    E ADDSUB T { $$ = makeNode(E); addChild($$, $1);
    Node* operator = makeNode(Addsub);
    operator->sign = strdup($2);
    addChild($$, operator); addChild($$, $3); }
    |  T { $$ = $1; }
    ;

T:
    T DIVSTAR F { $$ = makeNode(T); addChild($$, $1); 
    Node* operator = makeNode(divstar);
    operator->sign = strdup($2);
    addChild($$, operator); addChild($$, $3); }
    |  F { $$ = $1; }
    ;

F:
    ADDSUB F { $$ = makeNode(F); addChild($$, makeNode(Addsub)); addChild($$, $2); }
    |  '!' F { $$ = makeNode(F); addChild($$, makeNode(Not)); addChild($$, $2); }
    |  '(' Exp ')' { $$ = $2; }
    |  NUM { 
        $$ = makeNode(Num); 
        $$->value = $1; 
        
    }
    |  CHARACTER {$$ = makeNode(Character);
       $$->letter = strdup($1);}
    |  IDENT { $$ = makeNode(ident);
               $$->ident = strdup($1); }
    |  IDENT '(' Arguments ')' {$$ = makeNode(ident);
       $$->ident = strdup($1);}
    ;

Arguments:
    ListExp { $$ = $1; }
    | { $$ = makeNode(Arguments); }
    ;

ListExp:
    ListExp ',' Exp { $$ = $1; addSibling($$, $3); }
    |  Exp { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur de syntaxe à la ligne %d : %s", lineno, s);
    // Afficher le lexème ou caractère qui a provoqué l'erreur
    if (yytext[0] != '\0') {
        fprintf(stderr, " - lexème : '%s'\n", yytext);
    } else {
        fprintf(stderr, "\n");
    }
}

int main(int argc,char *argv[]) {
    // Afficher l'arbre fait planter le bac à sable
    if (argc < 2) {
        help(argv[0]);
        return 0;
    } else if (args_choice(argc, argv) == 1){
        if(!yyparse()){
            fprintf(stdout, "Affichage de l'arbre : \n");
            printTree(root);
            deleteTree(root);
            return 0;
        } else{
            fprintf(stderr, "Affichage de l'arbre impossible ! \n");
            return 1;
        }
    }
    
}
