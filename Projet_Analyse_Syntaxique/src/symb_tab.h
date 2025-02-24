#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128

// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	int type;
	int isStatic;
} Data;

// Table de symboles

typedef struct symb_table {
	Data* vars;
	int table_size;
	int index_tab;
} Symbol_table_locale;

// Table valeurs globales
typedef struct symb_table_global {
	Data* vars;
	int table_size;
	int index_tab;
} Symbol_table_global;

// Table de symboles pour les fonctions
typedef struct symb_table_func {
	char name[IDENT_LENGTH];
	int returnType; //Type de retour de la fonction
	Data* vars; // Paramètres de f
	Symbol_table_locale * local_tab; // Table de symboles variables locales
} Symbol_table_function;

typedef struct symb_tab_funcs {
	Symbol_table_function* tab_funcs; // Contient les tables de symbole propre aux fonctions
	int table_size;
	int index_tab;
} Symbol_table_functions;

typedef enum {
	LOCAL,
	GLOBAL,
	FUNCTION
} TableType;

// Prototype des fonctions
/**
 * Cette fonction ajoute une variable ou une fonction dans sa table
 */
void add_var(void* tab, TableType type, const char* name, label_t label, int lineno,int state);
/**
 * Replit la table de symboles d'une fonction (table de symboles variables golbales)
 */
void fill_symb_tab(void* tab, TableType type, Node* var);
/**
 * Affiche la table de symboles (Globale et Fonctions)
 */
void display_symb_tab(void* tab, TableType type);

/**
 * Initialise une table de symbole
 */
void* init_table(TableType type);
/**
 * Remplit la table des symbole des fonctions
 */
void fill_symb_tab_func(Symbol_table_functions* tab,TableType types, Node* root, int* index);
/**
 * Initialise la table des symboles des fonctions
 */
Symbol_table_functions* init_symb_tab_func(void);





#endif