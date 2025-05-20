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
 *  @param line_func : ligne de la fonction
 */
void error_global_var_func(int line_var_global, int line_func);

/**
 * Affiche une erreur de même définition variable locale / paramètre de fonction
 * @param varname : Nom de la variable
 * @param var_line : ligne de la variable
 */
void error_same_var_param_func(const char* varname, int var_line);

/**
 * Affiche un warning de conversion implicite de int vers char
 * @param lineno : Numéro de ligne
 */
void warn_implicit_conv_int_char(int lineno);

/**
 * Affiche une erreur d'affectation incompatible
 * @param left_type : Type de gauche
 * @param func_ret_type : type de retour de la fonction
 * @param lineno : Numéro de ligne
 */
void error_incomp_affect(const char* left_type, const char* func_ret_type, int lineno);

/**
 * Afiiche un warning de déclaration implicite de fonction
 * @param funcname : Nom de la fonction
 * @param lineno : Numéro de ligne
 */
void warn_implicit_func_declare(const char* funcname,int lineno);

/**
 * Affiche un warning de division par zéro
 * @param lineno : Numéro de ligne
 */
void warn_div_by_zero(int lineno);

/**
 * Affiche un warning d'absence de return dans une fonction
 * @param funcname : Nom de la fonction
 */
void warn_no_return(const char* funcname);

/**Affiche une erreur de nombre inférieur d'arguments dans une fonction
 * @param funcname : Nom de la fonction
 * @param lineno : Numéro de ligne
 */
void error_func_toofewargs(const char* funcname, int lineno);

/**
 * Affiche une erreur de nombre supérieur d'arguments dans une fonction
 * @param funcname : Nom de la fonction
 * @param lineno : Numéro de ligne
 */
void error_func_toomanyargs(const char* funcname, int lineno);

/**
 * Affiche une erreur de variable non déclarée
 * @param varname : Nom de la variable
 * @param lineno : Numéro de ligne
 */
void error_undeclare_var(const char* varname, int lineno);


/**
 * Affiche un warning de retour de valeur d'une fonction char
 * @param lineno : Numéro de ligne
 */
void warn_ret_int_func_char(int lineno);

/**
 * Affiche une erreur de retour de valeur d'une fonction void
 * @param lineno : Numéro de ligne
 */
void error_ret_value_func_void(int lineno);

/**
 * Affiche une erreur de retour de valeur d'une fonction void
 * @param funcsignType : Type de la fonction
 * @param lineno : Numéro de ligne
 */
void error_ret_void_func(const char* funcsignType, int lineno);

/**
 * Affiche un warning de variable globale non initialisée
 * @param varname : Nom de la variable
 * @param lineno : Numéro de ligne
 */
void warn_global_unitialized(const char* varname, int lineno);

/**
 * Affiche un warning de variable locale non initialisée
 * @param varname : Nom de la variable
 * @param funcname : Nom de la fonction
 * @param lineno : Numéro de ligne
 */
void warn_local_unitialized(const char* varname, const char* funcname, int lineno);

/**
 * Affiche une erreur de condition non arithmétique
 * @param lineno : Numéro de ligne
 */
void error_void_cond(int lineno);

/**
 * Affiche une erreur d'absence de fonction main
 */
void error_no_main(void);

/**
 * Affiche une erreur de type de retour différent de la fonction main
 * @param lineno : Numéro de ligne
 */
void error_diff_main_ret(int lineno);

/**
 * Affiche une erreur de type de retour incompatible
 * @param funcbody_ret : Type de retour de la fonction
 * @param func_ret_type : Type de la fonction
 * @param lineno : Numéro de ligne
 */
void error_retour_incomp(const char* funcbody_ret,const char* func_ret_type,int lineno);


/**
 * Affiche une erreur de type void non ignoré
 * @param lineno : Numéro de ligne
 */
void error_void_non_ignore(int lineno);

/**
 * Affiche une erreur de même nom de variable
 * @param lineno : Numéro de ligne
 */
void error_same_var_func(int lineno);
#endif // SEM_ERRORS_WARNS_H