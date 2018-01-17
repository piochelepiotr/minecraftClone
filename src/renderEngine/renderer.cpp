#include "renderer.h"
#include "toolbox/maths.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

EntityRenderer::EntityRenderer(StaticShader *shader, glm::mat4 const& projectionMatrix) :
    m_shader(shader),
    m_projectionMatrix(projectionMatrix)
{
}

EntityRenderer::~EntityRenderer()
{

}


void EntityRenderer::prepareTexturedModel(TexturedModel *texturedModel)
{
    RawModel *model = texturedModel->getModel();
    ModelTexture *texture = texturedModel->getTexture();
    glBindVertexArray(model->getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    m_shader->loadShineVariables(texture->getShineDamper(), texture->getReflectivity());
    m_shader->loadNumberOfRows(texturedModel->getTexture()->getNumberRows());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getTextID());
}

void EntityRenderer::unbindTexturedModel()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void EntityRenderer::prepareEntity(Entity *entity)
{
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getposition(),
    entity->getrotX(),
    entity->getrotY(),
    entity->getrotZ(),
    entity->getscale());
    m_shader->loadProjectionMatrix(m_projectionMatrix);
    m_shader->loadTransformationMatrix(transformationMatrix);
    m_shader->loadTextureOffset(entity->getTextureXOffset(), entity->getTextureYOffset());
}

void EntityRenderer::render(std::map<TexturedModel*, std::vector<Entity*>> const& entities)
{
    for(auto & v : entities)
    {
        prepareTexturedModel(v.first);
        for(auto & entity : v.second)
        {
            prepareEntity(entity);
            glDrawElements(GL_TRIANGLES, v.first->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
        }
        unbindTexturedModel();
    }
}

