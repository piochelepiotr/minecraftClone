#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include "glm/glm.hpp"
#include "toolbox/hash.h"

class PerlinNoise
{
public:
    PerlinNoise();
    static float noise(float x, float y);
private:
    static Hash m_hash;
    static float fade(float x);
    static float lerp(float t, float a, float b);
};

#endif // PERLINNOISE_H
