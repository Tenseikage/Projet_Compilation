%{
#include "tree.h"
#include "parser.tab.h" // Inclut les définitions générées par Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int lineno = 1;
int line = 1;
char* word = NULL;

void errorlex(const char *s) {
    fprintf(stderr, "Erreur lexicale à la ligne %d  (position %d : '%s')\n", lineno, line, yytext ? yytext : "inconnu");
    if (word) {
        fprintf(stderr, "%s\n", word);

        for(int i =0; i< line - 2;i++){
            fprintf(stderr, " ");
        }
        fprintf(stderr, "-^\n");
    }
}

void concat(char *text) {
    int new_length;
    if (word){
        new_length = strlen(word);
    } else {
        new_length = 0;
    }
    new_length = new_length + strlen(text) + 1;
    char *new_word = (char *)realloc(word, new_length);
    if (!new_word) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    word = new_word;
    if (!word[0]) {
       strcpy(word, text);
    }else {
        strcat(word, text);
    }
     
}


%}

%option noinput
%option nounput


%x COMMENT
%%

"//".*          ; /* Ignore les commentaires de type C */
"/*"            { BEGIN(COMMENT); } /* Commence un commentaire de type C */
<COMMENT>"*/"   { BEGIN(INITIAL); } /* Finit un commentaire de type C */
<COMMENT>\n     { lineno++; } /* Incrémente le compteur de lignes pour chaque nouvelle ligne dans un commentaire */
<COMMENT>.      ; /* Ignore les autres caractères dans un commentaire */
"int"           {line +=strlen(yytext); concat(yytext);strcpy(yylval.word,yytext); return TYPE; }
"static"        {line +=strlen(yytext); concat(yytext); return STATIC;}
"char"          {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext); return TYPE ;}
"void"          {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext); return VOID; }
"if"            {line +=strlen(yytext); concat(yytext); return IF; }
"else"          {line +=strlen(yytext); concat(yytext); return ELSE; }
"while"         {line +=strlen(yytext); concat(yytext);  return WHILE; }
"return"        {line +=strlen(yytext); concat(yytext);  return RETURN; }
"("             {line +=strlen(yytext); concat(yytext); return '(';}
")"             {line +=strlen(yytext); concat(yytext); return ')';}
"{"             {line +=strlen(yytext); concat(yytext); return '{';}
"}"             {line +=strlen(yytext); concat(yytext); return '}';}

[a-zA-Z_][a-zA-Z0-9_]* {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext);  return IDENT; } // Identificateurs
[0-9]+                 {line +=strlen(yytext); concat(yytext); yylval.num = atoi(yytext); return NUM; }   // Nombres entiers

"="             {line +=strlen(yytext); concat(yytext);  return '='; }
"!"             {line +=strlen(yytext); concat(yytext);  return '!';} 
";"             {line +=strlen(yytext); concat(yytext); return ';'; }
","             {line +=strlen(yytext); concat(yytext); return ',';}
"+"|"-"         {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext); return ADDSUB; }
"*"|"/"|"%"        {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext);  return DIVSTAR; }
"&&"            {line +=strlen(yytext);  concat(yytext); return AND; }
"||"            {line +=strlen(yytext); concat(yytext);  return OR; }
"=="|"!="       {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext); return EQ;}
"<"|">"|"<="|">=" {line +=strlen(yytext); concat(yytext);  strcpy(yylval.word, yytext); return ORDER;}
'(\\[a-z]|[^\'])' {line +=strlen(yytext); concat(yytext); strcpy(yylval.word,yytext); return CHARACTER;}
\n              { lineno++; word = NULL; line = 1; } // Incrément du numéro de ligne
[ \r\t]+          { line += strlen(yytext); concat(yytext);  }
.               { 
                    line += strlen(yytext); concat(yytext);  
                    errorlex("Error syntaxe");
                    return 1;  // Retourne 1 pour signaler l'erreur
                }

%%

