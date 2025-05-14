
#include<stdio.h>
#include "sem_errors_warns.h"

int semantic_warns = 0;
int semantic_errors = 0;

void error_var_exists(int lineno){
	fprintf(stderr, "\033[1;31mErreur \033[0m: la variable existe déjà en ligne : %d\n", lineno);
	semantic_errors++;
}


void error_function_exists(const char* funcname,int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction '%s' déja présente dans le programme (ligne %d).\n", funcname,lineno);
	semantic_errors++;
}


void error_global_var_func(int line_var_global,int line_func){
	fprintf(stderr,"\033[1;31mErreur\033[0m: Même définition variable globale ligne : %d / Nom de fonction ligne : %d\n",line_var_global,line_func);
	semantic_errors++;
}


void error_same_var_param_func(const char* varname,int var_line){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Même définition variable locale / Paramètre de fonction. Nom : %s, Ligne : %d\n", varname,var_line);
    semantic_errors++;

}

void warn_implicit_conv_int_char(int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Conversion implicite de 'int' en 'char' (ligne %d).\n", lineno);
	semantic_warns++; 
}

void error_incomp_affect(const char* left_type,const char* func_ret_type,int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Affectation incompatible %s/%s (ligne %d)\n",left_type,func_ret_type,lineno);
	semantic_errors++;

}

/*void error_implicit_func_declare(const char* funcname, int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", funcname,lineno);
	semantic_errors++;
}*/
void warn_implicit_func_declare(const char* funcname, int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Fonction %s appelée mais non déclarée (ligne %d).\n", funcname,lineno);
	semantic_warns++;
}

void warn_div_by_zero(int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Division par zéro détectée dans une expression (ligne %d).\n", lineno);
	semantic_warns += 1;
}

void warn_no_return(const char* funcname){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Absence de return dans la fonction non void %s \n", funcname); 
	semantic_warns++;
}

void error_func_toofewargs(const char* funcname, int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Pas assez d'arguments dans la fonction %s appelée(ligne %d).\n", funcname, lineno);
	semantic_errors += 1;
}


void error_func_toomanyargs(const char* funcname, int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Beaucoup d'arguments dans la fonction %s appelée (ligne %d).\n", funcname, lineno);
	semantic_errors += 1;
}


void error_undeclare_var(const char* varname,int lineno){
    fprintf(stderr, "\033[1;31mErreur\033[0m: Variable '%s' utilisé mais non déclaré (ligne %d).\n", varname, lineno);  
	semantic_errors += 1;
}

void warn_ret_int_func_char(int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Retour implicite de 'int' dans une fonction de retour 'char' (ligne %d).\n", lineno);
	semantic_warns++;
}


void error_ret_value_func_void(int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Retour avec une valeur dans une fonction de retour void (ligne %d).\n",lineno);   
	semantic_errors++;
}


void error_ret_void_func(const char* funcsignType,int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Retour void dans une fonction de retour  %s (ligne %d).\n",funcsignType,lineno);
    semantic_errors++;
	 
}

void warn_global_unitialized(const char* varname, int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Variable globale '%s' déclarée mais non initialisée (ligne %d).\n",
		varname,lineno);
	semantic_warns++;
}


void warn_local_unitialized(const char* varname,const char* funcname,int lineno){
	fprintf(stderr, "\033[1;35mWarning\033[0m: Variable locale '%s' dans la fonction '%s' déclarée mais non initialisée (ligne %d).\n",
		varname,funcname,lineno);
	semantic_warns++;

}

void error_void_cond(int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: La condition du 'if' doit être de type arithmétique (ligne %d).\n",lineno);
	semantic_errors++;
}


void error_no_main(void){
	fprintf(stderr, "\033[1;31mErreur\033[0m: La fonction 'main' est absente du code\n");
    semantic_errors++;
}

void error_diff_main_ret(int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: La fonction 'main' doit être de type 'int' (ligne %d).\n",lineno);
    semantic_errors++;
}


void error_retour_incomp(const char* funcbody_ret,const char* func_ret_type,int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: Retour incompatible %s/%s (ligne %d)\n",funcbody_ret,func_ret_type,lineno);
	semantic_errors++;

}

void error_void_non_ignore(int lineno){
	fprintf(stderr,"\033[1;31mErreur\033[0m: Valeur void pas ignoré comme il se doit (ligne %d) \n", lineno);
	semantic_errors++;
}

void error_same_var_func(int lineno){
	fprintf(stderr,"\033[1;31mErreur\033[0m: Même nom de variable et de fonction (ligne %d) \n", lineno);
	semantic_errors++;
}

//void error_type_main
/*oid error_condition_ident(int lineno){
	fprintf(stderr, "\033[1;31mErreur\033[0m: La condition du 'if' doit être de type 'int' (ligne %d).\n",lineno);
	semantic_errors++;

}*/






