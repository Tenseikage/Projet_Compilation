#ifndef __SEMANTICS__H_
#define __SEMANTICS__H_


/**Structure récupération partie droite expression  (cas d'opérations qui se suivent) */
typedef struct list_right{
	const char** list;
	int index;

} List_Right;

/**
 * Vérifie que les variables globales et noms de fonction n'ont pas le même nom
 */
int check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab);

/**
 * Vérifie que les variables locales et paramètres de fonction n'ont pas le même nom
 */
int check_param_local_vars(Symbol_table_functions* tab);


/*Vérifie les variables et les paramètres de fonctions */

void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs,char* funcname);

#endif