// AST utilities
#include "ast.hpp"
#include <cstdio>

namespace mc {

static void indent(int n) {
    for (int i = 0; i < n; ++i) std::cout << "  ";
}

Node* makeNode(NodeKind kind, SourcePos pos, const std::string& text) {
    return new Node(kind, pos, text);
}

Node* makeUnary(const std::string& op, Node* child, SourcePos pos) {
    Node* n = makeNode(NodeKind::UnOp, pos, op);
    if (child) n->children.push_back(child);
    return n;
}

Node* makeBinary(const std::string& op, Node* lhs, Node* rhs, SourcePos pos) {
    Node* n = makeNode(NodeKind::BinOp, pos, op);
    if (lhs) n->children.push_back(lhs);
    if (rhs) n->children.push_back(rhs);
    return n;
}

Node* append(Node* list, Node* item) {
    if (!list) return item;
    if (!item) return list;
    Node* p = list;
    while (!p->children.empty() && p->children.back() &&
           p->children.back()->kind == NodeKind::StmtList) {
        p = p->children.back();
    }
    p->children.push_back(item);
    return list;
}

Node* wrapList(NodeKind kind, Node* list, SourcePos pos) {
    Node* n = makeNode(kind, pos);
    if (list) n->children.push_back(list);
    return n;
}

static const char* kindName(NodeKind k) {
    switch (k) {
        case NodeKind::Program: return "Program";
        case NodeKind::Block: return "Block";
        case NodeKind::StmtList: return "StmtList";
        case NodeKind::Decl: return "Decl";
        case NodeKind::VarList: return "VarList";
        case NodeKind::Var: return "Var";
        case NodeKind::Assign: return "Assign";
        case NodeKind::Function: return "Function";
        case NodeKind::Return: return "Return";
        case NodeKind::If: return "If";
        case NodeKind::While: return "While";
        case NodeKind::For: return "For";
        case NodeKind::Print: return "Print";
        case NodeKind::Scan: return "Scan";
        case NodeKind::BinOp: return "BinOp";
        case NodeKind::UnOp: return "UnOp";
        case NodeKind::IntLiteral: return "Int";
        case NodeKind::Empty: return "Empty";
    }
    return "Unknown";
}

void printAst(const Node* n, int indentLevel) {
    if (!n) return;
    indent(indentLevel);
    std::cout << kindName(n->kind);
    if (!n->text.empty()) std::cout << "(" << n->text << ")";
    if (n->pos.line > 0) {
        std::cout << " @" << n->pos.line << ":" << n->pos.col;
    }
    std::cout << "\n";
    for (const auto* ch : n->children) {
        printAst(ch, indentLevel + 1);
    }
}

void freeAst(Node* n) {
    if (!n) return;
    for (auto* ch : n->children) {
        freeAst(ch);
    }
    delete n;
}

}  // namespace mc
