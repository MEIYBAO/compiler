// Basic optimizations: constant folding and dead code elimination
#include "optimizer.hpp"
#include <unordered_set>
#include <unordered_map>
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
    if (q.op == "+") { ok = true; return std::to_string(a + b); }
    if (q.op == "-") { ok = true; return std::to_string(a - b); }
    if (q.op == "*") { ok = true; return std::to_string(a * b); }
    if (q.op == "/") { if (b == 0) return {}; ok = true; return std::to_string(a / b); }
    if (q.op == "%") { if (b == 0) return {}; ok = true; return std::to_string(a % b); }
    if (q.op == "^") { ok = true; return std::to_string(static_cast<long long>(std::pow(a, b))); }
    if (q.op == "NEG") { ok = true; return std::to_string(-a); }
    if (q.op == "NOT") { ok = true; return std::to_string(!a); }
    if (q.op == "&&") { ok = true; return std::to_string((a && b) ? 1 : 0); }
    if (q.op == "||")  { ok = true; return std::to_string((a || b) ? 1 : 0); }
    if (q.op == "<")  { ok = true; return std::to_string(a < b); }
    if (q.op == "<=")  { ok = true; return std::to_string(a <= b); }
    if (q.op == ">")  { ok = true; return std::to_string(a > b); }
    if (q.op == ">=")  { ok = true; return std::to_string(a >= b); }
    if (q.op == "==")  { ok = true; return std::to_string(a == b); }
    if (q.op == "!=")  { ok = true; return std::to_string(a != b); }
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
        if (ok && (q.op.rfind("IF", 0) != 0) && q.op != "JZ") {
            q.op = "MOV";
            q.arg1 = val;
            q.arg2 = "-";
        } else if (ok && q.op == "JZ") {
            // if condition const
            if (val == "0") {
                // always jump -> keep as GOTO
                q.op = "GOTO";
                q.arg1 = "-";
                q.arg2 = "-";
                // res is label
            } else {
                q.op = "NOP"; // never jump
            }
        } else if (ok && q.op.rfind("IF", 0) == 0) {
            if (val == "1") {
                q.op = "GOTO";
                q.arg1 = q.arg2 = "-";
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
            (q.op == "=" || q.op == "MOV" || q.op == "+" || q.op == "-" || q.op == "*" ||
             q.op == "/" || q.op == "%" || q.op == "^" || q.op == "NEG" || q.op == "NOT" ||
             q.op == "&&" || q.op == "||" || q.op == "<" || q.op == "<=" || q.op == ">" ||
             q.op == ">=" || q.op == "==" || q.op == "!=")) {
            continue; // dead temp
        }
        kept.push_back(q);
    }
    code.swap(kept);
}

void simplifyControl(std::vector<Quad>& code) {
    // 1) eliminate redundant moves (x = x)
    std::vector<Quad> tmp;
    tmp.reserve(code.size());
    for (const auto& q : code) {
        if ((q.op == "=" || q.op == "MOV") && q.arg1 == q.res) continue;
        tmp.push_back(q);
    }
    code.swap(tmp);

    // 2) merge consecutive labels and redirect jumps
    std::unordered_map<std::string, std::string> alias;
    std::vector<Quad> merged;
    merged.reserve(code.size());
    std::string lastLabel;
    bool prevWasLabel = false;
    for (const auto& q : code) {
        if (q.op == "LABEL") {
            if (prevWasLabel) {
                alias[q.res] = lastLabel;
                continue;
            }
            lastLabel = q.res;
            prevWasLabel = true;
            merged.push_back(q);
        } else {
            prevWasLabel = false;
            merged.push_back(q);
        }
    }
    auto resolve = [&](const std::string& lbl) -> std::string {
        auto it = alias.find(lbl);
        if (it == alias.end()) return lbl;
        return it->second;
    };
    for (auto& q : merged) {
        if (q.op == "GOTO" || q.op == "JZ" || q.op.rfind("IF", 0) == 0) {
            q.res = resolve(q.res);
        }
    }

    // 3) drop jumps that fall through immediately
    std::vector<Quad> noFall;
    noFall.reserve(merged.size());
    for (size_t i = 0; i < merged.size(); ++i) {
        const auto& q = merged[i];
        if (q.op == "GOTO" && i + 1 < merged.size() && merged[i + 1].op == "LABEL" && merged[i + 1].res == q.res) {
            continue;
        }
        noFall.push_back(q);
    }

    // 4) remove unreachable code until next label after unconditional jump
    std::vector<Quad> reachable;
    reachable.reserve(noFall.size());
    bool skip = false;
    for (const auto& q : noFall) {
        if (q.op == "LABEL") {
            skip = false;
            reachable.push_back(q);
            continue;
        }
        if (skip) continue;
        reachable.push_back(q);
        if (q.op == "GOTO") {
            skip = true;
        }
    }
    code.swap(reachable);
}

static bool isPure(const Quad& q) {
    return q.op == "+" || q.op == "-" || q.op == "*" || q.op == "/" ||
           q.op == "%" || q.op == "^" || q.op == "NEG" || q.op == "NOT" ||
           q.op == "&&" || q.op == "||"  || q.op == "<"  || q.op == "<="  ||
           q.op == ">"  || q.op == ">="  || q.op == "=="  || q.op == "!=";
}

void copyPropagate(std::vector<Quad>& code) {
    std::unordered_map<std::string, std::string> rep;
    auto resolve = [&](const std::string& s) {
        auto it = rep.find(s);
        return it == rep.end() ? s : it->second;
    };
    for (auto& q : code) {
        // rewrite args
        if (q.op == "LABEL") {
            rep.clear(); // new basic block, drop mappings
        } else {
            if (q.arg1 != "-") q.arg1 = resolve(q.arg1);
            if (q.arg2 != "-") q.arg2 = resolve(q.arg2);
        }
        // READ writes to arg1 (res is "-"), so kill it explicitly
        if (q.op == "READ" && q.arg1 != "-") rep.erase(q.arg1);
        // kill mapping if we assign
        if (q.res != "-" && !q.res.empty()) rep.erase(q.res);
        // add mapping for copy
        if ((q.op == "MOV" || q.op == "=") && q.res != "-" && q.arg1 != "-") {
            rep[q.res] = resolve(q.arg1);
        }
        // after control-flow edges, drop mappings to avoid leaking across branches/loops
        if (q.op == "GOTO" || q.op == "JZ" || q.op.rfind("IF", 0) == 0 || q.op == "return" || q.op == "RETURN") {
            rep.clear();
        }
    }
}

void commonSubexprElim(std::vector<Quad>& code) {
    struct Key {
        std::string op, a1, a2;
        bool operator==(const Key& o) const { return op==o.op && a1==o.a1 && a2==o.a2; }
    };
    struct Hash {
        size_t operator()(const Key& k) const {
            return std::hash<std::string>{}(k.op + "|" + k.a1 + "|" + k.a2);
        }
    };
    auto canon = [](const std::string& op, std::string a1, std::string a2) {
        if (op=="+"||op=="*"||op=="&&"||op=="||"||op=="==") {
            if (a1>a2) std::swap(a1,a2);
        }
        return Key{op,a1,a2};
    };
    std::unordered_map<Key,std::string,Hash> table;
    for (auto& q : code) {
        if (isPure(q) && q.res.rfind("t",0)==0) {
            Key k = canon(q.op, q.arg1, q.arg2);
            auto it = table.find(k);
            if (it != table.end()) {
                // reuse existing temp
                std::string existing = it->second;
                q.op = "=";
                q.arg1 = existing;
                q.arg2 = "-";
            } else {
                table[k] = q.res;
            }
        } else {
            // side-effecting op: invalidate table on assigned var
            if (q.res != "-" && !q.res.empty()) table.clear();
        }
    }
}

}  // namespace mc
