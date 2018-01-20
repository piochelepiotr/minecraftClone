#ifndef MATHS_H
#define MATHS_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/camera.h"
class Maths
{
    public:
        static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);
        static glm::mat4 createTransformationMatrix(glm::vec2 translation, glm::vec2 const& scale);
        static glm::mat4 createViewMatrix(Camera const& camera);
};

#endif
