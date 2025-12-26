// Quadruple IR generation
#pragma once
#include "ast.hpp"
#include "semantic.hpp"
#include <string>
#include <vector>

namespace mc {

struct Quad {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string res;
};

struct Value {
    std::string name;
    bool isConst = false;
    long long cval = 0;
};

class IRBuilder {
public:
    Value genExpr(Node* expr);
    void genStmt(Node* stmt);
    void gen(Node* root);

    std::vector<Quad> code;

private:
    std::string newTemp();
    std::string newLabel();
    void emit(const std::string& op, const std::string& a1 = "-", const std::string& a2 = "-", const std::string& r = "-");

    int tempId = 0;
    int labelId = 0;
};

}  // namespace mc
