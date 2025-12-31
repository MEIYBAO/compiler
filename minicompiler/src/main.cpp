// Entry point for the mini C compiler pipeline
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include "parser.hpp"
#include "ast.hpp"
#include "semantic.hpp"
#include "ir.hpp"
#include "optimizer.hpp"
#include "codegen.hpp"

extern int yyparse();
extern FILE* yyin;
extern mc::Node* g_root;
extern int yylineno;
extern int yycolumn;
extern int yylex();
extern YYSTYPE yylval;
extern YYLTYPE yylloc;

static void printTree(const mc::Node* n, const std::string& prefix, bool last) {
    if (!n) return;
    std::cout << prefix;
    std::cout << (last ? "└── " : "├── ");
    switch (n->kind) {
        case mc::NodeKind::Program: std::cout << "程序"; break;
        case mc::NodeKind::Block: std::cout << "复合语句"; break;
        case mc::NodeKind::StmtList: std::cout << "语句序列"; break;
        case mc::NodeKind::Decl: std::cout << "变量声明 int"; break;
        case mc::NodeKind::VarList: std::cout << "变量列表"; break;
        case mc::NodeKind::Var: std::cout << "标识符 " << n->text; break;
        case mc::NodeKind::Assign: std::cout << "赋值语句"; break;
        case mc::NodeKind::Function: std::cout << "函数定义 int " << n->text; break;
        case mc::NodeKind::Return: std::cout << "return"; break;
        case mc::NodeKind::If: std::cout << "if语句"; break;
        case mc::NodeKind::While: std::cout << "while语句"; break;
        case mc::NodeKind::For: std::cout << "for语句"; break;
        case mc::NodeKind::Print: std::cout << "printf"; break;
        case mc::NodeKind::Scan: std::cout << "scanf"; break;
        case mc::NodeKind::BinOp: std::cout << "二元表达式 " << n->text; break;
        case mc::NodeKind::UnOp: std::cout << "一元表达式 " << n->text; break;
        case mc::NodeKind::IntLiteral: std::cout << "常量 " << n->text; break;
        case mc::NodeKind::Empty: std::cout << "空"; break;
    }
    std::cout << "\n";
    std::string childPrefix = prefix + (last ? "    " : "│   ");
    for (size_t i = 0; i < n->children.size(); ++i) {
        printTree(n->children[i], childPrefix, i + 1 == n->children.size());
    }
}

static void dumpIR(const std::vector<mc::Quad>& code) {
    for (size_t i = 0; i < code.size(); ++i) {
        const auto& q = code[i];
        std::cout << i << ": (" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.res << ")\n";
    }
}

static const char* tokenName(int t) {
    switch (t) {
        case KW_INT: return "int";
        case KW_IF: return "if";
        case KW_ELSE: return "else";
        case KW_WHILE: return "while";
        case KW_FOR: return "for";
        case KW_PRINTF: return "printf";
        case KW_SCANF: return "scanf";
        case KW_RETURN: return "return";
        case PLUS: return "+";
        case MINUS: return "-";
        case MUL: return "*";
        case DIV: return "/";
        case MOD: return "%";
        case POW: return "^";
        case ASSIGN: return "=";
        case EQ: return "==";
        case NE: return "!=";
        case GE: return ">=";
        case LE: return "<=";
        case GT: return ">";
        case LT: return "<";
        case AND: return "&&";
        case OR: return "||";
        case NOT: return "!";
        case SEMI: return ";";
        case COMMA: return ",";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case LBRACE: return "{";
        case RBRACE: return "}";
        default: return "";
    }
}

static const char* tokenCategory(int t) {
    switch (t) {
        case KW_INT: case KW_IF: case KW_ELSE: case KW_WHILE: case KW_FOR:
        case KW_PRINTF: case KW_SCANF: case KW_RETURN:
            return "关键字";
        case ID:
            return "标识符";
        case INTCONST:
            return "常量";
        case PLUS: case MINUS: case MUL: case DIV: case MOD: case POW:
        case ASSIGN: case EQ: case NE: case GE: case LE: case GT: case LT:
        case AND: case OR: case NOT:
            return "运算符";
        case SEMI: case COMMA: case LPAREN: case RPAREN: case LBRACE: case RBRACE:
            return "界符";
        default:
            return "未知";
    }
}

static void dumpTokens(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return;
    yyin = f;
    yylineno = 1;
    yycolumn = 1;
    std::cout << "词法分析结果\n";
    std::cout << " 行号           类别                词素\n";
    std::cout << "----------------------------------------\n";
    while (true) {
        int tok = yylex();
        if (tok == 0) break;
        std::string lexeme;
        if (tok == ID) {
            lexeme = yylval.sval;
            free(yylval.sval);
        } else if (tok == INTCONST) {
            lexeme = std::to_string(yylval.ival);
        } else {
            lexeme = tokenName(tok);
        }
        std::cout << std::setw(6) << yylloc.first_line
                  << "   " << std::setw(10) << tokenCategory(tok)
                  << "   " << std::setw(12) << lexeme << "\n";
    }
    fclose(f);
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cout << "\xEF\xBB\xBF"; // UTF-8 BOM for Windows editors
    yylineno = 1;
    yycolumn = 1;
    std::string asmPath = "output.asm";
    if (argc > 1) {
        std::string inputPath = argv[1];
        size_t slash = inputPath.find_last_of("/\\");
        std::string dir = (slash == std::string::npos) ? "" : inputPath.substr(0, slash + 1);
        std::string base = (slash == std::string::npos) ? inputPath : inputPath.substr(slash + 1);
        size_t dot = base.find_last_of('.');
        if (dot != std::string::npos) {
            base = base.substr(0, dot);
        }
        asmPath = dir + base + ".asm";
        dumpTokens(argv[1]);
        yyin = fopen(argv[1], "rb");
        if (!yyin) {
            perror("open input");
            return 1;
        }
    }

    if (yyparse() != 0) {
        std::cerr << "Parsing failed.\n";
        return 1;
    }

    std::cout << "\n语法分析结果\n语法树：\n\n";
    printTree(g_root, "", true);

    mc::SymbolTable symtab;
    std::vector<std::string> semErrors;
    mc::semanticCheck(g_root, semErrors, symtab);

    mc::IRBuilder builder;
    builder.gen(g_root);

    std::cout << "\n中间代码（四元式）：\n";
    dumpIR(builder.code);

    auto optimized = builder.code;
    mc::constantFold(optimized);
    mc::globalConstProp(optimized);
    mc::strengthReduce(optimized);
    mc::copyPropagate(optimized);
    mc::commonSubexprElim(optimized);
    mc::codeMotion(optimized);
    mc::deadCodeEliminate(optimized);
    mc::simplifyControl(optimized);

    std::cout << "\n优化后中间代码：\n";
    dumpIR(optimized);

    std::cout << "\n类型检查:\n";
    if (!semErrors.empty()) {
        for (auto& e : semErrors) std::cout << e << "\n";
        std::cout << "类型检查未通过\n";
    } else {
        std::cout << "类型检查通过\n";
    }

    std::cout << "\n错误分析:\n";
    if (!semErrors.empty()) {
        std::cout << "发现 " << semErrors.size() << " 个语义/类型错误，详见上述列表。\n";
    } else {
        std::cout << "未发现语义/类型错误。\n";
    }

    auto asmLines = mc::toAssembly(optimized);
    std::cout << "\n目标代码（x86汇编）：\n";
    for (auto& line : asmLines) std::cout << line << "\n";

    std::ofstream asmFile(asmPath, std::ios::binary);
    if (asmFile) {
        for (const auto& line : asmLines) {
            asmFile << line << "\n";
        }
    } else {
        std::cerr << "Failed to write assembly file to " << asmPath << "\n";
    }

    mc::freeAst(g_root);
    return 0;
}
