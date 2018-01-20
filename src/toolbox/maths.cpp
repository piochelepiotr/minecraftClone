#include "maths.h"
#include <iostream>

glm::mat4 Maths::createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale)
{
    //std::cout << "translation : " << translation.x << " " << translation.y << " " << translation.z << std::endl;
    glm::mat4 mat(1.0);
    mat = glm::translate(mat, translation);
    mat = glm::rotate   (mat, rx, glm::vec3(1, 0, 0));
    mat = glm::rotate   (mat, ry, glm::vec3(0, 1, 0));
    mat = glm::rotate   (mat, rz, glm::vec3(0, 0, 1));
    mat = glm::scale    (mat, glm::vec3(scale, scale, scale));
    return mat;
}

glm::mat4 Maths::createTransformationMatrix(glm::vec2 translation, glm::vec2 const& scale)
{
    glm::mat4 mat(1.0);
    mat = glm::translate(mat, glm::vec3(translation.x, translation.y, 0));
    mat = glm::scale    (mat, glm::vec3(scale.x, scale.y, 1));
    return mat;
}

glm::mat4 Maths::createViewMatrix(Camera const& camera)
{
    glm::mat4 mat(1.0);
    mat = glm::rotate   (mat, camera.pitch(), glm::vec3(1, 0, 0));
    mat = glm::rotate   (mat, camera.yaw(), glm::vec3(0, 1, 0));
    mat = glm::rotate   (mat, camera.roll(), glm::vec3(0, 0, 1));
    mat = glm::translate(mat, -camera.position());
    return mat;
}
