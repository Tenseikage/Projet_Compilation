#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128


/**
 * @author Christophe TARATIBU
 */
extern int global_offset;
extern int local_offset;


// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	char* type; // type de la variable
	int isStatic; // Vérifie si la variable est statique
	int lineno; // Ligne où est positionnée la variable
	int size; // Nombre d'octets utilisé par la variable
	int offset; // position dans le segment de mémoire
	int is_affected; // Vérifie si la variable a été affectée
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

// Table de symboles pour les fonctions
typedef struct symb_tab_funcs {
	Symbol_table_function* tab_funcs; // Contient les tables de symbole propre aux fonctions
	int table_size; // Taille de la table de fonctions
	int index_tab; // Index dans le tableau
} Symbol_table_functions;

// Type de la table de symboles
typedef enum {
	LOCAL,
	GLOBAL,
	FUNCTION,
	VARS
} TableType;

// Prototype des fonctions
/**
 * Remplit la table de symboles d'une fonction (table de symboles variables globales)
 * @param tab : Table de symboles
 * @param type : Type de la table
 * @param var : Variable à ajouter
 */
void fill_symb_tab(void* tab, TableType type, Node* var);
/**
 * Affiche la table de symboles (Globale et Fonctions)
 * @param tab : Table de symboles
 * @param type : Type de la table
 */
void display_symb_tab(void* tab, TableType type);

/**
 * Initialise une table de symbole
 * @param type : Type de la table
 * @return : Pointeur vers la table de symbole
 */
void* init_table(TableType type);
/**
 * Remplit la table des symbole des fonctions
 * @param tab : Table de symboles
 * @param types : Type de la table
 * @param root : Arbre syntaxique
 * @param index : Index de la table
 * @return : Pointeur vers la table de symbole
 */
void fill_symb_tab_func(Symbol_table_functions* tab,TableType types, Node* root, int* index);
/**
 * Initialise la table des symboles des fonctions
 * @return : Pointeur vers la table de symbole
 */
Symbol_table_functions* init_symb_tab_func(void);
/**
 * Libère les tables de symboles
 * @param global_tab : Table des symboles globales
 * @param funcs_tab : Table des symboles des fonctions
 */
void free_all_tables(Symbol_table_global* global_tab, Symbol_table_functions* funcs_tab) ;

/**
 * Vérifie les variables du corps de la fonction
 * @param root : Arbre syntaxique
 * @param global_tab : Table des symboles globales
 * @param tab_funcs : Table des symboles des fonctions
 * @param funcname : Nom de la fonction
 * 
 */

void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs,char* funcname);

/**
 * Vérifie qu'une variable est dans la table des symboles
 * @param tab : Table de symboles
 * @param type : Type de la table
 * @param name : Nom de la variable
 * @return : ligne de la variable si la variable est dans la table, 0 sinon
 */
int is_var_in_table(void* tab, TableType type, char* name);


/**
 * Vérifie qu'une fonction est dans la table des symboles
 * @param tab : Table de symboles
 * @param funcname : Nom de la fonction
 * @return : Type de la fonction si la fonction est dans la table, NULL sinon
 */
char* is_func_in_tab(Symbol_table_functions* tab, const char* funcname);

/**
 * Renvoie le nombre de paramètres d'une fonction
 * @param tab : Table de symboles
 * @param funcname : Nom de la fonction
 * @return : Nombre de paramètres de la fonction
 * @return : 0 si la fonction n'est pas dans la table
 * @return : -1 si la table est NULL
 */
int nb_params_func(Symbol_table_functions* tab, const char* funcname);


/**
 * Ajoute des fonctions natives à la table des symboles
 * @param tab_funcs : Table des symboles des fonctions
 */
void add_native_functions(Symbol_table_functions* tab_funcs,int* index);

/**
 * Affiche la table des symboles
 * @param global_tab : Table des symboles globales
 * @param tab_funcs : Table des symboles des fonctions
 */
void display_final_symtab(Symbol_table_global* global_tab,Symbol_table_functions* tab_funcs);


#endif