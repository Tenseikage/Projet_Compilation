#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include<getopt.h>
#include<stdlib.h>
#include "args.h"

void help(char* data){
    if (!data) return;
    fprintf(stdout,"usage : %s ./tpcc [OPTIONS] File.tpc \n", data);
    fprintf(stdout,"-t, --tree : Affichage de l'arbre \n");
    fprintf(stdout,"-h, --help : Affiche l'aide\n");
    fprintf(stdout,"Les autres options seront ignorés\n");
}


int args_choice(int argc, char* argv[]) {
    int opt;
    int result = -3;
    static struct option long_options[] = {
        {"help",    no_argument, 0, 'h'},
        {"tree",    no_argument, 0, 't'},
        {"symtabs", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    opterr = 0;

    while ((opt = getopt_long(argc, argv, "hts", long_options, NULL)) != -1) {
        switch (opt) {
            case 'h':
                help(argv[0]);
                return 0;
            case 't':
                return 1;
            case 's':
                return 2;
            case '?':
                if (optopt) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Option inconnue : -%c\n", optopt);
                } else if (argv[optind - 1]) {
                    fprintf(stderr, "\033[1;31mErreur\033[0m: Option inconnue : %s\n", argv[optind - 1]);
                }
                return -3;
            default:
                return -3;
        }
    }

    if (optind < argc && argv[optind][0] == '-') {
        fprintf(stderr, "\033[1;31mErreur\033[0m: Option inconnue : %s\n", argv[optind]);
        return -3;
    }

    return result;
}

