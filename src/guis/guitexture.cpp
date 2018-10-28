#include "guitexture.h"

GuiTexture::GuiTexture(GLuint id, const glm::vec2 &scale, const glm::vec2 &position) :
    m_id(id),
    m_scale(scale),
    m_position(position)
{
}

GLuint GuiTexture::id() const
{
    return m_id;
}

glm::vec2 GuiTexture::scale() const
{
    return m_scale;
}

glm::vec2 GuiTexture::position() const
{
    return m_position;
}
