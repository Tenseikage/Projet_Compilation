#ifndef SEM_ERRORS_WARNS_H
#define SEM_ERRORS_WARNS_H

/**
 * @author Christophe TARATIBU
 */

// Variables globales pour compter les erreurs et avertissements
extern int semantic_warns;
extern int semantic_errors;

/**
 * Affiche une erreur de variable déja existante
 * @param lineno : Numéro de ligne
 */
void error_var_exists(int lineno);


/**
 * Affiche une erreur de fonction déja existante
 * @param funcname : Nom de la fonction
 * @param lineno : Numéro de ligne
 * 
 */
void error_function_exists(const char* funcname, int lineno);

/**
 *  Affiche une erreur de même définition variable globale / nom de fonction
 *  @param line_var_global : ligne de la variable globale
 *  
 */
void error_global_var_func(int line_var_global, int line_func);

void error_same_var_param_func(const char* varname, int var_line);

void warn_implicit_conv_int_char(int lineno);

void error_incomp_affect(const char* left_type, const char* func_ret_type, int lineno);

//void error_implicit_func_declare(const char* funcname, int lineno);
void warn_implicit_func_declare(const char* funcname,int lineno);

void warn_div_by_zero(int lineno);

void warn_no_return(const char* funcname);

void error_func_toofewargs(const char* funcname, int lineno);

void error_func_toomanyargs(const char* funcname, int lineno);

void error_undeclare_var(const char* varname, int lineno);

void warn_ret_int_func_char(int lineno);

void error_ret_value_func_void(int lineno);

void error_ret_void_func(const char* funcsignType, int lineno);

void warn_global_unitialized(const char* varname, int lineno);

void warn_local_unitialized(const char* varname, const char* funcname, int lineno);

void error_void_cond(int lineno);

void error_no_main(void);

void error_diff_main_ret(int lineno);

void error_retour_incomp(const char* funcbody_ret,const char* func_ret_type,int lineno);


void error_void_non_ignore(int lineno);

void error_same_var_func(int lineno);
#endif // SEM_ERRORS_WARNS_H