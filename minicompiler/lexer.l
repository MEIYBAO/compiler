%option noyywrap nodefault yylineno
%option nounput noinput

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int colno = 1;

typedef struct Sym {
    char* name;
    long id;
    struct Sym* next;
} Sym;

static Sym* symtab = NULL;
static long next_id = 1;

static void update_col(const char* yytext) {
    colno += (int)strlen(yytext);
}

static void reset_col() {
    colno = 1;
}

static void print_token(const char* tok, const char* lexeme) {
    printf("%s\t%s\t\n", tok, lexeme);
}

static void print_token_int(const char* tok, const char* lexeme, long val) {
    printf("%s\t%s\t%ld\n", tok, lexeme, val);
}

static void print_token_real(const char* tok, const char* lexeme, double val) {
    printf("%s\t%s\t%g\n", tok, lexeme, val);
}

static long get_id(const char* name) {
    Sym* cur = symtab;
    while (cur) {
        if (strcmp(cur->name, name) == 0) {
            return cur->id;
        }
        cur = cur->next;
    }
    Sym* n = (Sym*)malloc(sizeof(Sym));
    if (!n) {
        return 0;
    }
    n->name = strdup(name);
    n->id = next_id++;
    n->next = symtab;
    symtab = n;
    return n->id;
}

%}

DIGIT      [0-9]
LETTER     [A-Za-z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INTCONST   {DIGIT}+
REALCONST  ({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)([eE][+-]?{DIGIT}+)?
SCICONST   {DIGIT}+[eE][+-]?{DIGIT}+

WS         [ \t\r]+

%%

\n              { reset_col(); }

{WS}            { update_col(yytext); }

"//".*          { update_col(yytext); }

"/*"([^*]|\*+[^*/])*\*+"/"   { update_col(yytext); }

"int"           { print_token("TYPE", yytext); update_col(yytext); }
"float"         { print_token("TYPE", yytext); update_col(yytext); }
"double"        { print_token("TYPE", yytext); update_col(yytext); }
"void"          { print_token("VOID", yytext); update_col(yytext); }
"main"          { print_token("MAIN", yytext); update_col(yytext); }
"if"            { print_token("IF", yytext); update_col(yytext); }
"else"          { print_token("ELSE", yytext); update_col(yytext); }
"while"         { print_token("WHILE", yytext); update_col(yytext); }
"for"           { print_token("FOR", yytext); update_col(yytext); }
"return"        { print_token("RETURN", yytext); update_col(yytext); }
"struct"        { print_token("STRUCT", yytext); update_col(yytext); }

"printf"        { print_token("PRINTF", yytext); update_col(yytext); }
"scanf"         { print_token("SCANF", yytext); update_col(yytext); }

"&&"            { print_token("AND", yytext); update_col(yytext); }
"||"            { print_token("OR", yytext);  update_col(yytext); }
"!"             { print_token("NOT", yytext); update_col(yytext); }
"->"            { print_token("ARROW", yytext); update_col(yytext); }

"=="            { print_token("EQUAL", yytext);  update_col(yytext); }
"!="            { print_token("NOTEQUAL", yytext);  update_col(yytext); }
">="            { print_token("GREATEREQ", yytext);  update_col(yytext); }
"<="            { print_token("LESSEQ", yytext);  update_col(yytext); }
">"             { print_token("GREATER", yytext);  update_col(yytext); }
"<"             { print_token("LESS", yytext);  update_col(yytext); }

"="             { print_token("ASSIGN", yytext); update_col(yytext); }

"+"             { print_token("ADD", yytext);  update_col(yytext); }
"-"             { print_token("SUB", yytext); update_col(yytext); }
"*"             { print_token("MUL", yytext);   update_col(yytext); }
"/"             { print_token("DIV", yytext);   update_col(yytext); }
"%"             { print_token("MOD", yytext);   update_col(yytext); }
"^"             { print_token("POW", yytext);   update_col(yytext); }
"&"             { print_token("ADDR", yytext);  update_col(yytext); }

";"             { print_token("SEMICOLON", yytext);   update_col(yytext); }
","             { print_token("COMMA", yytext);  update_col(yytext); }
"("             { print_token("LP", yytext); update_col(yytext); }
")"             { print_token("RP", yytext); update_col(yytext); }
"{"             { print_token("LBRACE", yytext); update_col(yytext); }
"}"             { print_token("RBRACE", yytext); update_col(yytext); }
"["             { print_token("LBRACKET", yytext); update_col(yytext); }
"]"             { print_token("RBRACKET", yytext); update_col(yytext); }
"."             { print_token("DOT", yytext); update_col(yytext); }

{REALCONST}     {
                    double v = strtod(yytext, NULL);
                    print_token_real("NUMBER", yytext, v);
                    update_col(yytext);
                }

{SCICONST}      {
                    double v = strtod(yytext, NULL);
                    print_token_real("NUMBER", yytext, v);
                    update_col(yytext);
                }

{INTCONST}      {
                    long v = strtol(yytext, NULL, 10);
                    print_token_int("NUMBER", yytext, v);
                    update_col(yytext);
                }

{ID}            {
                    long id = get_id(yytext);
                    print_token_int("ID", yytext, id);
                    update_col(yytext);
                }

.               {
                    printf("ERRORCHAR\t%s\t%d:%d\n", yytext, yylineno, colno);
                    update_col(yytext);
                }
%%
int main(int argc, char** argv) {
    printf("单词\t词素\t属性\n");
    if (argc > 1) {
        FILE* f = fopen(argv[1], "rb");
        if (!f) {
            perror("open input file");
            return 1;
        }
        yyin = f;
    }
    yylex();
    return 0;
}
