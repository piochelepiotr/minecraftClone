#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/player.h"

class Camera
{
public:
    Camera(glm::vec3 const& position = glm::vec3(0,0,0));
    glm::vec3 position() const;
    float pitch() const;
    float yaw() const;
    float roll() const;
    void  lockOnPlayer(Player *player);

private:
    glm::vec3 m_position;
    float m_pitch;
    float m_yaw;
    float m_roll;
    float m_followDistance;
    float m_cameraHeight;
};

#endif // CAMERA_H
