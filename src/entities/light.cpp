#include "light.h"

Light::Light(const glm::vec3 &position, const glm::vec3 &colour) :
    m_position(position),
    m_colour(colour)
{

}

glm::vec3 Light::position() const
{
    return m_position;
}

void Light::setPosition(const glm::vec3 &position)
{
    m_position = position;
}

glm::vec3 Light::colour() const
{
    return m_colour;
}

void Light::setColour(const glm::vec3 &colour)
{
    m_colour = colour;
}
