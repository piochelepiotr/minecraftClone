#include "camera.h"
#include "SFML/Window.hpp"

Camera::Camera(const glm::vec3 &position) :
    m_position(position),
    m_pitch(0.0),
    m_yaw(0),
    m_roll(0),
    m_followDistance(-1),
    m_cameraHeight(2)
{

}

glm::vec3 Camera::position() const
{
    return m_position;
}

float Camera::pitch() const
{
    return m_pitch;
}

float Camera::yaw() const
{
    return m_yaw;
}

float Camera::roll() const
{
    return m_roll;
}

void Camera::lockOnPlayer(Player *player)
{
    glm::mat4 mat(1.0);
    mat = glm::rotate   (mat, player->getrotY(), glm::vec3(0, 1, 0));
    glm::vec3 forward(0, 0, m_followDistance);
    glm::vec3 movement = mat * glm::vec4(forward, 1);
    m_position.x = player->getposition().x + movement.x;
    m_position.y = player->getposition().y + m_cameraHeight;
    m_position.z = player->getposition().z + movement.z;
    m_yaw = -player->getrotY();
}

void Camera::setPitch(float pitch)
{
    m_pitch = pitch;
}

