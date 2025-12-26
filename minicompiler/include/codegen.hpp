// Pseudo assembly generation from quads
#pragma once
#include "ir.hpp"
#include <string>
#include <vector>

namespace mc {

std::vector<std::string> toAssembly(const std::vector<Quad>& code);

}  // namespace mc
