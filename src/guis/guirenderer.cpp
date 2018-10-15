#include "guirenderer.h"
#include "toolbox/maths.h"
#include <iostream>

GuiRenderer::GuiRenderer(Loader *loader)
{
    float positions[] = {-1, 1, -1, -1, 1, 1, 1, -1};
    m_model = loader->loadToVao(positions, 8);
    m_shader = new GuiShader();
}

void GuiRenderer::render(std::vector<GuiTexture *> const &guis)
{
    m_shader->start();
    glBindVertexArray(m_model->getVaoID());
    glEnableVertexAttribArray(0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    //rendering
    for (auto &gui : guis)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gui->id());
        glm::mat4 transMat = Maths::createTransformationMatrix(gui->position(), gui->scale());
        m_shader->loadTransformationMatrix(transMat);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, m_model->getVertexCount());
    }
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
    m_shader->stop();
}

GuiRenderer::~GuiRenderer()
{
    delete m_model;
    delete m_shader;
}
