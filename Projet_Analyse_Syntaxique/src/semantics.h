#ifndef __SEMANTICS__H_
#define __SEMANTICS__H_

/**
 * @author Christophe TARATIBU
 */


/**Structure récupération partie droite expression  (cas d'opérations qui se suivent) */
typedef struct list_right{
	const char** list;
	int index;

} List_Right;

/**
 * Vérifie que les variables globales et noms de fonction n'ont pas le même nom
 * @param tab : Table des fonctions
 * @param global_tab : Table des variables globales
 */
void check_name_func_global(Symbol_table_functions* tab, Symbol_table_global* global_tab);

/**
 * Vérifie que les variables locales et paramètres de fonction n'ont pas le même nom
 * @param tab : Table des fonctions
 */
void check_param_local_vars(Symbol_table_functions* tab);


/**
 * Vérifie les variables et les paramètres de fonctions 
 * 	@param root : Arbre syntaxique
 * 	@param global_tab : Table des variables globales
 *  @param tab_funcs : Table des fonctions
 *  @param funcname : Nom de la fonction
 */

void check_variables(Node* root, Symbol_table_global* global_tab, Symbol_table_functions* tab_funcs,char* funcname);


/**
 * Vérifie que les variables sont bien initialisées
 * @param tab_funk : Table des fonctions
 * @param global_tab : Table des variables globales
*/
void check_unitialized_vars(Symbol_table_functions* tab_funk, Symbol_table_global* global_tab);


/**
 * Vérifie que la fonction main est bien présente
 * @param tab_funks : Table des fonctions
 */
void is_main_in_code(Symbol_table_functions* tab_funks);

/**
 * Vérifie que les variable locales n'ont pas le même nom entre elles
 * @param tab : Table des fonctions
 */
void same_var_name_func(Symbol_table_functions*tab);

/**
 * Récupère le type d'une variable
 * @param tab : Table symboles
 * @param type : Type de la table
 * @param name : Nom de la variable
 * @return : Type de la variable
 */
const char* get_var_type(void* tab, TableType type, const char* name);

#endif