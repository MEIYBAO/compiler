// Handwritten scanner to replace flex (avoids path issues on Windows)
#include "parser.hpp"
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

int yylineno = 1;
int yycolumn = 1;
extern YYSTYPE yylval;
extern YYLTYPE yylloc;
FILE* yyin = stdin;

static int peekc = EOF;

static int getc_wrap() {
    int c;
    if (peekc != EOF) {
        c = peekc;
        peekc = EOF;
    } else {
        c = fgetc(yyin);
    }
    if (c == '\n') {
        yylineno++;
        yycolumn = 1;
    } else if (c != EOF) {
        yycolumn++;
    }
    return c;
}

static void ungetc_wrap(int c) {
    if (c == EOF) return;
    peekc = c;
    if (c == '\n') {
        yylineno--;
    } else {
        yycolumn--;
    }
}

static void set_loc(int start_col, int end_col) {
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = start_col;
    yylloc.last_column = end_col;
}

static int match_follow(char expect, int tok_true, int tok_false) {
    int c = getc_wrap();
    if (c == expect) {
        set_loc(yycolumn - 2, yycolumn - 1);
        return tok_true;
    }
    ungetc_wrap(c);
    set_loc(yycolumn - 1, yycolumn - 1);
    return tok_false;
}

static char* dup_cstr(const std::string& s) {
    char* p = static_cast<char*>(std::malloc(s.size() + 1));
    if (!p) return nullptr;
    std::memcpy(p, s.c_str(), s.size() + 1);
    return p;
}

static int keyword_or_id(const std::string& s) {
    if (s == "int") return KW_INT;
    if (s == "if") return KW_IF;
    if (s == "else") return KW_ELSE;
    if (s == "while") return KW_WHILE;
    if (s == "for") return KW_FOR;
    if (s == "printf") return KW_PRINTF;
    if (s == "scanf") return KW_SCANF;
    yylval.sval = dup_cstr(s);
    return ID;
}

int yylex() {
    int c;
    while (true) {
        int start_col = yycolumn;
        c = getc_wrap();
        if (c == EOF) return 0;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;

        // single-line comment
        if (c == '/' && (peekc = fgetc(yyin)) == '/') {
            while ((c = fgetc(yyin)) != '\n' && c != EOF) {}
            if (c == '\n') { yylineno++; yycolumn = 1; }
            peekc = EOF;
            continue;
        }
        // multi-line comment
        if (c == '/' && peekc == '*') {
            peekc = EOF;
            int prev = 0;
            while ((c = fgetc(yyin)) != EOF) {
                if (c == '\n') { yylineno++; yycolumn = 1; }
                else yycolumn++;
                if (prev == '*' && c == '/') break;
                prev = c;
            }
            continue;
        } else if (peekc != EOF) {
            ungetc_wrap(peekc);
            peekc = EOF;
        }

        // identifiers / keywords
        if (std::isalpha(c) || c == '_') {
            std::string s;
            s.push_back(static_cast<char>(c));
            while (true) {
                int d = getc_wrap();
                if (std::isalnum(d) || d == '_') {
                    s.push_back(static_cast<char>(d));
                } else {
                    ungetc_wrap(d);
                    break;
                }
            }
            set_loc(start_col, yycolumn - 1);
            return keyword_or_id(s);
        }

        // numbers
        if (std::isdigit(c)) {
            long val = c - '0';
            while (true) {
                int d = getc_wrap();
                if (std::isdigit(d)) {
                    val = val * 10 + (d - '0');
                } else {
                    ungetc_wrap(d);
                    break;
                }
            }
            yylval.ival = static_cast<int>(val);
            set_loc(start_col, yycolumn - 1);
            return INTCONST;
        }

        // operators and punctuation
        switch (c) {
            case '&': {
                int d = getc_wrap();
                if (d == '&') { set_loc(start_col, yycolumn - 1); return AND; }
                ungetc_wrap(d); break;
            }
            case '|': {
                int d = getc_wrap();
                if (d == '|') { set_loc(start_col, yycolumn - 1); return OR; }
                ungetc_wrap(d); break;
            }
            case '!': {
                int d = getc_wrap();
                if (d == '=') { set_loc(start_col, yycolumn - 1); return NE; }
                ungetc_wrap(d); set_loc(start_col, start_col); return NOT;
            }
            case '=': return match_follow('=', EQ, ASSIGN);
            case '>': return match_follow('=', GE, GT);
            case '<': return match_follow('=', LE, LT);
            case '+': set_loc(start_col, start_col); return PLUS;
            case '-': set_loc(start_col, start_col); return MINUS;
            case '*': set_loc(start_col, start_col); return MUL;
            case '/': set_loc(start_col, start_col); return DIV;
            case '%': set_loc(start_col, start_col); return MOD;
            case '^': set_loc(start_col, start_col); return POW;
            case ';': set_loc(start_col, start_col); return SEMI;
            case ',': set_loc(start_col, start_col); return COMMA;
            case '(': set_loc(start_col, start_col); return LPAREN;
            case ')': set_loc(start_col, start_col); return RPAREN;
            case '{': set_loc(start_col, start_col); return LBRACE;
            case '}': set_loc(start_col, start_col); return RBRACE;
            default:
                std::fprintf(stderr, "<ERRORCHAR, %c> at %d:%d\n", c, yylineno, start_col);
                break;
        }
    }
}
