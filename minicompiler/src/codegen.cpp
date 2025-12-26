// Convert quads to a simple textual assembly
#include "codegen.hpp"
#include <sstream>

namespace mc {

static bool isLabelOp(const std::string& op) {
    return op == "LABEL" || op == "GOTO" || op.rfind("IF", 0) == 0;
}

std::vector<std::string> toAssembly(const std::vector<Quad>& code) {
    std::vector<std::string> out;
    out.reserve(code.size() * 2);
    for (const auto& q : code) {
        std::ostringstream os;
        if (q.op == "LABEL") {
            os << q.res << ":";
        } else if (q.op == "GOTO") {
            os << "JMP " << q.res;
        } else if (q.op.rfind("IF", 0) == 0) {
            os << q.op.substr(2) << " " << q.arg1;
            if (q.arg2 != "-") os << ", " << q.arg2;
            os << " -> " << q.res;
        } else if (q.op == "=" || q.op == "MOV") {
            os << "MOV " << q.res << ", " << q.arg1;
        } else if (q.op == "NEG") {
            os << "NEG " << q.res << ", " << q.arg1;
        } else if (q.op == "NOT") {
            os << "NOT " << q.res << ", " << q.arg1;
        } else if (q.op == "&&" || q.op == "||" || q.op == "<" || q.op == "<=" ||
                   q.op == ">" || q.op == ">=" || q.op == "==" || q.op == "!=") {
            os << q.op << " " << q.res << ", " << q.arg1 << ", " << q.arg2;
        } else if (q.op == "JZ") {
            os << "JZ " << q.arg1 << " -> " << q.res;
        } else if (q.op == "ADD" || q.op == "SUB" || q.op == "MUL" || q.op == "DIV" || q.op == "MOD" || q.op == "POW") {
            os << q.op << " " << q.res << ", " << q.arg1 << ", " << q.arg2;
        } else if (q.op == "FUNC_BEGIN") {
            os << "FUNC_BEGIN " << q.arg1;
        } else if (q.op == "FUNC_END") {
            os << "FUNC_END " << q.arg1;
        } else if (q.op == "RETURN") {
            os << "RETURN " << q.arg1;
        } else if (q.op == "READ") {
            os << "READ " << q.arg1;
        } else if (q.op == "WRITE") {
            os << "WRITE " << q.arg1;
        } else {
            os << q.op << " " << q.arg1 << " " << q.arg2 << " " << q.res;
        }
        out.push_back(os.str());
    }
    return out;
}

}  // namespace mc
