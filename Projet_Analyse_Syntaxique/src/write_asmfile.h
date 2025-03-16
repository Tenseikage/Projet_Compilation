#ifndef __WRITE_ASMFILE_H__
#define __WRITE_ASMFILE_H__

/**
 *  Écrit dans le fichier asm nouvellement crée
 */
void write_asm_file(FILE *file);

/**
 *  Écrit la fin de fichier asm
*/

void write_end_asm_file(FILE *file);

/**
 *  Convertit l'opérateur trouvé dans l'arbre asbstrait en mot
 */
char* asm_operator(char* op);

/**
 * Parcours l'arbre à la recherche d'opérations arithmétques et les
 * écrits sous la forme de code assembleur asm
 */
void parcours_operators(Node* root, FILE * file);

/**
 *  Parocours l'arbre à la recherche de la fonction main
 * qui y est représenté
 */

int parcours_arbre_main(Node* root);

#endif