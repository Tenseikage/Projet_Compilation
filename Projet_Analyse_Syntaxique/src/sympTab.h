typedef struct var{
    char *name;
    int value;
    int isConst;
    int isStatic;
    int isInt;
}Variable;

//table des symboles
typedef struct tab {
    Variable* tab;    
    int size;
    int maxsize;

}symbTab;

//tableau des tables de symboles
typedef struct tabofsymbtab {
    symbTab* FunctionTab; //tableaux des var de fonctions
    symbTab* globalTab; //tableaux des var globales
    int size;
    int maxsize;
}TabOfSymbTab;

//verif si un identificateur est déja dans la table
int is_identifier_in_symbtab(char* ident, symbTab* tab);

//ajout d'un symbole dans la table
int add_symbol(symbTab* tab, char* ident, int value, int isConst, int isInt);

//initialisation de la table
symbTab* init_symbtab();

//
void fill_symbtab(symbTab* tab);
