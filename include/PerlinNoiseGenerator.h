//
// Created by Cristi on 2/9/2025.
//

#ifndef PROJECTC_PERLINNOISEGENERATOR_H
#define PROJECTC_PERLINNOISEGENERATOR_H

#include <vector>
#include "Game_exports.h"

namespace Gmlib {
    GAME_EXPORTS std::vector<std::vector<float>> GeneratePerlinNoise(unsigned int size, unsigned int density = 11, unsigned int seed = 0);
} // Gmlib

#endif //PROJECTC_PERLINNOISEGENERATOR_H
