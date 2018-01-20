#ifndef GUITEXTURE_H
#define GUITEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class GuiTexture
{
public:
    GuiTexture(GLuint id, glm::vec2 const& scale, glm::vec2 const& position);
    GLuint id() const;
    glm::vec2 scale() const;
    glm::vec2 position() const;

private:
    GLuint m_id;
    glm::vec2 m_scale;
    glm::vec2 m_position;
};

#endif // GUITEXTURE_H
