//
// Created by Cristi on 2/9/2025.
//

#include "../include/PerlinNoiseGenerator.h"
#include "raylib.h"
#include <random>
#include <array>
#include <algorithm>

namespace Gmlib {

    float dotProduct(Vector2 a, Vector2 b){
        return a.x * b.x + a.y * b.y;
    }

    Vector2 constantVector(unsigned int permutation){
        switch (permutation % 4) {
            default:
            case 0:
                return {-1, -1};
            case 1:
                return {1, -1};
            case 2:
                return {-1, 1};
            case 3:
                return {1, 1};
        }
    }

    float Fade(float x){
        return ((6 * x - 15) * x + 10) * x * x * x;
    }

    float Lerp(float x, float a1, float a2){
        return a1 + x * (a2 - a1);
    }

    std::vector<std::vector<float>> GeneratePerlinNoise(unsigned int size, unsigned int density, unsigned int seed){
        // based on algorithm provided here: https://rtouti.github.io/graphics/perlin-noise-algorithm

        std::random_device rd;
        std::mt19937 gen(rd());
        if(seed == 0)
            seed = gen();
        gen.seed(seed);

        std::array<unsigned int, 257> permutations{};
        for(unsigned int i = 0; i < 256; i++)
            permutations[i] = i;
        std::shuffle(std::begin(permutations), std::end(permutations), gen);
        permutations[256] = permutations[0];

        std::vector<std::vector<float>> noise(size);
        for(unsigned int i = 0; i < size; i++)
            noise.emplace_back(size);

        for(unsigned int i = 0; i < size; i++){
            for(unsigned int j = 0; j < size; j++){
                const Vector2 coords = {i / static_cast<float>(density), j / static_cast<float>(density)};
                const unsigned int x = (i / density) % 256;
                const unsigned int y = (j / density) % 256;
                const float xf = coords.x - floor(coords.x);
                const float yf = coords.y - floor(coords.y);

                const Vector2 topRight = {xf - 1, yf -1};
                const Vector2 topLeft = {xf, yf - 1};
                const Vector2 bottomRight = {xf - 1, yf};
                const Vector2 bottomLeft = {xf, yf};

                const float dotTopRight = dotProduct(topRight, constantVector(permutations[permutations[x + 1] + y + 1]));
                const float dotTopLeft = dotProduct(topLeft, constantVector(permutations[permutations[x] + y + 1]));
                const float dotBottomRight = dotProduct(bottomRight, constantVector(permutations[permutations[x + 1] + y]));
                const float dotBottomLeft = dotProduct(bottomLeft, constantVector(permutations[permutations[x] + y]));

                const float u = Fade(xf);
                const float v = Fade(yf);

                noise[i].emplace_back(Lerp(u,
                                   Lerp(v, dotBottomLeft, dotTopLeft),
                                   Lerp(v, dotBottomRight, dotTopRight)));
            }
        }

        return noise;
    }
} // Gmlib