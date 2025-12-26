// Semantic checking implementation
#include "semantic.hpp"
#include <sstream>

namespace mc {

static std::string posStr(SourcePos p) {
    std::ostringstream os;
    os << p.line << ":" << p.col;
    return os.str();
}

bool SymbolTable::declare(const std::string& name, const Type& type, SourcePos pos, std::string& err) {
    if (scopes.empty()) enterScope();
    auto& current = scopes.back();
    if (current.count(name)) {
        std::ostringstream os;
        os << "Redefinition of " << name << " at " << posStr(pos);
        err = os.str();
        return false;
    }
    current[name] = Symbol{name, type, pos};
    return true;
}

std::optional<Symbol> SymbolTable::lookup(const std::string& name) const {
    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
        auto f = it->find(name);
        if (f != it->end()) return f->second;
    }
    return std::nullopt;
}

static void addError(std::vector<std::string>& errors, const std::string& msg) {
    errors.push_back(msg);
}

static bool requireInt(Type t, SourcePos p, const std::string& ctx, std::vector<std::string>& errors) {
    if (t.base == BasicType::Invalid) return false;
    if (t.base != BasicType::Int) {
        addError(errors, ctx + " expects int at " + posStr(p));
        return false;
    }
    return true;
}

Type checkExpr(Node* expr, SymbolTable& symtab, std::vector<std::string>& errors) {
    if (!expr) return {BasicType::Invalid};
    switch (expr->kind) {
        case NodeKind::IntLiteral:
            return {BasicType::Int};
        case NodeKind::Var: {
            auto sym = symtab.lookup(expr->text);
            if (!sym) {
                addError(errors, "Undeclared identifier '" + expr->text + "' at " + posStr(expr->pos));
                return {BasicType::Invalid};
            }
            return sym->type;
        }
        case NodeKind::BinOp: {
            auto lt = checkExpr(expr->children[0], symtab, errors);
            auto rt = checkExpr(expr->children[1], symtab, errors);
            if (lt.base == BasicType::Invalid || rt.base == BasicType::Invalid) {
                return {BasicType::Invalid}; // avoid cascading errors
            }
            if (lt.base != BasicType::Int || rt.base != BasicType::Int) {
                addError(errors, "Type mismatch for operator '" + expr->text + "' at " + posStr(expr->pos));
                return {BasicType::Invalid};
            }
            return {BasicType::Int};
        }
        case NodeKind::UnOp: {
            auto t = checkExpr(expr->children[0], symtab, errors);
            if (t.base == BasicType::Invalid) {
                return {BasicType::Invalid}; // upstream error already reported
            }
            if (t.base != BasicType::Int) {
                addError(errors, "Type mismatch for operator '" + expr->text + "' at " + posStr(expr->pos));
                return {BasicType::Invalid};
            }
            return {BasicType::Int};
        }
        default:
            return {BasicType::Invalid};
    }
}

static void checkStmt(Node* stmt, SymbolTable& symtab, std::vector<std::string>& errors) {
    if (!stmt) return;
    switch (stmt->kind) {
        case NodeKind::Decl: {
            // first pass: declare vars
            for (auto* child : stmt->children) {
                if (child->kind == NodeKind::VarList) {
                    for (auto* v : child->children) {
                        if (v->kind != NodeKind::Var) continue;
                        std::string err;
                        if (!symtab.declare(v->text, {BasicType::Int}, v->pos, err)) {
                            addError(errors, err);
                        }
                    }
                } else if (child->kind == NodeKind::Var) {
                    std::string err;
                    if (!symtab.declare(child->text, {BasicType::Int}, child->pos, err)) {
                        addError(errors, err);
                    }
                }
            }
            // second pass: handle initializers
            for (auto* child : stmt->children) {
                if (child->kind == NodeKind::VarList) {
                    for (auto* v : child->children) {
                        if (v->kind == NodeKind::Assign) {
                            auto* lhs = v->children[0];
                            auto* rhs = v->children[1];
                            auto sym = symtab.lookup(lhs->text);
                            if (!sym) {
                                addError(errors, "Undeclared identifier '" + lhs->text + "' at " + posStr(lhs->pos));
                            }
                            auto rt = checkExpr(rhs, symtab, errors);
                            if (rt.base != BasicType::Int) {
                                addError(errors, "Type mismatch for initializer at " + posStr(rhs->pos));
                            }
                        }
                    }
                }
            }
            break;
        }
        case NodeKind::Assign: {
            auto* lhs = stmt->children[0];
            auto* rhs = stmt->children[1];
            auto sym = symtab.lookup(lhs->text);
            if (!sym) {
                addError(errors, "Undeclared identifier '" + lhs->text + "' at " + posStr(lhs->pos));
            } else if (sym->type.base != BasicType::Int) {
                addError(errors, "Assignment type mismatch for '" + lhs->text + "' at " + posStr(lhs->pos));
            }
            auto rt = checkExpr(rhs, symtab, errors);
            if (rt.base != BasicType::Int) {
                addError(errors, "Right-hand side type mismatch at " + posStr(rhs->pos));
            }
            break;
        }
        case NodeKind::Return: {
            if (!stmt->children.empty()) {
                auto t = checkExpr(stmt->children[0], symtab, errors);
                requireInt(t, stmt->children[0]->pos, "Return value", errors);
            }
            break;
        }
        case NodeKind::Function: {
            symtab.enterScope();
            if (!stmt->children.empty()) {
                checkStmt(stmt->children[0], symtab, errors);
            }
            symtab.leaveScope();
            break;
        }
        case NodeKind::If: {
            auto t = checkExpr(stmt->children[0], symtab, errors);
            requireInt(t, stmt->children[0]->pos, "If condition", errors);
            symtab.enterScope();
            checkStmt(stmt->children[1], symtab, errors);
            symtab.leaveScope();
            if (stmt->children.size() > 2) {
                symtab.enterScope();
                checkStmt(stmt->children[2], symtab, errors);
                symtab.leaveScope();
            }
            break;
        }
        case NodeKind::While: {
            auto t = checkExpr(stmt->children[0], symtab, errors);
            requireInt(t, stmt->children[0]->pos, "While condition", errors);
            symtab.enterScope();
            checkStmt(stmt->children[1], symtab, errors);
            symtab.leaveScope();
            break;
        }
        case NodeKind::For: {
            symtab.enterScope();
            checkStmt(stmt->children[0], symtab, errors);  // init
            if (stmt->children[1]) {
                auto t = checkExpr(stmt->children[1], symtab, errors);  // cond
                requireInt(t, stmt->children[1]->pos, "For condition", errors);
            }
            checkStmt(stmt->children[2], symtab, errors);  // step
            checkStmt(stmt->children[3], symtab, errors);  // body
            symtab.leaveScope();
            break;
        }
        case NodeKind::Print: {
            auto t = checkExpr(stmt->children[0], symtab, errors);
            requireInt(t, stmt->children[0]->pos, "printf argument", errors);
            break;
        }
        case NodeKind::Scan: {
            auto sym = symtab.lookup(stmt->children[0]->text);
            if (!sym) {
                addError(errors, "Undeclared identifier '" + stmt->children[0]->text + "' at " +
                                  posStr(stmt->children[0]->pos));
            }
            break;
        }
        case NodeKind::Block:
        case NodeKind::StmtList: {
            symtab.enterScope();
            for (auto* child : stmt->children) {
                checkStmt(child, symtab, errors);
            }
            symtab.leaveScope();
            break;
        }
        default:
            break;
    }
}

void semanticCheck(Node* root, std::vector<std::string>& errors, SymbolTable& symtab) {
    if (!root) return;
    if (root->kind != NodeKind::Program) {
        addError(errors, "Root is not a Program node");
        return;
    }
    symtab.enterScope();
    for (auto* child : root->children) {
        checkStmt(child, symtab, errors);
    }
    symtab.leaveScope();
}

}  // namespace mc
