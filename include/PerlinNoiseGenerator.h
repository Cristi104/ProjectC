//
// Created by Cristi on 2/9/2025.
//

#ifndef PROJECTC_PERLINNOISEGENERATOR_H
#define PROJECTC_PERLINNOISEGENERATOR_H

#include <vector>
#include "raylib.h"
#include "Game_exports.h"

namespace Gmlib {
    /// generates a 2d array of size by size elements representing a perlin noise
    /// @param size width and heigth of the returned array
    /// @param density number of sample points between grid points (higher values generate bigger features while smaller ones get closer to random noise)
    /// @param seed seed used for generation the same seed always generates the same map
    GAME_EXPORTS std::vector<std::vector<float>>
    GeneratePerlinNoise(unsigned int size, unsigned int density = 20, unsigned int seed = 0);

    /// generates a 2d array of size by size elements representing a perlin noise with Brownian motion
    /// @param size width and heigth of the returned array
    /// @param density number of sample points between grid points (higher values generate bigger features while smaller ones get closer to random noise)
    /// @param seed seed used for generation the same seed always generates the same map
    /// @param octaves number of octaves to use for generation (higher values generate more jagged edges)
    /// @param amplitudeSettings how much each octave influences the final result (the first is x=1 second is 1 * y=0.7 third is 1 * 0.7 ^ 2 and so on)
    /// @param frequencySettings how much each octave's density is changed (the first is density * x=1 the second is density * 1 * y=0.5 and so on)
    GAME_EXPORTS std::vector<std::vector<float>>
    GenerateFractalBrownianMotion(unsigned int size, unsigned int density = 20, unsigned int seed = 0, unsigned int octaves = 8,
                                  Vector2 amplitudeSettings = {1, 0.7}, Vector2 frequencySettings = {1, 0.5});
} // Gmlib

#endif //PROJECTC_PERLINNOISEGENERATOR_H
