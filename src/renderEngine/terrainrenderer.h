#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "shaders/terrainshader.h"
#include "glm/glm.hpp"
#include "terrain/terrain.h"
#include <vector>

class TerrainRenderer
{
    public:
        TerrainRenderer(TerrainShader *shader, glm::mat4 const& projectionMatrix);
        ~TerrainRenderer();
        void render(std::vector<Terrain*> const& terrains);
    private:
        void prepareTerrain(Terrain *terrain);
        void unbindTerrain();
        void loadMatrices(Terrain *terrain);
        TerrainShader *m_shader;
        glm::mat4 m_projectionMatrix;
};

#endif // TERRAINRENDERER_H
