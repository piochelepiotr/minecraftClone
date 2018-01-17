#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
public:
    Light(glm::vec3  const& position, glm::vec3 const& colour);
    glm::vec3 position() const;
    void setPosition(const glm::vec3 &position);
    glm::vec3 colour() const;
    void setColour(const glm::vec3 &colour);

private:
    glm::vec3 m_position;
    glm::vec3 m_colour;
};

#endif // LIGHT_H
