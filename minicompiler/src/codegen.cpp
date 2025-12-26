// Convert quads to x86 (NASM-like) assembly
#include "codegen.hpp"
#include <set>
#include <sstream>
#include <unordered_map>

namespace mc {
namespace {

// Simple helper to check if a string is an immediate integer literal
bool isImm(const std::string& s, long long& v) {
    if (s.empty()) return false;
    try {
        size_t idx = 0;
        v = std::stoll(s, &idx, 10);
        return idx == s.size();
    } catch (...) {
        return false;
    }
}

bool isLabelName(const std::string& s) {
    return !s.empty() && s[0] == 'L';
}

struct FunctionIR {
    std::string name;
    std::vector<Quad> quads;
    std::vector<std::string> locals; // variables + temporaries
    std::unordered_map<std::string, int> offsets; // name -> ebp offset
    int stackSize = 0;
};

void addVarIfNeeded(const std::string& name, std::set<std::string>& vars) {
    if (name == "-" || name.empty()) return;
    if (isLabelName(name)) return; // labels are not stored
    long long dummy = 0;
    if (isImm(name, dummy)) return; // immediates are not stored
    vars.insert(name);
}

// Slice quads into per-function chunks and collect locals/temps
std::vector<FunctionIR> splitFunctions(const std::vector<Quad>& code) {
    std::vector<FunctionIR> funcs;
    FunctionIR current;
    bool inFunc = false;
    std::set<std::string> vars;

    auto finalize = [&]() {
        if (!inFunc) return;
        current.locals.assign(vars.begin(), vars.end());
        int offset = 0;
        for (const auto& v : current.locals) {
            offset += 4;
            current.offsets[v] = -offset;
        }
        current.stackSize = (offset + 15) / 16 * 16; // 16-byte align for calls
        funcs.push_back(current);
        current = FunctionIR{};
        vars.clear();
        inFunc = false;
    };

    for (const auto& q : code) {
        if (q.op == "FUNC_BEGIN") {
            finalize();
            inFunc = true;
            current.name = q.arg1.empty() ? "main" : q.arg1;
            continue;
        }
        if (q.op == "FUNC_END") {
            finalize();
            continue;
        }
        if (!inFunc) continue; // skip stray code
        current.quads.push_back(q);

        addVarIfNeeded(q.arg1, vars);
        addVarIfNeeded(q.arg2, vars);
        if (q.op != "LABEL" && !isLabelName(q.res)) {
            addVarIfNeeded(q.res, vars);
        }
    }

    finalize();
    return funcs;
}

std::string memRef(const FunctionIR& fn, const std::string& name) {
    auto it = fn.offsets.find(name);
    if (it == fn.offsets.end()) return name; // unexpected, but avoid crash
    int off = it->second;
    if (off == 0) return "[ebp]";
    std::ostringstream os;
    os << "[ebp" << (off > 0 ? "+" : "") << off << "]";
    return os.str();
}

void loadToReg(std::vector<std::string>& out, const FunctionIR& fn, const std::string& src, const std::string& reg) {
    long long imm = 0;
    if (isImm(src, imm)) {
        out.push_back("    mov " + reg + ", " + src);
    } else {
        out.push_back("    mov " + reg + ", " + memRef(fn, src));
    }
}

void storeFromReg(std::vector<std::string>& out, const FunctionIR& fn, const std::string& dst, const std::string& reg) {
    if (dst == "-" || dst.empty()) return;
    out.push_back("    mov " + memRef(fn, dst) + ", " + reg);
}

void boolify(std::vector<std::string>& out, const std::string& reg, const std::string& low8) {
    out.push_back("    cmp " + reg + ", 0");
    out.push_back("    setne " + low8);
    out.push_back("    movzx " + reg + ", " + low8);
}

std::string setccForCmp(const std::string& op) {
    if (op == "<") return "setl";
    if (op == "<=") return "setle";
    if (op == ">") return "setg";
    if (op == ">=") return "setge";
    if (op == "==") return "sete";
    if (op == "!=") return "setne";
    return {};
}

std::string jccForCmp(const std::string& op) {
    if (op == "<") return "jl";
    if (op == "<=") return "jle";
    if (op == ">") return "jg";
    if (op == ">=") return "jge";
    if (op == "==") return "je";
    if (op == "!=") return "jne";
    return {};
}

} // namespace

std::vector<std::string> toAssembly(const std::vector<Quad>& code) {
    auto funcs = splitFunctions(code);
    std::vector<std::string> out;
    out.reserve(code.size() * 4 + 32);

    out.push_back("; x86 (32-bit) assembly emitted from IR");
    out.push_back("extern printf");
    out.push_back("extern scanf");
    out.push_back("section .data");
    out.push_back("fmt_read  db \"%d\", 0");
    out.push_back("fmt_write db \"%d\", 10, 0");
    out.push_back("section .text");

    int powId = 0;

    for (const auto& fn : funcs) {
        if (!fn.name.empty()) {
            out.push_back("global " + fn.name);
        }
        out.push_back(fn.name + ":");
        out.push_back("    push ebp");
        out.push_back("    mov ebp, esp");
        if (fn.stackSize > 0) {
            out.push_back("    sub esp, " + std::to_string(fn.stackSize));
        }

        std::string retLabel = fn.name + "_ret";

        for (const auto& q : fn.quads) {
            if (q.op == "LABEL") {
                out.push_back(q.res + ":");
                continue;
            }
            if (q.op == "GOTO") {
                out.push_back("    jmp " + q.res);
                continue;
            }
            if (q.op == "JZ") {
                long long imm = 0;
                if (isImm(q.arg1, imm)) {
                    if (imm == 0) out.push_back("    jmp " + q.res);
                    continue;
                }
                loadToReg(out, fn, q.arg1, "eax");
                out.push_back("    cmp eax, 0");
                out.push_back("    je " + q.res);
                continue;
            }
            if (q.op.rfind("IF", 0) == 0) {
                std::string cmp = jccForCmp(q.op.substr(2));
                if (!cmp.empty()) {
                    loadToReg(out, fn, q.arg1, "eax");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    cmp eax, ebx");
                    out.push_back("    " + cmp + " " + q.res);
                } else {
                    out.push_back("    ; unhandled conditional " + q.op);
                }
                continue;
            }
            if (q.op == "=" || q.op == "MOV") {
                loadToReg(out, fn, q.arg1, "eax");
                storeFromReg(out, fn, q.res, "eax");
                continue;
            }
            if (q.op == "NEG") {
                loadToReg(out, fn, q.arg1, "eax");
                out.push_back("    neg eax");
                storeFromReg(out, fn, q.res, "eax");
                continue;
            }
            if (q.op == "NOT") {
                loadToReg(out, fn, q.arg1, "eax");
                boolify(out, "eax", "al");
                out.push_back("    xor eax, 1"); // logical not
                storeFromReg(out, fn, q.res, "eax");
                continue;
            }
            if (q.op == "&&" || q.op == "||") {
                loadToReg(out, fn, q.arg1, "eax");
                loadToReg(out, fn, q.arg2, "ebx");
                boolify(out, "eax", "al");
                boolify(out, "ebx", "bl");
                if (q.op == "&&") {
                    out.push_back("    and eax, ebx");
                } else {
                    out.push_back("    or eax, ebx");
                }
                boolify(out, "eax", "al");
                storeFromReg(out, fn, q.res, "eax");
                continue;
            }
            if (q.op == "<" || q.op == "<=" || q.op == ">" || q.op == ">=" || q.op == "==" || q.op == "!=") {
                loadToReg(out, fn, q.arg1, "eax");
                loadToReg(out, fn, q.arg2, "ebx");
                out.push_back("    cmp eax, ebx");
                std::string setcc = setccForCmp(q.op);
                out.push_back("    " + setcc + " al");
                out.push_back("    movzx eax, al");
                storeFromReg(out, fn, q.res, "eax");
                continue;
            }
            if (q.op == "+" || q.op == "-" || q.op == "*" || q.op == "/" || q.op == "%" || q.op == "^") {
                if (q.op == "^") {
                    int id = powId++;
                    std::string loop = "pow_loop_" + std::to_string(id);
                    std::string done = "pow_done_" + std::to_string(id);
                    loadToReg(out, fn, q.arg1, "eax");
                    loadToReg(out, fn, q.arg2, "ecx");
                    out.push_back("    mov ebx, 1");
                    out.push_back("    cmp ecx, 0");
                    out.push_back("    jl " + done);
                    out.push_back(loop + ":");
                    out.push_back("    cmp ecx, 0");
                    out.push_back("    je " + done);
                    out.push_back("    imul ebx, eax");
                    out.push_back("    dec ecx");
                    out.push_back("    jmp " + loop);
                    out.push_back(done + ":");
                    out.push_back("    mov eax, ebx");
                    storeFromReg(out, fn, q.res, "eax");
                } else if (q.op == "+") {
                    loadToReg(out, fn, q.arg1, "eax");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    add eax, ebx");
                    storeFromReg(out, fn, q.res, "eax");
                } else if (q.op == "-") {
                    loadToReg(out, fn, q.arg1, "eax");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    sub eax, ebx");
                    storeFromReg(out, fn, q.res, "eax");
                } else if (q.op == "*") {
                    loadToReg(out, fn, q.arg1, "eax");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    imul eax, ebx");
                    storeFromReg(out, fn, q.res, "eax");
                } else if (q.op == "/") {
                    loadToReg(out, fn, q.arg1, "eax");
                    out.push_back("    cdq");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    idiv ebx");
                    storeFromReg(out, fn, q.res, "eax");
                } else if (q.op == "%") {
                    loadToReg(out, fn, q.arg1, "eax");
                    out.push_back("    cdq");
                    loadToReg(out, fn, q.arg2, "ebx");
                    out.push_back("    idiv ebx");
                    storeFromReg(out, fn, q.res, "edx");
                }
                continue;
            }
            if (q.op == "READ") {
                out.push_back("    ; READ " + q.arg1);
                out.push_back("    lea eax, " + memRef(fn, q.arg1));
                out.push_back("    push eax");
                out.push_back("    push fmt_read");
                out.push_back("    call scanf");
                out.push_back("    add esp, 8");
                continue;
            }
            if (q.op == "WRITE") {
                out.push_back("    ; WRITE " + q.arg1);
                loadToReg(out, fn, q.arg1, "eax");
                out.push_back("    push eax");
                out.push_back("    push fmt_write");
                out.push_back("    call printf");
                out.push_back("    add esp, 8");
                continue;
            }
            if (q.op == "return" || q.op == "RETURN") {
                if (q.arg1 != "-" && !q.arg1.empty()) {
                    loadToReg(out, fn, q.arg1, "eax");
                }
                out.push_back("    jmp " + retLabel);
                continue;
            }

            // Fallback: keep unhandled ops visible for debugging
            std::ostringstream os;
            os << "    ; unhandled op " << q.op << " " << q.arg1 << " " << q.arg2 << " " << q.res;
            out.push_back(os.str());
        }

        out.push_back(retLabel + ":");
        out.push_back("    mov esp, ebp");
        out.push_back("    pop ebp");
        out.push_back("    ret");
    }

    return out;
}

}  // namespace mc
