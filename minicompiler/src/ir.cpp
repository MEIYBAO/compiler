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
            auto a = genExpr(expr->children[0]);
            auto b = genExpr(expr->children[1]);
            const std::string& op = expr->text;
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
            if (op == "&&" || op == "||") {
                // Short-circuit via cond translation
                std::string ltrue = newLabel();
                std::string lfalse = newLabel();
                std::string lend = newLabel();
                genCond(expr, ltrue, lfalse);
                emit("LABEL", "-", "-", ltrue);
                emit("MOV", "1", "-", t);
                emit("GOTO", "-", "-", lend);
                emit("LABEL", "-", "-", lfalse);
                emit("MOV", "0", "-", t);
                emit("LABEL", "-", "-", lend);
            } else if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "==" || op == "!=") {
                std::string ltrue = newLabel();
                std::string lfalse = newLabel();
                std::string lend = newLabel();
                genCond(expr, ltrue, lfalse);
                emit("LABEL", "-", "-", ltrue);
                emit("MOV", "1", "-", t);
                emit("GOTO", "-", "-", lend);
                emit("LABEL", "-", "-", lfalse);
                emit("MOV", "0", "-", t);
                emit("LABEL", "-", "-", lend);
            } else {
                std::string opName;
                if (op == "+") opName = "ADD";
                else if (op == "-") opName = "SUB";
                else if (op == "*") opName = "MUL";
                else if (op == "/") opName = "DIV";
                else if (op == "%") opName = "MOD";
                else if (op == "^") opName = "POW";
                emit(opName, a.name, b.name, t);
            }
            return {t, false, 0};
        }
        default:
            break;
    }
    return {"0", true, 0};
}

void IRBuilder::genCond(Node* expr, const std::string& ltrue, const std::string& lfalse) {
    if (!expr) {
        emit("GOTO", "-", "-", ltrue);
        return;
    }
    if (expr->kind == NodeKind::BinOp) {
        const std::string& op = expr->text;
        if (op == "&&") {
            std::string mid = newLabel();
            genCond(expr->children[0], mid, lfalse);
            emit("LABEL", "-", "-", mid);
            genCond(expr->children[1], ltrue, lfalse);
            return;
        }
        if (op == "||") {
            std::string mid = newLabel();
            genCond(expr->children[0], ltrue, mid);
            emit("LABEL", "-", "-", mid);
            genCond(expr->children[1], ltrue, lfalse);
            return;
        }
        if (op == "<" || op == "<=" || op == ">" || op == ">=" || op == "==" || op == "!=") {
            auto a = genExpr(expr->children[0]);
            auto b = genExpr(expr->children[1]);
            std::string opName = "IF" + op;
            emit(opName, a.name, b.name, ltrue);
            emit("GOTO", "-", "-", lfalse);
            return;
        }
    }
    auto v = genExpr(expr);
    emit("IFNZ", v.name, "-", ltrue);
    emit("GOTO", "-", "-", lfalse);
}

void IRBuilder::genStmt(Node* stmt) {
    if (!stmt) return;
    switch (stmt->kind) {
        case NodeKind::Decl:
            // no code needed for pure declarations
            break;
        case NodeKind::Assign: {
            auto rhs = genExpr(stmt->children[1]);
            emit("MOV", rhs.name, "-", stmt->children[0]->text);
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
            genCond(stmt->children[0], ltrue, lfalse);
            emit("LABEL", "-", "-", ltrue);
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
            genCond(stmt->children[0], lbody, lend);
            emit("LABEL", "-", "-", lbody);
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
                genCond(stmt->children[1], lbody, lend);
            } else {
                emit("GOTO", "-", "-", lbody);
            }
            emit("LABEL", "-", "-", lbody);
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
