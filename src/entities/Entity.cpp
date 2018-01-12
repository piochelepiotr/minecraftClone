#include "Entity.h"

Entity::Entity(glm::vec3 position, TexturedModel *model, float rotX, float rotY, float rotZ, float scale) :
m_position(position),
m_model(model),
m_rotX(rotX),
m_rotY(rotY),
m_rotZ(rotZ),
m_scale(scale)
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
