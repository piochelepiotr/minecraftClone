#include "Entity.h"
#include "SFML/Window.hpp"

Entity::Entity(glm::vec3 position, TexturedModel *model, float rotX, float rotY, float rotZ, float scale, int textureIndex) :
    m_position(position),
    m_model(model),
    m_rotX(rotX),
    m_rotY(rotY),
    m_rotZ(rotZ),
    m_scale(scale),
    m_textureIndex(textureIndex)
{

}

Entity::Entity() :
    m_position(glm::vec3(0,0,0)),
    m_rotX(0),
    m_rotY(0),
    m_rotZ(0),
    m_scale(1),
    m_textureIndex(0)
{

}

Entity::~Entity()
{

}

void Entity::increasePosition(float dx, float dy, float dz)
{
    m_position.x += dx;
    m_position.y += dy;
    m_position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz)
{
    m_rotX += dx;
    m_rotY += dy;
    m_rotZ += dz;
}

void Entity::move()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        m_position.z -= 0.05;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_position.z += 0.05;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_position.x += 0.05;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        m_position.x -= 0.05;
    }
}

int Entity::getTextureIndex() const
{
    return m_textureIndex;
}

void Entity::setTextureIndex(int textureIndex)
{
    m_textureIndex = textureIndex;
}

float Entity::getTextureXOffset()
{
    int column = m_textureIndex % m_model->getTexture()->getNumberRows();
    return (float) column / (float) m_model->getTexture()->getNumberRows();
}

float Entity::getTextureYOffset()
{
    int row = m_textureIndex / m_model->getTexture()->getNumberRows();
    return (float) row / (float) m_model->getTexture()->getNumberRows();
}
