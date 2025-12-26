%option noyywrap nodefault yylineno
%option nounput noinput

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
  词法输出格式建议：
    <TOKEN, lexeme>
  非法字符：
    <ERRORCHAR, ch> at line:col
*/

static int colno = 1;   // 当前列号（从 1 开始）

static void update_col(const char* yytext) {
    // yytext 不含 '\n' 的情况下，列号 += yyleng
    colno += (int)strlen(yytext);
}

static void reset_col() {
    colno = 1;
}

static void print_token(const char* tok, const char* lexeme) {
    printf("<%s, %s>\n", tok, lexeme);
}

static void print_token_int(const char* tok, const char* lexeme, long val) {
    printf("<%s, %s, %ld>\n", tok, lexeme, val);
}

%}

/* ---------- 正则定义区 ---------- */
DIGIT      [0-9]
LETTER     [A-Za-z_]
ID         {LETTER}({LETTER}|{DIGIT})*
INTCONST   {DIGIT}+
REALCONST  ({DIGIT}+\.{DIGIT}*|{DIGIT}*\.{DIGIT}+)([eE][+-]?{DIGIT}+)?
SCICONST   {DIGIT}+[eE][+-]?{DIGIT}+

WS         [ \t\r]+

/* ---------- 规则区 ---------- */
%%

\n              { reset_col(); /* yylineno 自动 +1 */ }


{WS}            { update_col(yytext); }


"//".*          { update_col(yytext); }


"/*"([^*]|\*+[^*/])*\*+"/"   { update_col(yytext); /* 其中可能含 \n，此处简单实现：不逐行计列 */ }


"int"           { print_token("KW_INT", yytext); update_col(yytext); }
"float"         { print_token("KW_FLOAT", yytext); update_col(yytext); }
"double"        { print_token("KW_DOUBLE", yytext); update_col(yytext); }
"void"          { print_token("KW_VOID", yytext); update_col(yytext); }
"if"            { print_token("KW_IF", yytext); update_col(yytext); }
"else"          { print_token("KW_ELSE", yytext); update_col(yytext); }
"while"         { print_token("KW_WHILE", yytext); update_col(yytext); }
"for"           { print_token("KW_FOR", yytext); update_col(yytext); }
"return"        { print_token("KW_RETURN", yytext); update_col(yytext); }
"struct"        { print_token("KW_STRUCT", yytext); update_col(yytext); }


"printf"        { print_token("KW_PRINTF", yytext); update_col(yytext); }
"scanf"         { print_token("KW_SCANF", yytext); update_col(yytext); }

"&&"            { print_token("AND", yytext); update_col(yytext); }
"||"            { print_token("OR", yytext);  update_col(yytext); }
"!"             { print_token("NOT", yytext); update_col(yytext); }
"->"            { print_token("ARROW", yytext); update_col(yytext); }


"=="            { print_token("EQ", yytext);  update_col(yytext); }
"!="            { print_token("NE", yytext);  update_col(yytext); }
">="            { print_token("GE", yytext);  update_col(yytext); }
"<="            { print_token("LE", yytext);  update_col(yytext); }
">"             { print_token("GT", yytext);  update_col(yytext); }
"<"             { print_token("LT", yytext);  update_col(yytext); }


"="             { print_token("ASSIGN", yytext); update_col(yytext); }


"+"             { print_token("PLUS", yytext);  update_col(yytext); }
"-"             { print_token("MINUS", yytext); update_col(yytext); }
"*"             { print_token("MUL", yytext);   update_col(yytext); }
"/"             { print_token("DIV", yytext);   update_col(yytext); }
"%"             { print_token("MOD", yytext);   update_col(yytext); }
"^"             { print_token("POW", yytext);   update_col(yytext); }
"&"             { print_token("ADDR", yytext);  update_col(yytext); }


";"             { print_token("SEMI", yytext);   update_col(yytext); }
","             { print_token("COMMA", yytext);  update_col(yytext); }
"("             { print_token("LPAREN", yytext); update_col(yytext); }
")"             { print_token("RPAREN", yytext); update_col(yytext); }
"{"             { print_token("LBRACE", yytext); update_col(yytext); }
"}"             { print_token("RBRACE", yytext); update_col(yytext); }
"["             { print_token("LBRACKET", yytext); update_col(yytext); }
"]"             { print_token("RBRACKET", yytext); update_col(yytext); }
"."             { print_token("DOT", yytext); update_col(yytext); }


{REALCONST}     {
                    double v = strtod(yytext, NULL);
                    printf("<%s, %s, %g>\n", "REALCONST", yytext, v);
                    update_col(yytext);
                }

{SCICONST}      {
                    double v = strtod(yytext, NULL);
                    printf("<%s, %s, %g>\n", "REALCONST", yytext, v);
                    update_col(yytext);
                }

{INTCONST}      {
                    long v = strtol(yytext, NULL, 10);
                    print_token_int("INTCONST", yytext, v);
                    update_col(yytext);
                }

{ID}            {
                    /* 关键字已在上面先匹配；走到这一定是标识符 */
                    print_token("ID", yytext);
                    update_col(yytext);
                }


.               {
                    /* yytext 为单字符 */
                    printf("<ERRORCHAR, %s> at %d:%d\n", yytext, yylineno, colno);
                    update_col(yytext);
                }
%%
/* 供独立测试：只做词法分析 */
int main(int argc, char** argv) {
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