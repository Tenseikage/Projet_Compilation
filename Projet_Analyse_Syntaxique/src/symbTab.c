#include "sympTab.h"
#include <stdio.h>

int is_identifier_in_symbtab(char* ident, symbTab* tab){
    for(int i = 0; i < tab->size; i++){
        if(strcmp(tab->tab[i].name, ident) == 0){
            return 1;
        }
    }
    return 0;
}

int add_symbol(symbTab* symbTab , char* ident, int value, int isConst, int isInt){
    if(is_identifier_in_symbtab(ident, symbTab)){
        return 0;
    }
    if(symbTab->size == symbTab->maxsize){
        symbTab->maxsize *= 2;
        symbTab->tab = realloc(symbTab->tab, symbTab->maxsize * sizeof(Variable));
    }
    symbTab->tab[symbTab->size].name = ident;
    symbTab->tab[symbTab->size].value = value;
    symbTab->tab[symbTab->size].isConst = isConst;
    symbTab->tab[symbTab->size].isInt = isInt;
    symbTab->size++;
    return 1;
}

symbTab* init_symbtab(){
    symbTab* tab = malloc(sizeof(symbTab));
    tab->size = 0;
    tab->maxsize = 10;
    tab->tab = malloc(tab->maxsize * sizeof(Variable));
    return tab;
}

