#ifndef MATHS_H
#define MATHS_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Maths
{
    public:
        static glm::mat4 createTransformationMatrix(glm::vec3 translation, float rx, float ry, float rz, float scale);
};

#endif
