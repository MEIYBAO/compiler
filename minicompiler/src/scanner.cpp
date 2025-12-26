// Handwritten scanner to avoid flex path issues on Windows
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

static int getch() {
    while (true) {
        int c = fgetc(yyin);
        if (c == EOF) return EOF;
        if (c == 0xEF) {
            int b2 = fgetc(yyin);
            int b3 = fgetc(yyin);
            if (b2 == 0xBB && b3 == 0xBF) {
                // skip BOM
                continue;
            } else {
                if (b3 != EOF) ungetc(b3, yyin);
                if (b2 != EOF) ungetc(b2, yyin);
                c = 0xEF;
            }
        }
        if (c == '\n') {
            yylineno++;
            yycolumn = 1;
        } else {
            yycolumn++;
        }
        return c;
    }
}

static void ungetch(int c) {
    if (c == EOF) return;
    ungetc(c, yyin);
    if (c == '\n') {
        yylineno--;
        // column reset is rough; not critical for positions after unget
        yycolumn = 1;
    } else {
        yycolumn--;
    }
}

static void set_loc(int start_col, int end_col) {
    yylloc.first_line = yylloc.last_line = yylineno;
    yylloc.first_column = start_col;
    yylloc.last_column = end_col;
}

static int keyword_or_id(const std::string& s) {
    if (s == "int") return KW_INT;
    if (s == "if") return KW_IF;
    if (s == "else") return KW_ELSE;
    if (s == "while") return KW_WHILE;
    if (s == "for") return KW_FOR;
    if (s == "return") return KW_RETURN;
    if (s == "printf") return KW_PRINTF;
    if (s == "scanf") return KW_SCANF;
    char* p = static_cast<char*>(std::malloc(s.size() + 1));
    std::memcpy(p, s.c_str(), s.size() + 1);
    yylval.sval = p;
    return ID;
}

int yylex() {
    int c;
    while (true) {
        int start_col = yycolumn;
        c = getch();
        if (c == EOF) return 0;
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;

        // comments
        if (c == '/') {
            int d = getch();
            if (d == '/') {
                while ((c = getch()) != '\n' && c != EOF) {}
                continue;
            } else if (d == '*') {
                int prev = 0;
                while ((c = getch()) != EOF) {
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }
                continue;
            } else {
                ungetch(d);
            }
        }

        // identifiers/keywords
        if (std::isalpha(c) || c == '_') {
            std::string s;
            s.push_back(static_cast<char>(c));
            while (true) {
                int d = getch();
                if (std::isalnum(d) || d == '_') {
                    s.push_back(static_cast<char>(d));
                } else {
                    ungetch(d);
                    break;
                }
            }
            set_loc(start_col, yycolumn - 1);
            return keyword_or_id(s);
        }

        // integer
        if (std::isdigit(c)) {
            long val = c - '0';
            while (true) {
                int d = getch();
                if (std::isdigit(d)) {
                    val = val * 10 + (d - '0');
                } else {
                    ungetch(d);
                    break;
                }
            }
            yylval.ival = static_cast<int>(val);
            set_loc(start_col, yycolumn - 1);
            return INTCONST;
        }

        // operators and punctuators
        switch (c) {
            case '&': {
                int d = getch();
                if (d == '&') { set_loc(start_col, yycolumn - 1); return AND; }
                ungetch(d); break;
            }
            case '|': {
                int d = getch();
                if (d == '|') { set_loc(start_col, yycolumn - 1); return OR; }
                ungetch(d); break;
            }
            case '!': {
                int d = getch();
                if (d == '=') { set_loc(start_col, yycolumn - 1); return NE; }
                ungetch(d); set_loc(start_col, start_col); return NOT;
            }
            case '=': {
                int d = getch();
                if (d == '=') { set_loc(start_col, yycolumn - 1); return EQ; }
                ungetch(d); set_loc(start_col, start_col); return ASSIGN;
            }
            case '>': {
                int d = getch();
                if (d == '=') { set_loc(start_col, yycolumn - 1); return GE; }
                ungetch(d); set_loc(start_col, start_col); return GT;
            }
            case '<': {
                int d = getch();
                if (d == '=') { set_loc(start_col, yycolumn - 1); return LE; }
                ungetch(d); set_loc(start_col, start_col); return LT;
            }
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
