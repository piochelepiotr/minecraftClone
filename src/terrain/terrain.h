#ifndef TERRAIN_H
#define TERRAIN_H

#include "models/rawModel.h"
#include "textures/modelTexture.h"
#include "renderEngine/loader.h"

class Terrain
{
public:
    Terrain(float grid_x, float grid_z, ModelTexture *texture, Loader *loader);
    float x() const;
    float z() const;
    RawModel *model() const;
    ModelTexture *texture() const;

private:
    RawModel *generateTerrain(Loader *loader);
    static const float SIZE;
    static const int VERTEX_COUNT;
    float m_x;
    float m_z;
    RawModel *m_model;
    ModelTexture *m_texture;
};

#endif // TERRAIN_H
