//
// Created by Cristi on 2/9/2025.
//

#include "../include/PerlinNoiseGenerator.h"
#include <random>
#include <array>
#include <algorithm>

namespace GmLib {

    float dotProduct(Vector2 a, Vector2 b){
        return a.x * b.x + a.y * b.y;
    }

    Vector2 constantVector(unsigned int permutation){
        switch (permutation % 8) {
            default:
            case 0:
                return {-0.71, -0.71};
            case 1:
                return {0.71, -0.71};
            case 2:
                return {-0.71, 0.71};
            case 3:
                return {0.71, 0.71};
            case 4:
                return {-1, 0};
            case 5:
                return {1, 0};
            case 6:
                return {0, 1};
            case 7:
                return {0, -1};
            case 8:
                return {0.92, 0.38};
            case 9:
                return {0.38, 0.92};
            case 10:
                return {-0.92, 0.38};
            case 11:
                return {-0.38, 0.92};
            case 12:
                return {0.92, -0.38};
            case 13:
                return {0.38, -0.92};
            case 14:
                return {-0.92, -0.38};
            case 15:
                return {-0.38, -0.92};
        }
    }

    float Fade(float x){
        return ((6 * x - 15) * x + 10) * x * x * x;
    }

    float Lerp(float x, float a1, float a2){
        return a1 + x * (a2 - a1);
    }

#define WRAP 512

    std::vector<std::vector<float>> GeneratePerlinNoise(unsigned int size, unsigned int seed, unsigned int density){
        // based on algorithm provided here: https://rtouti.github.io/graphics/perlin-noise-algorithm

        std::random_device rd;
        std::mt19937 gen(rd());
        if(seed == 0)
            seed = gen();
        gen.seed(seed);

        if(density == 0) density = 1;

        std::array<unsigned int, WRAP + 1> permutations{};
        for(unsigned int i = 0; i < WRAP; i++)
            permutations[i] = i;
        std::shuffle(std::begin(permutations), std::end(permutations), gen);
        permutations[WRAP] = permutations[0];

        std::vector<std::vector<float>> noise(size);
        for(unsigned int i = 0; i < size; i++)
            noise.emplace_back(size);

        for(unsigned int i = 0; i < size; i++){
            for(unsigned int j = 0; j < size; j++){
                const Vector2 coords = {i / static_cast<float>(density), j / static_cast<float>(density)};
                const unsigned int x = (i / density) % WRAP;
                const unsigned int y = (j / density) % WRAP;
                const float xf = coords.x - floor(coords.x);
                const float yf = coords.y - floor(coords.y);

                const Vector2 topRight = {xf - 1, yf -1};
                const Vector2 topLeft = {xf, yf - 1};
                const Vector2 bottomRight = {xf - 1, yf};
                const Vector2 bottomLeft = {xf, yf};

                const float dotTopRight = dotProduct(topRight, constantVector(permutations[(permutations[x + 1] + y + 1) % WRAP]));
                const float dotTopLeft = dotProduct(topLeft, constantVector(permutations[(permutations[x] + y + 1) % WRAP]));
                const float dotBottomRight = dotProduct(bottomRight, constantVector(permutations[(permutations[x + 1] + y) % WRAP]));
                const float dotBottomLeft = dotProduct(bottomLeft, constantVector(permutations[(permutations[x] + y) % WRAP]));

                const float u = Fade(xf);
                const float v = Fade(yf);

                noise[i].emplace_back(Lerp(u,
                                   Lerp(v, dotBottomLeft, dotTopLeft),
                                   Lerp(v, dotBottomRight, dotTopRight)));
            }
        }

        return std::move(noise);
    }

    std::vector<std::vector<float>> GenerateFractalBrownianMotion(unsigned int size, unsigned int seed, unsigned int density, unsigned int octaves, float amplitudeScaling, float frequencyScaling) {
        std::random_device rd;
        std::mt19937 gen(rd());
        if(seed == 0)
            seed = gen();
        gen.seed(seed);

        std::vector<std::vector<float>> noise(size, std::vector<float>(size));
        std::vector<std::vector<float>> perlinNoise;

        float amplitude = 1;
        float frequency = 1.0/density;

        for(unsigned int octave = 0; octave < octaves; octave++){
            perlinNoise = GeneratePerlinNoise(size, seed, 1.0/frequency);

            for(unsigned int i = 0; i < size; i++){
                for(unsigned int j = 0; j < size; j++) {
                    noise[i][j] += amplitude * perlinNoise[i][j];
                }
            }

            amplitude *= amplitudeScaling;
            frequency *= frequencyScaling;
        }

        return noise;
    }
} // Gmlib