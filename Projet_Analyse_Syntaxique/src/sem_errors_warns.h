#ifndef SEM_ERRORS_WARNS_H
#define SEM_ERRORS_WARNS_H


// Variables globales pour compter les erreurs et avertissements
extern int semantic_warns;
extern int semantic_errors;

// Déclarations des fonctions pour les erreurs et avertissements
void error_var_exists(int lineno);

void error_function_exists(const char* funcname, int lineno);

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

void warn_ret_int_func_void(int lineno);

void warn_ret_void_func(const char* funcsignType, int lineno);

void warn_global_unitialized(const char* varname, int lineno);

void warn_local_unitialized(const char* varname, const char* funcname, int lineno);

void error_void_cond(int lineno);


#endif // SEM_ERRORS_WARNS_H