%{   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "tree.h"

void yyerror(const char *s);

Node* root;
extern char *yytext;
extern int lineno;
extern int line;
extern char * word;
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
  char word[10];
  int num;
}
%precedence IF 
%precedence ELSE 



%token VOID IF ELSE WHILE RETURN OR AND STATIC
%token<num> NUM
%token <word> EQ ADDSUB DIVSTAR TYPE ORDER IDENT CHARACTER
%type <node> Prog DeclVars DeclVarsLocale Declarateurs DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp
%%

Prog:  DeclVars DeclFoncts 
    { $$ = makeNode(Prog); 
    if($1->firstChild == NULL){
         addChild($$, NULL);
    } else {
        addChild($$, $1);
    }
    addChild($$, $2); root = $$;}
    ;

DeclVars:
       DeclVars TYPE Declarateurs ';' 
       { 
       $$ = $1;
       // Vesion père unique, plusieurs fils
       Node* nodeType1 = makeNode(type);
       nodeType1->word = strdup($2);
       addChild($$, nodeType1); addChild(nodeType1, $3); }

    |  DeclVars STATIC TYPE Declarateurs ';' {yyerror("Variable globale statique"); return 1;}
    |  { $$ = makeNode(DeclVars); }
    ;

Declarateurs:
       Declarateurs ',' IDENT 
       { $$ = $1;
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($3); // Autre variable liée à la première
       addSibling($$, nodeIdent); }
       
    |  IDENT  
      { $$ = makeNode(ident);
       $$->word = strdup($1); }
    ;

DeclFoncts:
       DeclFoncts DeclFonct 
       { $$ = $1; 
       addSibling($$, $2);
       }
    |  DeclFonct { $$ = $1; }
    ;

DeclFonct:
       EnTeteFonct Corps { $$ = makeNode(DeclFonct); addChild($$, $1); addSibling($1, $2);
		
       }
    ;

EnTeteFonct:
       TYPE IDENT '(' Parametres ')' 
       { $$ = makeNode(EnTeteFonct); 
       Node* nodeType = makeNode(type);
       nodeType->word = strdup($1);
       addChild($$, nodeType); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($2);
       addChild($$, nodeIdent); 
       addSibling($$, $4); }

    |  VOID IDENT '(' Parametres ')' 
       { 
       $$ = makeNode(Void); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($2);
       addChild($$,nodeIdent); 
       addSibling($$, $4); }
    ;

Parametres:
       VOID {$$ = makeNode(Void); }
    |  ListTypVar { $$ = makeNode(ListTypVar); addChild($$, $1); }
    ;

ListTypVar:
       ListTypVar ',' TYPE IDENT 
       { $$ = $1;
       Node* nodeType = makeNode(type);
       nodeType->word = strdup($3); 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($4);
       addSibling($$, nodeType);   addSibling(nodeType, nodeIdent); }

    |  TYPE IDENT { 
       Node* nodeType = makeNode(type);
       nodeType->word = strdup($1);
       $$ = nodeType;
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($2);
       addSibling(nodeType, nodeIdent);}
    ;

Corps:
    '{' DeclVarsLocale SuiteInstr '}' { $$ = makeNode(Corps); 
    if ($2->firstChild == NULL){
        addChild($$, NULL);
    } else {
         addChild($$, $2);
    }
    if ($3->firstChild == NULL){
     addChild($$, NULL);
    } else {
        addChild($$, $3);
    }
    }
    ;

DeclVarsLocale:
        DeclVarsLocale STATIC TYPE Declarateurs ';' { $$ = $1;
        Node* elem = makeNode(Static);
        Node* nodeType = makeNode(type);
        nodeType->word = strdup($3);
        addChild(elem,nodeType);
        addChild($$,elem);
        addChild(nodeType,$4);}
    |   DeclVarsLocale TYPE Declarateurs ';' { 
        $$ = $1;
        Node* elem = makeNode(NonStatic); 
        Node* nodeType = makeNode(type);
        nodeType->word = strdup($2);
        addChild(elem,nodeType);
        addChild($$, elem); 
        addChild(nodeType, $3); }
    |   {$$ = makeNode(DeclVarsLocale);}
;

SuiteInstr:
       SuiteInstr Instr { $$ = $1; addChild($$, $2); }
    | { $$ = makeNode(SuiteInstr); }
    ;

Instr:
       IDENT '=' Exp ';' {  
       $$ = makeNode(ident);
       $$->word = strdup($1);
       addChild($$, $3); }

    |  IF '(' Exp ')' Instr %prec IF { $$ = makeNode(If);
        Node* exp = makeNode (Exp);
        addChild(exp, $3);
		addChild($$, exp);
		addChild($$, $5); 
        }

    |  IF '(' Exp ')' Instr ELSE Instr %prec ELSE { 
       $$ = makeNode(If);
       Node* exp = makeNode (Exp);
       Node* nodeElse = makeNode(Else);
       addChild(exp,$3);
       addChild($$,exp);
       addChild($$,$5);
       addChild(nodeElse,$7);
       addSibling($$,nodeElse); 
       }



    |  WHILE '(' Exp ')' Instr { 
        $$ = makeNode(While);
        Node* exp = makeNode (Exp);
        addChild(exp,$3);
        addChild($$,exp);
        addChild($$,$5);
    }

    |  IDENT '(' Arguments ')' ';' { 
       Node* nodeIdent = makeNode(ident);
       nodeIdent->word = strdup($1);
       $$ = nodeIdent;
       addChild($$, $3);
    }
    

    |  RETURN Exp ';' {  $$ = makeNode(Return); addChild($$, $2); }

    |  RETURN ';' { $$ = makeNode(Return);
       addChild($$,makeNode(Void)); }

    |  '{' SuiteInstr '}' { $$ = $2; }

    |  ';' { $$ = makeNode(Instr); }
    ;

Exp:
    Exp OR TB { Node* NodeOr = makeNode(Or);
        addChild(NodeOr,$1);
        addChild(NodeOr,$3);
        $$ = NodeOr;
    }
    |  TB { $$ = $1; }
    ;

TB:
    TB AND FB { Node* NodeAnd = makeNode(And);
        addChild(NodeAnd,$1);
        addChild(NodeAnd,$3);
        $$ = NodeAnd;
    }
    |  FB { $$ = $1; }
    ;

FB:
    FB EQ M { Node * nodeEq = makeNode(Eq);
        nodeEq->word = strdup($2);
        addChild(nodeEq,$1);
        addChild(nodeEq,$3);
        $$ = nodeEq;
    }
    |  M { $$ = $1; }
    ;

M:
    M ORDER E { 
        Node* nodeOrder = makeNode(Order);
        nodeOrder->word = strdup($2);
        addChild(nodeOrder,$1); 
        addChild(nodeOrder, $3);
        $$ = nodeOrder; 
    }
    |  E { $$ = $1; }
    ;

E:
    E ADDSUB T {
        Node* operator = makeNode(Addsub);
        operator->word = strdup($2);
        addChild(operator,$1); 
        addChild(operator, $3);
        $$ = operator; 
    }
    |  T { $$ = $1; }
    ;

T:
    T DIVSTAR F { Node* operator = makeNode(divstar);
        operator->word = strdup($2);
        addChild(operator,$1); 
        addChild(operator, $3);
        $$ = operator; 
    }
    |  F { $$ = $1; }
    ;

F:
    ADDSUB F { 
        Node* operator = makeNode(Addsub);
        operator->word = strdup($1);
        addChild(operator,$2); 
        $$ = operator; 
        }
    |  '!' F {Node* notNode = makeNode(Not);
           notNode->word = strdup("!"); 
           addChild(notNode,$2);
           $$ = notNode;
           }
           
    |  '(' Exp ')' { $$ = $2; }
    |  NUM { 
        $$ = makeNode(Num); 
        $$->value = $1; 
        
    }
    |  IDENT { $$ = makeNode(ident);
               $$->word = strdup($1); }
    |  CHARACTER {$$ = makeNode(Character);
       $$->word = strdup($1);}
    |  IDENT '(' Arguments ')' {$$ = makeNode(ident);
       $$->word = strdup($1);
       //Node nodeArg = makeNode(Arguments);
       addChild($$,$3);}
    ;

Arguments:
    ListExp { $$ = makeNode(Arguments); addChild($$,$1);}
    | { $$ = makeNode(Void); }
    ;

ListExp:
    ListExp ',' Exp { $$ = $1; addSibling($$, $3); }
    |  Exp { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique à la ligne %d  (position %d : '%s')\n", lineno, line, yytext ? yytext : "inconnu");
    if (word) {
        fprintf(stderr, "%s\n", word);

        for(int i =0; i< line - 2;i++){
            fprintf(stderr, " ");
        }
        fprintf(stderr, "-^\n");
    }
}


