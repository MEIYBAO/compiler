// Simple IR optimizations
#pragma once
#include "ir.hpp"

namespace mc {

void constantFold(std::vector<Quad>& code);
void deadCodeEliminate(std::vector<Quad>& code);

}  // namespace mc
