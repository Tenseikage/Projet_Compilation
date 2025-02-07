#ifndef __SYMB_TAB_H__
#define __SYMB_TAB_H__
#define IDENT_LENGTH 128
#define TYPE_LENGTH 32

// Donnée d'une variable
typedef struct datas {
	char name[IDENT_LENGTH]; // Nom de la variable
	char type [TYPE_LENGTH]; // Type de la variable
} Data;

// Table desymboles

typedef struct symb_table {
	Data* vars;
	int table_size;
} Symbol_table;

// Prototype des fonctions



#endif