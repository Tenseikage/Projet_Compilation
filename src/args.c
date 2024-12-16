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
                fprintf(stdout, "Affichage de l'arbre : \n");
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
            fprintf(stdout, "Affichage de l'arbre : \n");
            // Ajoutez le code pour gérer l'option --tree ici
            return 1;
        }
    }
	return -3; // Erreur quelconque
}

/*
void args_valids(int argc, char* argv[]){
    char c; 
    FILE* output_file = stdout;

    // Réinitialiser les variables globales de getopt
    optind = 1;
    opterr = 0;
    optopt = 0;
    optarg = NULL;

    // Deuxième passe pour traiter les arguments
    while ((c = getopt(argc, argv, ":n:i:o:cdfsvh")) != -1){
        switch (c) {
        case 'n':
            fprintf(stdout,"number of values: %d\n", atoi(optarg));
            break;

        case 'i':
           fprintf(stdout,"input stream : %s\n",optarg);
           break;

        case 'o':
            output_file = fopen(optarg,"w");
            fprintf(stdout,"output stream : %s \n",optarg);
            break;

        case 'c':
            fprintf(stdout,"type of values : char\n");
            break;

        case 'd':
            printf(stdout,"type of values : int\n");
            break;
        case 'f':
            fprintf(stdout,"type of values : float\n");
            break;
        case 's':
            fprintf(stdout,"sort values : yes\n");
            break;
        case 'v':
            fprintf(stdout,"verbose mode : yes\n");
            break;
        case 'h':
            help(argv[0]);
            break;
        default:
            break;
        }
    }
}
*/
/*int main(int argc, char *argv[]) {
    if (argc < 2) {
        help(argv[0]);
        return 1;
    }
    if (args_case_check(argc,argv) == -1){
        return -1;
    } else {
        args_valids(argc,argv);
        return 0;
    }
    return 0;
}*/