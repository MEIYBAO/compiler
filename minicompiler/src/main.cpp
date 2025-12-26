// Entry point for the mini C compiler pipeline
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "parser.hpp"
#include "ast.hpp"
#include "semantic.hpp"
#include "ir.hpp"
#include "optimizer.hpp"
#include "codegen.hpp"

extern int yyparse();
extern FILE* yyin;
extern mc::Node* g_root;

static void dumpIR(const std::vector<mc::Quad>& code) {
    for (size_t i = 0; i < code.size(); ++i) {
        const auto& q = code[i];
        std::cout << i << ": (" << q.op << ", " << q.arg1 << ", " << q.arg2 << ", " << q.res << ")\n";
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
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

    std::cout << "=== AST ===\n";
    mc::printAst(g_root);

    mc::SymbolTable symtab;
    std::vector<std::string> semErrors;
    mc::semanticCheck(g_root, semErrors, symtab);
    if (!semErrors.empty()) {
        std::cout << "=== Semantic Errors ===\n";
        for (auto& e : semErrors) std::cout << e << "\n";
    } else {
        std::cout << "=== Semantic OK ===\n";
    }

    mc::IRBuilder builder;
    builder.gen(g_root);

    std::cout << "=== IR (raw) ===\n";
    dumpIR(builder.code);

    auto optimized = builder.code;
    mc::constantFold(optimized);
    mc::deadCodeEliminate(optimized);

    std::cout << "=== IR (optimized) ===\n";
    dumpIR(optimized);

    auto asmLines = mc::toAssembly(optimized);
    std::cout << "=== Pseudo ASM ===\n";
    for (auto& line : asmLines) std::cout << line << "\n";

    mc::freeAst(g_root);
    return 0;
}
