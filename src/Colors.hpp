//
// Created by talleux on 2/16/24.
//

#pragma once

#include <string>

static std::string color(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
