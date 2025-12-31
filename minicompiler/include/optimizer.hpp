// Simple IR optimizations
#pragma once
#include "ir.hpp"

namespace mc {

void constantFold(std::vector<Quad>& code);
void globalConstProp(std::vector<Quad>& code);
void strengthReduce(std::vector<Quad>& code);
void deadCodeEliminate(std::vector<Quad>& code);
void simplifyControl(std::vector<Quad>& code);
void copyPropagate(std::vector<Quad>& code);
void commonSubexprElim(std::vector<Quad>& code);
void codeMotion(std::vector<Quad>& code);

}  // namespace mc
