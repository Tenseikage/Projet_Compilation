#ifndef __WRITE_ASMFILE_H__
#define __WRITE_ASMFILE_H__
#include "symb_tab.h"
/**
 *  Écrit dans le fichier asm nouvellement crée
 */
void write_asm_file(FILE *file);

/**
 *  Écrit la fin de fichier asm
*/

void write_end_asm_file(FILE *file);

/**
 *  Parocours l'arbre à la recherche de la fonction main
 * qui y est représenté
 */

 void parcours_arbre(Node* root,FILE* file,Symbol_table_global* global_tab);


/**
 * Initialisation du tableau contenant les variables globales
 */

 void write_asm_tab_global(FILE* file,Symbol_table_global* global_tab);


#endif