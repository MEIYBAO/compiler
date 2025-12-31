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

static bool isPure(const Quad& q);

// Strength reduction / algebraic simplifications that keep existing op set
void strengthReduce(std::vector<Quad>& code) {
    auto isZero = [](const std::string& s) {
        long long v = 0;
        return isImm(s, v) && v == 0;
    };
    auto isOne = [](const std::string& s) {
        long long v = 0;
        return isImm(s, v) && v == 1;
    };

    for (auto& q : code) {
        if (q.res == "-" || q.res.empty()) continue;
        const std::string& a = q.arg1;
        const std::string& b = q.arg2;
        if (q.op == "+") {
            if (isZero(a)) { q.op = "MOV"; q.arg1 = b; q.arg2 = "-"; }
            else if (isZero(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
        } else if (q.op == "-") {
            if (isZero(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
        } else if (q.op == "*") {
            if (isZero(a) || isZero(b)) { q.op = "MOV"; q.arg1 = "0"; q.arg2 = "-"; }
            else if (isOne(a)) { q.op = "MOV"; q.arg1 = b; q.arg2 = "-"; }
            else if (isOne(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
        } else if (q.op == "/") {
            if (isOne(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
            else if (isZero(a)) { q.op = "MOV"; q.arg1 = "0"; q.arg2 = "-"; }
        } else if (q.op == "%") {
            if (isOne(b) || isZero(a)) { q.op = "MOV"; q.arg1 = "0"; q.arg2 = "-"; }
        } else if (q.op == "^") {
            if (isZero(b)) { q.op = "MOV"; q.arg1 = "1"; q.arg2 = "-"; }
            else if (isOne(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
            else if (isOne(a)) { q.op = "MOV"; q.arg1 = "1"; q.arg2 = "-"; }
        } else if (q.op == "&&") {
            if (isZero(a) || isZero(b)) { q.op = "MOV"; q.arg1 = "0"; q.arg2 = "-"; }
            else if (isOne(a)) { q.op = "MOV"; q.arg1 = b; q.arg2 = "-"; }
            else if (isOne(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
        } else if (q.op == "||") {
            if (isOne(a) || isOne(b)) { q.op = "MOV"; q.arg1 = "1"; q.arg2 = "-"; }
            else if (isZero(a)) { q.op = "MOV"; q.arg1 = b; q.arg2 = "-"; }
            else if (isZero(b)) { q.op = "MOV"; q.arg1 = a; q.arg2 = "-"; }
        }
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
    std::unordered_map<std::string, std::string> constEnv; // var -> const string

    auto resolveConst = [&](std::string& s) {
        long long tmp = 0;
        if (isImm(s, tmp)) return;
        auto it = constEnv.find(s);
        if (it != constEnv.end()) s = it->second;
    };

    for (auto& q : code) {
        if (q.op == "LABEL") {
            constEnv.clear();
            continue;
        }

        // substitute known constants
        if (q.op != "READ") {
            resolveConst(q.arg1);
            resolveConst(q.arg2);
        }

        bool ok = false;
        std::string val = compute(q, ok);
        bool producedConst = false;

        if (ok && (q.op.rfind("IF", 0) != 0) && q.op != "JZ") {
            q.op = "MOV";
            q.arg1 = val;
            q.arg2 = "-";
            producedConst = true;
        } else if (ok && q.op == "JZ") {
            if (val == "0") {
                q.op = "GOTO";
                q.arg1 = "-";
                q.arg2 = "-";
            } else {
                q.op = "NOP";
            }
            constEnv.clear();
        } else if (ok && q.op.rfind("IF", 0) == 0) {
            if (val == "1") {
                q.op = "GOTO";
                q.arg1 = q.arg2 = "-";
            } else {
                q.op = "NOP";
            }
            constEnv.clear();
        }

        // env maintenance
        if (q.op == "READ") {
            if (q.arg1 != "-") constEnv.erase(q.arg1);
        }
        if (q.res != "-" && !q.res.empty()) {
            if (producedConst) constEnv[q.res] = val;
            else constEnv.erase(q.res);
        }
        if (q.op == "GOTO" || q.op == "JZ" || q.op.rfind("IF", 0) == 0 ||
            q.op == "return" || q.op == "RETURN") {
            constEnv.clear();
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
    std::unordered_set<std::string> live;
    auto addLive = [&](const std::string& s) {
        long long tmp;
        if (s == "-" || isImm(s, tmp)) return;
        live.insert(s);
    };
    auto isPureOp = [&](const Quad& q) {
        return q.op == "=" || q.op == "MOV" || isPure(q);
    };
    auto isControl = [&](const Quad& q) {
        return q.op == "GOTO" || q.op == "JZ" || q.op.rfind("IF", 0) == 0;
    };
    auto isSideEffect = [&](const Quad& q) {
        return q.op == "READ" || q.op == "WRITE" || isControl(q) || q.op == "return" || q.op == "RETURN";
    };

    std::vector<Quad> kept;
    kept.reserve(code.size());

    for (auto it = code.rbegin(); it != code.rend(); ++it) {
        const auto& q = *it;
        if (q.op == "LABEL") {
            // boundary of basic block: be conservative, keep label and reset liveness
            kept.push_back(q);
            live.clear();
            continue;
        }

        bool remove = false;
        if (isPureOp(q) && !isSideEffect(q) && !q.res.empty() && q.res != "-") {
            if (live.find(q.res) == live.end()) {
                remove = true; // dead store
            }
        }

        if (!remove) {
            kept.push_back(q);
            // update liveness: kill def, add uses
            live.erase(q.res);
            addLive(q.arg1);
            addLive(q.arg2);
            // branches/IO: result may be a target/param, keep it live
            if (isControl(q) || q.op == "WRITE" || q.op == "READ") {
                addLive(q.res);
            }
        }
    }

    std::reverse(kept.begin(), kept.end());
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

// Simple loop-aware code motion: hoist loop-invariant pure computations to a preheader
void codeMotion(std::vector<Quad>& code) {
    std::vector<Quad> out;
    out.reserve(code.size());
    size_t i = 0;
    while (i < code.size()) {
        const auto& q = code[i];
        if (q.op != "LABEL") {
            out.push_back(q);
            ++i;
            continue;
        }

        const std::string label = q.res;
        size_t backIdx = code.size();
        int jumpsToLabel = 0;
        bool hasPrevJump = false;
        for (size_t k = 0; k < i; ++k) {
            if ((code[k].op == "GOTO" || code[k].op == "JZ" || code[k].op.rfind("IF", 0) == 0) &&
                code[k].res == label) {
                hasPrevJump = true;
                break;
            }
        }
        // find a backward GOTO that closes the loop
        for (size_t k = i + 1; k < code.size(); ++k) {
            if (code[k].op == "GOTO" && code[k].res == label) {
                backIdx = k;
                jumpsToLabel++;
                break;
            }
            if (code[k].op == "LABEL" && k != i) break; // stop at next block
        }
        // count other jumps to this label within the same block
        for (size_t k = i + 1; k < backIdx && k < code.size(); ++k) {
            if ((code[k].op == "GOTO" || code[k].op == "JZ" || code[k].op.rfind("IF", 0) == 0) &&
                code[k].res == label) {
                jumpsToLabel++;
            }
        }

        if (hasPrevJump || backIdx == code.size() || jumpsToLabel > 1) {
            // not a simple loop, keep as is
            out.push_back(q);
            ++i;
            continue;
        }

        // collect writes inside loop body [i+1, backIdx)
        std::unordered_map<std::string, int> writeCount;
        std::unordered_set<std::string> bodyWrites;
        for (size_t k = i + 1; k < backIdx; ++k) {
            const auto& bq = code[k];
            if (bq.op == "READ" && bq.arg1 != "-") {
                writeCount[bq.arg1]++;
                bodyWrites.insert(bq.arg1);
            }
            if (bq.res != "-" && !bq.res.empty()) {
                writeCount[bq.res]++;
                bodyWrites.insert(bq.res);
            }
        }

        std::vector<Quad> hoist;
        std::unordered_set<size_t> skipIdx;
        for (size_t k = i + 1; k < backIdx; ++k) {
            const auto& bq = code[k];
            if (!(isPure(bq) || bq.op == "=" || bq.op == "MOV")) continue;
            if (bq.res == "-" || bq.res.empty()) continue;
            // only hoist if result is a temp and written once in loop
            if (writeCount[bq.res] != 1) continue;
            if (bq.res.rfind("t", 0) != 0) continue; // be conservative: only temps

            auto operandSafe = [&](const std::string& s) {
                if (s == "-" || s.empty()) return true;
                long long v = 0;
                if (isImm(s, v)) return true;
                return bodyWrites.find(s) == bodyWrites.end();
            };
            if (!operandSafe(bq.arg1) || !operandSafe(bq.arg2)) continue;

            hoist.push_back(bq);
            skipIdx.insert(k);
        }

        if (hoist.empty()) {
            out.push_back(q);
            ++i;
            continue;
        }

        // create preheader label
        std::string preLabel = label + "_pre";
        out.push_back({"LABEL", "-", "-", preLabel});
        for (auto& h : hoist) out.push_back(h);
        out.push_back(q); // original loop label

        // copy loop body, skipping hoisted instructions
        for (size_t k = i + 1; k <= backIdx; ++k) {
            if (skipIdx.count(k)) continue;
            Quad nq = code[k];
            // keep back edge targeting the original label; no other jumps expected here
            out.push_back(nq);
        }

        // advance
        i = backIdx + 1;
        // retarget future jumps to this loop entry to the preheader
        for (size_t k = i; k < code.size(); ++k) {
            auto& fq = code[k];
            if ((fq.op == "GOTO" || fq.op == "JZ" || fq.op.rfind("IF", 0) == 0) && fq.res == label) {
                fq.res = preLabel;
            }
        }
    }
    code.swap(out);
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
