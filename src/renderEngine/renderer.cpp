#include "renderer.h"
#include "toolbox/maths.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::prepare()
{
    static const float black[] = { 1.0f, 1.0f, 0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(Entity *entity, StaticShader & shader)
{
    TexturedModel *texturedModel = entity->getmodel();
    RawModel *model = texturedModel->getModel();
    glBindVertexArray(model->getVaoID());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getposition(),
    entity->getrotX(),
    entity->getrotY(),
    entity->getrotZ(),
    entity->getscale());
    shader.loadTransformationMatrix(transformationMatrix);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel->getTexture()->getTextID());
    //glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());
    glDrawElements(GL_TRIANGLES, model->getVertexCount(), GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
}

