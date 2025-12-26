// AST definitions for mini C compiler
#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace mc {

struct SourcePos {
    int line = 0;
    int col = 0;
};

enum class NodeKind {
    Program,
    Block,
    StmtList,
    Decl,
    VarList,
    Var,
    Assign,
    Function,
    Return,
    If,
    While,
    For,
    Print,
    Scan,
    BinOp,
    UnOp,
    IntLiteral,
    Empty
};

struct Node {
    NodeKind kind;
    SourcePos pos;
    std::string text;            // identifier name or operator text
    std::vector<Node*> children; // generic children list

    Node(NodeKind k, SourcePos p, std::string t = {})
        : kind(k), pos(p), text(std::move(t)) {}
};

Node* makeNode(NodeKind kind, SourcePos pos, const std::string& text = {});
Node* makeUnary(const std::string& op, Node* child, SourcePos pos);
Node* makeBinary(const std::string& op, Node* lhs, Node* rhs, SourcePos pos);
Node* append(Node* list, Node* item);
Node* wrapList(NodeKind kind, Node* list, SourcePos pos);
void printAst(const Node* n, int indent = 0);
void freeAst(Node* n);

}  // namespace mc
