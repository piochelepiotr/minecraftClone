#include "perlinnoise.h"
#include <math.h>
#include <iostream>

using namespace glm;

Hash PerlinNoise::m_hash = Hash(54);

PerlinNoise::PerlinNoise()
{

}

float PerlinNoise::fade(float x)
{
    return 6*std::pow(x, 5) -15*std::pow(x, 4) + 10*std::pow(x, 3);
}

float PerlinNoise::lerp(float t, float a, float b)
{
    return (1-t)*a + t*b;
}

float PerlinNoise::noise(float x, float y)
{
    int X = int(x);
    int Y = int(y);
    x = x - X;
    y = y - Y;
    x = fade(x);
    y = fade(y);
    vec2 gaa = m_hash.hashToVec(m_hash.hash(X,Y));
    vec2 gab = m_hash.hashToVec(m_hash.hash(X,Y+1));
    vec2 gba = m_hash.hashToVec(m_hash.hash(X+1,Y));
    vec2 gbb = m_hash.hashToVec(m_hash.hash(X+1,Y+1));
    vec2 paa(0,0);
    vec2 pab(0,1);
    vec2 pba(1,0);
    vec2 pbb(1,1);
    vec2 p(x,y);
    vec2 daa = p - paa;
    vec2 dab = p - pab;
    vec2 dba = p - pba;
    vec2 dbb = p - pbb;
    double maa = dot(daa, gaa);
    double mab = dot(dab, gab);
    double mba = dot(dba, gba);
    double mbb = dot(dbb, gbb);
    double v1 = lerp(x, maa, mba);
    double v2 = lerp(x, mab, mbb);
    double av = lerp(y, v1, v2) / 2 + 0.5;
    return av;
}
