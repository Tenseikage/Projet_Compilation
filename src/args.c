#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include<getopt.h>
#include<stdlib.h>
#include "args.h"

void help(char* data){
    if (!data) return;
    fprintf(stdout,"usage : %s [options] \n", data);
    fprintf(stdout,"-t, --tree : Affichage de l'arbre \n");
    fprintf(stdout,"-h, --help : Affiche l'aide\n");
    fprintf(stdout,"Les autres options seront ignorés\n");
}


int args_choice(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ht")) != -1) {
        switch (opt) {
            case 'h':
                help(argv[0]);
                return 0;
            case 't':
                return 1;
            case '?':
                if (optopt == 'h' || optopt == 't') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint(optopt)) {
                    fprintf(stderr, "Option inconnue `-%c`.\n", optopt);
                } else {
                    fprintf(stderr, "Caractère d'option inconnue `\\x%x`.\n", optopt);
                }
                return -1;
            default:
                return -2;
        }
    }

    // Options longues
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            help(argv[i]);
            return 0;
        } else if (strcmp(argv[i], "--tree") == 0) {
            return 1;
        }
    }
	return -3; // Erreur quelconque
}

