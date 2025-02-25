/* tree.h */

typedef enum {
  E,
  T,
  divstar,
  Prog,
  DeclVars,
  Declarateurs,
  DeclVarsLocale,
  DeclFoncts,
  DeclFonct,
  EnTeteFonct,
  Parametres,
  ListTypVar,
  Corps,
  SuiteInstr,
  Instr,
  Exp,
  Arguments,
  ListExp,
  type,
  ident,
  Void,
  If,
  Else,
  While,
  Return,
  Or,
  And,
  Eq,
  Order,
  Addsub,
  Num,
  Character,
  Static,
  Not,
  NonStatic
  /* Ajoutez d'autres labels si nécessaire */
} label_t;

typedef struct Node {
  label_t label;
  struct Node *firstChild, *nextSibling;
  int lineno;
  int value;
  char* word;
} Node;

Node *makeNode(label_t label);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);
int countLeaves(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling

