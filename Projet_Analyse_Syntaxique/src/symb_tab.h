#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128




// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	char* type; // type de la variable
	int isStatic; // Vérifie si la variable est statique
	int lineno; // Ligne où est positionnée la variable
} Data;



// Table de symboles

typedef struct symb_table {
	Data* vars;
	int table_size;
	int index_tab;
} Symbol_table_locale;

// Table valeurs globales
typedef struct symb_table_global {
	Data* vars; // Tableau de variables globales
	int table_size; // Taille du tableau
	int index_tab; // Position dans le tableau
} Symbol_table_global;

// Table de symboles pour les fonctions
typedef struct symb_table_func {
	char name[IDENT_LENGTH];
	char* returnType; //Type de retour de la fonction
	Data* vars; // Paramètres de fonctions
	int tabv_size; // Taille du tableau local
	int index_tabv; // Position dans le tableau local
	int lineno; // Ligne où se trouve la fonction
	Symbol_table_locale * local_tab; // Table de symboles variables locales
} Symbol_table_function;

typedef struct symb_tab_funcs {
	Symbol_table_function* tab_funcs; // Contient les tables de symbole propre aux fonctions
	int table_size; // Taille de la table de fonctions
	int index_tab; // Index dans le tableau
} Symbol_table_functions;

typedef enum {
	LOCAL,
	GLOBAL,
	FUNCTION,
	VARS
} TableType;

// Prototype des fonctions
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
/**
 * Libère les tables de symboles
 */
void free_all_tables(Symbol_table_global* global_tab, Symbol_table_functions* funcs_tab) ;

/**
 * Vérifie que les variables globales et noms de fonction n'ont pas le même nom
 */
int check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab);

/**
 * Vérifie que les variables locales et paramètres de fonction n'ont pas le même nom
 */
int check_param_local_vars(Symbol_table_functions* tab);


#endif