#ifndef MOUSEPICKER_H
#define MOUSEPICKER_H

#include <glm/glm.hpp>
#include "entities/camera.h"
#include "world/world.h"
#define MAX_DISTANCE_BLOCK 30

class MousePicker
{
public:
    MousePicker(Camera *camera, World *world, glm::mat4 const& projectionMatrix, double windowX, double windowY);
    glm::vec3 currentRay() const;
    void update();
    void updateWindowSize(double windowX, double windowY);
    bool getAimedBlock(int & x, int & y, int & z);
    double placeInFront(double x_s, double y_s, double z_s, glm::vec3 const& dir);

private:
    double getNextBlock(double & x_i, double & y_i, double & z_i, glm::vec3 const& dir,
                  int & x, int & y, int & z);
    glm::vec4 toEyeCoord(glm::vec4 const& clipCoord);
    void createViewMatrix();
    void computeMouseRay();
    glm::vec2 getNormalizedCoord(double x, double y);
    glm::vec3 toWorldCoord(glm::vec4 const& eyeCoord);
    glm::vec3 m_currentRay;
    glm::mat4 m_invertProjectionMatrix;
    glm::mat4 m_viewMatrix;
    Camera *m_camera;
    World *m_world;
    glm::mat4 m_projectionMatrix;
    double m_windowX;
    double m_windowY;
};

#endif // MOUSEPICKER_H
