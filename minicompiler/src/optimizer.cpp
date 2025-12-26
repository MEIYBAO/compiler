// Basic optimizations: constant folding and dead code elimination
#include "optimizer.hpp"
#include <unordered_set>
#include <regex>
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

static std::string compute(const Quad& q, bool& ok) {
    ok = false;
    long long a, b;
    if (!isImm(q.arg1, a) || (!isImm(q.arg2, b) && q.arg2 != "-")) return {};
    if (q.op == "ADD") { ok = true; return std::to_string(a + b); }
    if (q.op == "SUB") { ok = true; return std::to_string(a - b); }
    if (q.op == "MUL") { ok = true; return std::to_string(a * b); }
    if (q.op == "DIV") { if (b == 0) return {}; ok = true; return std::to_string(a / b); }
    if (q.op == "MOD") { if (b == 0) return {}; ok = true; return std::to_string(a % b); }
    if (q.op == "POW") { ok = true; return std::to_string(static_cast<long long>(std::pow(a, b))); }
    if (q.op == "NEG") { ok = true; return std::to_string(-a); }
    if (q.op == "NOT") { ok = true; return std::to_string(!a); }
    if (q.op == "IF<" || q.op == "IF<=" || q.op == "IF>" || q.op == "IF>=" || q.op == "IF==" || q.op == "IF!=") {
        ok = true;
        bool cond = false;
        if (q.op == "IF<") cond = a < b;
        else if (q.op == "IF<=") cond = a <= b;
        else if (q.op == "IF>") cond = a > b;
        else if (q.op == "IF>=") cond = a >= b;
        else if (q.op == "IF==") cond = a == b;
        else if (q.op == "IF!=") cond = a != b;
        return cond ? "1" : "0";
    }
    return {};
}

void constantFold(std::vector<Quad>& code) {
    for (auto& q : code) {
        bool ok = false;
        std::string val = compute(q, ok);
        if (ok && (q.op.rfind("IF", 0) != 0)) {
            q.op = "MOV";
            q.arg1 = val;
            q.arg2 = "-";
        } else if (ok && q.op.rfind("IF", 0) == 0) {
            // constant conditional: replace with direct jump or NOP
            if (val == "1") {
                q.op = "GOTO";
                q.arg1 = q.arg2 = "-";
                // res keeps target label
            } else {
                q.op = "NOP";
            }
        }
    }
    // remove NOPs
    std::vector<Quad> cleaned;
    cleaned.reserve(code.size());
    for (auto& q : code) {
        if (q.op == "NOP") continue;
        cleaned.push_back(q);
    }
    code.swap(cleaned);
}

void deadCodeEliminate(std::vector<Quad>& code) {
    std::unordered_set<std::string> used;
    for (const auto& q : code) {
        auto mark = [&](const std::string& s) {
            long long tmp;
            if (s == "-" || isImm(s, tmp)) return;
            used.insert(s);
        };
        if (q.op == "LABEL") continue;
        mark(q.arg1);
        mark(q.arg2);
        if (q.op.rfind("IF", 0) == 0 || q.op == "GOTO" || q.op == "READ" || q.op == "WRITE") {
            mark(q.res);
        }
    }
    std::vector<Quad> kept;
    kept.reserve(code.size());
    for (const auto& q : code) {
        if (q.res.rfind("t", 0) == 0 && used.find(q.res) == used.end() &&
            (q.op == "MOV" || q.op == "ADD" || q.op == "SUB" || q.op == "MUL" ||
             q.op == "DIV" || q.op == "MOD" || q.op == "POW" || q.op == "NEG" || q.op == "NOT")) {
            continue; // dead temp
        }
        kept.push_back(q);
    }
    code.swap(kept);
}

}  // namespace mc
