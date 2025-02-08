#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include<getopt.h>
#include<stdlib.h>
#include "args.h"

void help(char* data){
    if (!data) return;
    fprintf(stdout,"usage : %s [OPTIONS] \n", data);
    fprintf(stdout,"-t, --tree : Affichage de l'arbre \n");
    fprintf(stdout,"-h, --help : Affiche l'aide\n");
    fprintf(stdout,"Les autres options seront ignorés\n");
}


int args_choice(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0){
            help(argv[i]);
            return 0;
        } else if (strcmp(argv[i], "--tree") == 0 || (strcmp(argv[i], "-t") == 0)) {
            return 1;
        }
        
    } 
	return -3; // Erreur quelconque
}

