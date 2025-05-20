#ifndef __ARGS_H__
#define __ARGS_H__

/**
 * @author Christophe TARATIBU
 */

/**
 * Affiche l'aide du programme
 * @param data : Nom de l'option
 */
void help(char* data);

/**
 * Récupère les arguments de la ligne de commande
 * @param argc : Nombre d'arguments
 * @param argv : Arguments
 */
int args_choice(int argc, char* argv[]);

#endif