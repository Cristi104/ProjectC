//
// Created by Cristi on 2/9/2025.
//

#ifndef PROJECTC_PERLINNOISEGENERATOR_H
#define PROJECTC_PERLINNOISEGENERATOR_H

#include <vector>
#include "raylib.h"
#include "Game_exports.h"

namespace GmLib {
    /// generates a 2d array of size by size elements representing a perlin noise
    /// @param size width and heigth of the returned array
    /// @param seed seed used for generation the same seed always generates the same map
    /// @param density number of sample points between grid points (higher values generate bigger features while smaller ones get closer to random noise)
    GAME_EXPORTS std::vector<std::vector<float>>
    GeneratePerlinNoise(unsigned int size, unsigned int seed = 0, unsigned int density = 20);

    /// generates a 2d array of size by size elements representing a perlin noise with Brownian motion
    /// @param size width and heigth of the returned array
    /// @param seed seed used for generation the same seed always generates the same map
    /// @param density number of sample points between grid points (higher values generate bigger features while smaller ones get closer to random noise)
    /// @param octaves number of octaves to use for generation (higher values generate more jagged edges)
    /// @param amplitudeScaling how much each octave influences the final result (values smaller than 1 decrease the effect of each octave while above 1 increases)
    /// @param frequencyScaling how much each octave's density is changed (values smaller than 1 increase the density of each octave while above 1 decreases)
    GAME_EXPORTS std::vector<std::vector<float>>
    GenerateFractalBrownianMotion(unsigned int size, unsigned int seed = 0, unsigned int density = 20, unsigned int octaves = 8,
                                  float amplitudeScaling = 0.7, float frequencyScaling = 1.5);
} // Gmlib

#endif //PROJECTC_PERLINNOISEGENERATOR_H
