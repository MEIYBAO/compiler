%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---- forward decl ---- */
int yylex(void);
void yyerror(const char* s);

extern int yylineno;   /* flex %option yylineno 提供 */
extern FILE* yyin;

/* ---------------------------
   AST 结点定义（骨架）
--------------------------- */
typedef enum {
  AST_PROGRAM,
  AST_BLOCK,
  AST_DECL,
  AST_ASSIGN,
  AST_IF,
  AST_WHILE,
  AST_FOR,
  AST_IO,
  AST_BINOP,
  AST_UNOP,
  AST_ID,
  AST_INT
} AstKind;

typedef struct AST {
  AstKind kind;
  char*   text;     /* ID 名 / op / printf/scanf */
  long    ival;     /* int const */
  struct AST* a;
  struct AST* b;
  struct AST* c;
  struct AST* next; /* 链表 */
} AST;

static AST* ast_new(AstKind k){ AST* n=(AST*)calloc(1,sizeof(AST)); n->kind=k; return n; }
static AST* ast_id(const char* s){ AST* n=ast_new(AST_ID); n->text=strdup(s); return n; }
static AST* ast_int(long v){ AST* n=ast_new(AST_INT); n->ival=v; return n; }
static AST* ast_binop(const char* op, AST* x, AST* y){
  AST* n=ast_new(AST_BINOP); n->text=strdup(op); n->a=x; n->b=y; return n;
}
static AST* ast_unop(const char* op, AST* x){
  AST* n=ast_new(AST_UNOP); n->text=strdup(op); n->a=x; return n;
}
static AST* ast_link(AST* head, AST* node){
  if(!node) return head;
  if(!head) return node;
  AST* p=head; while(p->next) p=p->next; p->next=node; return head;
}

static void ast_print(AST* n, int indent){
  if(!n) return;
  for(int i=0;i<indent;i++) printf("  ");
  switch(n->kind){
    case AST_PROGRAM: printf("PROGRAM\n"); break;
    case AST_BLOCK:   printf("BLOCK\n"); break;
    case AST_DECL:    printf("DECL(int)\n"); break;
    case AST_ASSIGN:  printf("ASSIGN\n"); break;
    case AST_IF:      printf("IF\n"); break;
    case AST_WHILE:   printf("WHILE\n"); break;
    case AST_FOR:     printf("FOR\n"); break;
    case AST_IO:      printf("IO(%s)\n", n->text?n->text:""); break;
    case AST_BINOP:   printf("BINOP(%s)\n", n->text); break;
    case AST_UNOP:    printf("UNOP(%s)\n", n->text); break;
    case AST_ID:      printf("ID(%s)\n", n->text); break;
    case AST_INT:     printf("INT(%ld)\n", n->ival); break;
    default:          printf("?\n"); break;
  }
  if(n->a) ast_print(n->a, indent+1);
  if(n->b) ast_print(n->b, indent+1);
  if(n->c) ast_print(n->c, indent+1);
  if(n->next) ast_print(n->next, indent);
}

AST* g_root = NULL;

%}

%error-verbose


%union {
  long  ival;
  char* sval;
  AST*  node;
}

/* ---- tokens ---- */
%token <sval> ID
%token <ival> INTCONST

%token KW_INT KW_IF KW_ELSE KW_WHILE KW_FOR KW_PRINTF KW_SCANF

%token PLUS MINUS MUL DIV MOD POW
%token ASSIGN
%token EQ NE GE LE GT LT
%token AND OR NOT

%token SEMI COMMA LPAREN RPAREN LBRACE RBRACE

/* ---- precedence ---- */
%left OR
%left AND
%right NOT
%nonassoc EQ NE GT LT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right POW
%right UMINUS

/* ---- nonterm types ---- */
%type <node> program stmt_list stmt block
%type <node> decl decl_list
%type <node> assign io_stmt
%type <node> if_stmt while_stmt for_stmt
%type <node> for_init for_cond for_step
%type <node> expr bool_expr rel_expr

%%

program
  : stmt_list
    {
      g_root = ast_new(AST_PROGRAM);
      g_root->a = $1;
      $$ = g_root;
    }
  ;

stmt_list
  : /* empty */          { $$ = NULL; }
  | stmt_list stmt       { $$ = ast_link($1, $2); }
  ;

stmt
  : decl SEMI            { $$ = $1; }
  | assign SEMI          { $$ = $1; }
  | io_stmt SEMI         { $$ = $1; }
  | if_stmt              { $$ = $1; }
  | while_stmt           { $$ = $1; }
  | for_stmt             { $$ = $1; }
  | block                { $$ = $1; }
  | SEMI                 { $$ = NULL; }
  ;

block
  : LBRACE stmt_list RBRACE
    {
      AST* n = ast_new(AST_BLOCK);
      n->a = $2;
      $$ = n;
    }
  ;

decl
  : KW_INT decl_list
    {
      AST* n = ast_new(AST_DECL);
      n->a = $2;
      $$ = n;
    }
  ;

decl_list
  : ID
    {
      $$ = ast_id($1);
      free($1);
    }
  | decl_list COMMA ID
    {
      $$ = ast_link($1, ast_id($3));
      free($3);
    }
  ;

assign
  : ID ASSIGN expr
    {
      AST* n = ast_new(AST_ASSIGN);
      n->a = ast_id($1);
      n->b = $3;
      $$ = n;
      free($1);
    }
  ;

io_stmt
  : KW_PRINTF LPAREN expr RPAREN
    {
      AST* n = ast_new(AST_IO);
      n->text = strdup("printf");
      n->a = $3;
      $$ = n;
    }
  | KW_SCANF LPAREN ID RPAREN
    {
      AST* n = ast_new(AST_IO);
      n->text = strdup("scanf");
      n->a = ast_id($3);
      $$ = n;
      free($3);
    }
  ;

if_stmt
  : KW_IF LPAREN bool_expr RPAREN stmt
    {
      AST* n = ast_new(AST_IF);
      n->a = $3; n->b = $5;
      $$ = n;
    }
  | KW_IF LPAREN bool_expr RPAREN stmt KW_ELSE stmt
    {
      AST* n = ast_new(AST_IF);
      n->a = $3; n->b = $5; n->c = $7;
      $$ = n;
    }
  ;

while_stmt
  : KW_WHILE LPAREN bool_expr RPAREN stmt
    {
      AST* n = ast_new(AST_WHILE);
      n->a = $3; n->b = $5;
      $$ = n;
    }
  ;

for_stmt
  : KW_FOR LPAREN for_init SEMI for_cond SEMI for_step RPAREN stmt
    {
      AST* n = ast_new(AST_FOR);
      n->a = $3;   /* init */
      n->b = $5;   /* cond */
      n->c = $7;   /* step */
      n->next = $9;/* body */
      $$ = n;
    }
  ;

/* for 子部件 */
for_init
  : /* empty */          { $$ = NULL; }
  | assign               { $$ = $1;   }
  ;

for_step
  : /* empty */          { $$ = NULL; }
  | assign               { $$ = $1;   }
  ;

for_cond
  : /* empty */          { $$ = NULL; } /* NULL 表示恒真，后续翻译 IR 时处理 */
  | bool_expr            { $$ = $1;   }
  ;

/* bool_expr：&& || ! + rel_expr */
bool_expr
  : bool_expr OR  bool_expr   { $$ = ast_binop("||", $1, $3); }
  | bool_expr AND bool_expr   { $$ = ast_binop("&&", $1, $3); }
  | NOT bool_expr             { $$ = ast_unop("!", $2); }
  | LPAREN bool_expr RPAREN   { $$ = $2; }
  | rel_expr                  { $$ = $1; }
  ;

rel_expr
  : expr LT expr  { $$ = ast_binop("<",  $1, $3); }
  | expr LE expr  { $$ = ast_binop("<=", $1, $3); }
  | expr GT expr  { $$ = ast_binop(">",  $1, $3); }
  | expr GE expr  { $$ = ast_binop(">=", $1, $3); }
  | expr EQ expr  { $$ = ast_binop("==", $1, $3); }
  | expr NE expr  { $$ = ast_binop("!=", $1, $3); }
  ;

expr
  : expr PLUS expr        { $$ = ast_binop("+", $1, $3); }
  | expr MINUS expr       { $$ = ast_binop("-", $1, $3); }
  | expr MUL expr         { $$ = ast_binop("*", $1, $3); }
  | expr DIV expr         { $$ = ast_binop("/", $1, $3); }
  | expr MOD expr         { $$ = ast_binop("%", $1, $3); }
  | expr POW expr         { $$ = ast_binop("^", $1, $3); }
  | MINUS expr %prec UMINUS { $$ = ast_unop("NEG", $2); }
  | LPAREN expr RPAREN    { $$ = $2; }
  | ID
    {
      $$ = ast_id($1);
      free($1);
    }
  | INTCONST
    {
      $$ = ast_int($1);
    }
  ;

%%

void yyerror(const char* s){
  fprintf(stderr, "Parse Error: %s at line %d\n", s, yylineno);
}

int main(int argc, char** argv){
  if(argc > 1){
    yyin = fopen(argv[1], "rb");
    if(!yyin){ perror("open input"); return 1; }
  }

  if(yyparse() == 0){
    printf("=== PARSE OK ===\n");
    printf("=== AST ===\n");
    ast_print(g_root, 0);
  }
  return 0;
}
