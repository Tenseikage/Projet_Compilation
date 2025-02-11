#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128

// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	int type;
} Data;

// Table desymboles

typedef struct symb_table {
	Data* vars;
	int table_size;
	int index_tab;
} Symbol_table;

// Table valeurs globales
typedef struct symb_table_global {
	Data* vars;
	int table_size;
	int index_tab;
} Symbol_table_global;


// Prototype des fonctions
void add_var(Symbol_table* tab,const char* name, label_t type, int lineno);
void fill_symb_tab(Symbol_table* tab, Node* var);
void display_symb_tab(Symbol_table* tab);
Symbol_table* init_table(void);





#endif