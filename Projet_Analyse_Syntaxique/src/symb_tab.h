#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128

// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	int type;
	int isStatic;
} Data;

// Table desymboles

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
	Data* vars; // Paramètres de f
	Symbol_table_locale * tab;
} Symbol_table_function;

typedef struct symb_tab_funcs {
	Symbol_table_function* tab; // Contient les tables de symbole propre aux fonctions
} Symbol_table_functions;

typedef enum {
	LOCAL,
	GLOBAL,
	FUNCTION
} TableType;

// Prototype des fonctions
void add_var(void* tab, TableType type, const char* name, label_t label, int lineno,int state);
void fill_symb_tab(void* tab, TableType type, Node* var);
void display_symb_tab(void* tab, TableType type);
void* init_table(TableType type);
//void free_table(void* tab, TableType type);




#endif