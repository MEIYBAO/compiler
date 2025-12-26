%{
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include "ast.hpp"

using namespace mc;

#ifndef YYLTYPE
typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED 1
#endif

extern int yylex(void);
extern int yylineno;
extern int yycolumn;
void yyerror(const char* msg);

Node* g_root = nullptr;

static SourcePos loc(const YYLTYPE& l) {
    return {l.first_line, l.first_column};
}
%}

%error-verbose
%locations
%code requires {
  #include "ast.hpp"
}

%union {
    int ival;
    char* sval;
    mc::Node* node;
}

%token <sval> ID
%token <ival> INTCONST

%token KW_INT KW_IF KW_ELSE KW_WHILE KW_FOR KW_PRINTF KW_SCANF
%token PLUS MINUS MUL DIV MOD POW
%token ASSIGN
%token EQ NE GE LE GT LT
%token AND OR NOT
%token SEMI COMMA LPAREN RPAREN LBRACE RBRACE

%type <node> program stmt_list stmt block decl id_list assign io_stmt if_stmt while_stmt for_stmt opt_expr opt_assign expr bool_expr rel_expr

%left OR
%left AND
%right NOT
%nonassoc EQ NE GT LT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right POW
%right UMINUS

%%

program
  : stmt_list
    {
      g_root = makeNode(NodeKind::Program, loc(@1));
      if ($1) g_root->children.push_back($1);
      $$ = g_root;
    }
  ;

stmt_list
  : /* empty */ { $$ = nullptr; }
  | stmt_list stmt
    {
      if ($1 == nullptr) $$ = makeNode(NodeKind::StmtList, loc(@2));
      else $$ = $1;
      if ($2) $$->children.push_back($2);
    }
  ;

stmt
  : decl SEMI            { $$ = $1; }
  | assign SEMI          { $$ = $1; }
  | io_stmt SEMI         { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | while_stmt           { $$ = $1; }
  | for_stmt             { $$ = $1; }
  | block                { $$ = $1; }
  | SEMI                 { $$ = makeNode(NodeKind::Empty, loc(@1)); }
  ;

block
  : LBRACE stmt_list RBRACE
    {
      $$ = makeNode(NodeKind::Block, loc(@1));
      if ($2) $$->children.push_back($2);
    }
  ;

decl
  : KW_INT id_list
    {
      $$ = makeNode(NodeKind::Decl, loc(@1));
      if ($2) $$->children.push_back($2);
    }
  ;

id_list
  : ID
    {
      $$ = makeNode(NodeKind::Var, loc(@1), $1);
      free($1);
    }
  | id_list COMMA ID
    {
      $$ = $1;
      $$->children.push_back(makeNode(NodeKind::Var, loc(@3), $3));
      free($3);
    }
  ;

assign
  : ID ASSIGN expr
    {
      Node* lhs = makeNode(NodeKind::Var, loc(@1), $1);
      $$ = makeNode(NodeKind::Assign, loc(@2));
      $$->children.push_back(lhs);
      $$->children.push_back($3);
      free($1);
    }
  ;

io_stmt
  : KW_PRINTF LPAREN expr RPAREN
    {
      $$ = makeNode(NodeKind::Print, loc(@1));
      $$->children.push_back($3);
    }
  | KW_SCANF LPAREN ID RPAREN
    {
      $$ = makeNode(NodeKind::Scan, loc(@1));
      $$->children.push_back(makeNode(NodeKind::Var, loc(@3), $3));
      free($3);
    }
  ;

if_stmt
  : KW_IF LPAREN bool_expr RPAREN stmt
    {
      $$ = makeNode(NodeKind::If, loc(@1));
      $$->children.push_back($3);
      $$->children.push_back($5);
    }
  | KW_IF LPAREN bool_expr RPAREN stmt KW_ELSE stmt
    {
      $$ = makeNode(NodeKind::If, loc(@1));
      $$->children.push_back($3);
      $$->children.push_back($5);
      $$->children.push_back($7);
    }
  ;

while_stmt
  : KW_WHILE LPAREN bool_expr RPAREN stmt
    {
      $$ = makeNode(NodeKind::While, loc(@1));
      $$->children.push_back($3);
      $$->children.push_back($5);
    }
  ;

for_stmt
  : KW_FOR LPAREN opt_assign SEMI opt_expr SEMI opt_assign RPAREN stmt
    {
      $$ = makeNode(NodeKind::For, loc(@1));
      $$->children.push_back($3 ? $3 : makeNode(NodeKind::Empty, loc(@1)));
      $$->children.push_back($5);
      $$->children.push_back($7 ? $7 : makeNode(NodeKind::Empty, loc(@1)));
      $$->children.push_back($9);
    }
  ;

opt_expr
  : /* empty */ { $$ = nullptr; }
  | bool_expr   { $$ = $1; }
  ;

opt_assign
  : /* empty */ { $$ = nullptr; }
  | assign      { $$ = $1; }
  ;

bool_expr
  : bool_expr OR bool_expr   { $$ = makeBinary("||", $1, $3, loc(@2)); }
  | bool_expr AND bool_expr  { $$ = makeBinary("&&", $1, $3, loc(@2)); }
  | NOT bool_expr            { $$ = makeUnary("!", $2, loc(@1)); }
  | LPAREN bool_expr RPAREN  { $$ = $2; }
  | rel_expr                 { $$ = $1; }
  ;

rel_expr
  : expr LT expr  { $$ = makeBinary("<",  $1, $3, loc(@2)); }
  | expr LE expr  { $$ = makeBinary("<=", $1, $3, loc(@2)); }
  | expr GT expr  { $$ = makeBinary(">",  $1, $3, loc(@2)); }
  | expr GE expr  { $$ = makeBinary(">=", $1, $3, loc(@2)); }
  | expr EQ expr  { $$ = makeBinary("==", $1, $3, loc(@2)); }
  | expr NE expr  { $$ = makeBinary("!=", $1, $3, loc(@2)); }
  ;

expr
  : expr PLUS expr   { $$ = makeBinary("+", $1, $3, loc(@2)); }
  | expr MINUS expr  { $$ = makeBinary("-", $1, $3, loc(@2)); }
  | expr MUL expr    { $$ = makeBinary("*", $1, $3, loc(@2)); }
  | expr DIV expr    { $$ = makeBinary("/", $1, $3, loc(@2)); }
  | expr MOD expr    { $$ = makeBinary("%", $1, $3, loc(@2)); }
  | expr POW expr    { $$ = makeBinary("^", $1, $3, loc(@2)); }
  | MINUS expr %prec UMINUS { $$ = makeUnary("NEG", $2, loc(@1)); }
  | LPAREN expr RPAREN      { $$ = $2; }
  | ID
    {
      $$ = makeNode(NodeKind::Var, loc(@1), $1);
      free($1);
    }
  | INTCONST
    {
      $$ = makeNode(NodeKind::IntLiteral, loc(@1), std::to_string($1));
    }
  ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Parse Error: %s at line %d, col %d\n", s, yylloc.first_line, yylloc.first_column);
}
