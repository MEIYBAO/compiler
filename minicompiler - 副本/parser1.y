%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char* s);
%}

%token ID INTCONST
%token PLUS MINUS SEMI

%%

program
  : program stmt
  | /* empty */
  ;

stmt
  : ID PLUS INTCONST SEMI
  ;

%%

void yyerror(const char* s){
  fprintf(stderr, "error: %s\n", s);
}

int main(void){
  yyparse();
  return 0;
}
