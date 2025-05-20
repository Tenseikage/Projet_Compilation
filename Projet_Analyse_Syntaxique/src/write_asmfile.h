#ifndef __WRITE_ASMFILE_H__
#define __WRITE_ASMFILE_H__
#include "symb_tab.h"

/**
 * @author Christophe TARATIBU
 */

/**
 *  Écrit l'entête du fichier asm avec les fonctions de base
 *  @param file : Fichier asm
 */
void write_asm_file_and_built_funcs(FILE *file);

/**
 *  Écrit la fin de fichier asm
 *  @param file : Fichier asm
*/
void write_end_asm_file(FILE *file);

/**
 *  Parocours l'arbre à la recherche de la fonction main
 * qui y est représenté
 * @param root : Arbre syntaxique
 * @param file : Fichier asm
 * @param global_tab : Table des variables globales
 * @param tab_funks : Table des fonctions
 */

 void parcours_arbre(Node* root,FILE* file,Symbol_table_global* global_tab,Symbol_table_functions* tab_funks);


/**
 * Initialisation du tableau contenant les variables globales et statiques
 * @param file : Fichier asm
 * @param global_tab : Table des variables globales
 * @param tab_funks : Table des fonctions
 */

 void write_asm_tab_global_static(FILE* file,Symbol_table_global* global_tab,Symbol_table_functions* tab_funks);



#endif