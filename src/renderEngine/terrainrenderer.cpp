#include "terrainrenderer.h"
#include "toolbox/maths.h"
#include <iostream>

TerrainRenderer::TerrainRenderer(TerrainShader *shader, glm::mat4 const& projectionMatrix) :
    m_shader(shader),
    m_projectionMatrix(projectionMatrix)
{

}

TerrainRenderer::~TerrainRenderer()
{

}

void TerrainRenderer::prepareTerrain(Terrain *terrain)
{
    RawModel *model = terrain->model();
    ModelTexture *texture = terrain->texture();
    glBindVertexArray(model->getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    m_shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture->getTextID());
}

void TerrainRenderer::unbindTerrain()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void TerrainRenderer::loadMatrices(Terrain *terrain)
{
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(glm::vec3(terrain->x(), 0, terrain->z()), 0, 0, 0, 1);
    m_shader->loadProjectionMatrix(m_projectionMatrix);
    m_shader->loadTransformationMatrix(transformationMatrix);
}

void TerrainRenderer::render(std::vector<Terrain*> const& terrains)
{
    for(auto & terrain : terrains)
    {
        prepareTerrain(terrain);
        loadMatrices(terrain);
        glDrawElements(GL_TRIANGLES, terrain->model()->getVertexCount(), GL_UNSIGNED_INT, 0);
        unbindTerrain();
    }
}
