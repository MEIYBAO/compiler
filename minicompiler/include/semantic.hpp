// Semantic analysis: symbol table and type checking
#pragma once
#include "ast.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>

namespace mc {

enum class BasicType { Int, Invalid };

struct Type {
    BasicType base = BasicType::Invalid;
};

struct Symbol {
    std::string name;
    Type type;
    SourcePos pos;
};

class SymbolTable {
public:
    void enterScope() { scopes.emplace_back(); }
    void leaveScope() { if (!scopes.empty()) scopes.pop_back(); }

    bool declare(const std::string& name, const Type& type, SourcePos pos, std::string& err);
    std::optional<Symbol> lookup(const std::string& name) const;

private:
    std::vector<std::unordered_map<std::string, Symbol>> scopes;
};

// Collect semantic errors into errors; also populates symbol table.
void semanticCheck(Node* root, std::vector<std::string>& errors, SymbolTable& symtab);

// Evaluate expression type for checking
Type checkExpr(Node* expr, SymbolTable& symtab, std::vector<std::string>& errors);

}  // namespace mc
