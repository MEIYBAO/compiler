// IR generation from AST
#include "ir.hpp"
#include <cmath>

namespace mc {

static bool isImm(const std::string& s, long long& v) {
    if (s.empty()) return false;
    try {
        size_t idx = 0;
        v = std::stoll(s, &idx, 10);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

std::string IRBuilder::newTemp() {
    return "t" + std::to_string(++tempId);
}

std::string IRBuilder::newLabel() {
    return "L" + std::to_string(++labelId);
}

void IRBuilder::emit(const std::string& op, const std::string& a1, const std::string& a2, const std::string& r) {
    code.push_back({op, a1, a2, r});
}

Value IRBuilder::genExpr(Node* expr) {
    if (!expr) return {"0", true, 0};
    switch (expr->kind) {
        case NodeKind::IntLiteral:
            return {expr->text, true, std::stoll(expr->text)};
        case NodeKind::Var:
            return {expr->text, false, 0};
        case NodeKind::UnOp: {
            auto v = genExpr(expr->children[0]);
            if (expr->text == "NEG") {
                if (v.isConst) return {std::to_string(-v.cval), true, -v.cval};
                std::string t = newTemp();
                emit("NEG", v.name, "-", t);
                return {t, false, 0};
            } else if (expr->text == "!") {
                if (v.isConst) {
                    long long val = !v.cval;
                    return {std::to_string(val), true, val};
                }
                std::string t = newTemp();
                emit("NOT", v.name, "-", t);
                return {t, false, 0};
            }
            break;
        }
        case NodeKind::BinOp: {
            const std::string& op = expr->text;
            if (op == "&&" || op == "||") {
                auto a = genExpr(expr->children[0]);
                std::string t = newTemp();
                std::string lshort = newLabel();
                std::string lend = newLabel();
                if (op == "&&") {
                    emit("MOV", "0", "-", t);               // default false
                    emit("JZ", a.name, "-", lshort);        // left false -> short
                    auto b = genExpr(expr->children[1]);    // only eval when left true
                    emit("JZ", b.name, "-", lshort);        // right false -> short
                    emit("MOV", "1", "-", t);               // both true
                    emit("GOTO", "-", "-", lend);
                    emit("LABEL", "-", "-", lshort);
                    emit("MOV", "0", "-", t);
                    emit("LABEL", "-", "-", lend);
                } else { // ||
                    emit("MOV", "1", "-", t);               // default true
                    emit("JZ", a.name, "-", lshort);        // if left false, need right
                    emit("GOTO", "-", "-", lend);           // left true -> short to true
                    emit("LABEL", "-", "-", lshort);
                    auto b = genExpr(expr->children[1]);    // eval right only if needed
                    emit("JZ", b.name, "-", lshort + "_f"); // if right false -> go set false
                    emit("GOTO", "-", "-", lend);           // right true -> keep 1
                    emit("LABEL", "-", "-", lshort + "_f");
                    emit("MOV", "0", "-", t);
                    emit("LABEL", "-", "-", lend);
                }
                return {t, false, 0};
            }
            auto a = genExpr(expr->children[0]);
            auto b = genExpr(expr->children[1]);
            auto compute = [&](long long x, long long y) -> long long {
                if (op == "+") return x + y;
                if (op == "-") return x - y;
                if (op == "*") return x * y;
                if (op == "/") return y == 0 ? 0 : x / y;
                if (op == "%") return y == 0 ? 0 : x % y;
                if (op == "^") return static_cast<long long>(std::pow(x, y));
                if (op == "&&") return (x && y) ? 1 : 0;
                if (op == "||") return (x || y) ? 1 : 0;
                if (op == "<") return x < y;
                if (op == "<=") return x <= y;
                if (op == ">") return x > y;
                if (op == ">=") return x >= y;
                if (op == "==") return x == y;
                if (op == "!=") return x != y;
                return 0;
            };
            if (a.isConst && b.isConst) {
                long long val = compute(a.cval, b.cval);
                return {std::to_string(val), true, val};
            }
            std::string t = newTemp();
            std::string opName = op; // keep symbolic op
            emit(opName, a.name, b.name, t);
            return {t, false, 0};
        }
        default:
            break;
    }
    return {"0", true, 0};
}

void IRBuilder::genStmt(Node* stmt) {
    if (!stmt) return;
    switch (stmt->kind) {
        case NodeKind::Decl: {
            // emit code for initializers inside VarList children
            for (auto* group : stmt->children) {
                if (group->kind != NodeKind::VarList) continue;
                for (auto* v : group->children) {
                    if (v->kind == NodeKind::Assign) {
                        auto rhs = genExpr(v->children[1]);
                        emit("=", rhs.name, "-", v->children[0]->text);
                    }
                }
            }
            break;
        }
        case NodeKind::Assign: {
            auto rhs = genExpr(stmt->children[1]);
            emit("=", rhs.name, "-", stmt->children[0]->text);
            break;
        }
        case NodeKind::Return: {
            auto v = genExpr(stmt->children[0]);
            emit("return", v.name, "-", "-");
            break;
        }
        case NodeKind::Function: {
            emit("FUNC_BEGIN", stmt->text, "-", "-");
            if (!stmt->children.empty()) genStmt(stmt->children[0]);
            emit("FUNC_END", stmt->text, "-", "-");
            break;
        }
        case NodeKind::Print: {
            auto v = genExpr(stmt->children[0]);
            emit("WRITE", v.name, "-", "-");
            break;
        }
        case NodeKind::Scan: {
            emit("READ", stmt->children[0]->text, "-", "-");
            break;
        }
        case NodeKind::If: {
            std::string ltrue = newLabel();
            std::string lfalse = newLabel();
            std::string lend = newLabel();
            auto cond = genExpr(stmt->children[0]);
            emit("JZ", cond.name, "-", lfalse);
            genStmt(stmt->children[1]);
            emit("GOTO", "-", "-", lend);
            emit("LABEL", "-", "-", lfalse);
            if (stmt->children.size() > 2) {
                genStmt(stmt->children[2]);
            }
            emit("LABEL", "-", "-", lend);
            break;
        }
        case NodeKind::While: {
            std::string lstart = newLabel();
            std::string lbody = newLabel();
            std::string lend = newLabel();
            emit("LABEL", "-", "-", lstart);
            auto cond = genExpr(stmt->children[0]);
            emit("JZ", cond.name, "-", lend);
            genStmt(stmt->children[1]);
            emit("GOTO", "-", "-", lstart);
            emit("LABEL", "-", "-", lend);
            break;
        }
        case NodeKind::For: {
            std::string lcond = newLabel();
            std::string lbody = newLabel();
            std::string lend = newLabel();
            // init
            genStmt(stmt->children[0]);
            emit("LABEL", "-", "-", lcond);
            if (stmt->children[1]) {
                auto cond = genExpr(stmt->children[1]);
                emit("JZ", cond.name, "-", lend);
            }
            genStmt(stmt->children[3]); // body
            genStmt(stmt->children[2]); // step
            emit("GOTO", "-", "-", lcond);
            emit("LABEL", "-", "-", lend);
            break;
        }
        case NodeKind::Block:
        case NodeKind::StmtList:
            for (auto* ch : stmt->children) genStmt(ch);
            break;
        default:
            break;
    }
}

void IRBuilder::gen(Node* root) {
    if (!root) return;
    for (auto* ch : root->children) {
        genStmt(ch);
    }
}

}  // namespace mc
