#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "shaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class StaticShader : public ShaderProgram
{
    public:
        StaticShader();
        void loadTransformationMatrix(glm::mat4 & transformationMatrix);
    protected:
        void bindAttributes();
        virtual void getAllUniformLocations();
    private:
        int m_location_transforamtionMatrix;
        static const std::string VERTEX_FILE;
        static const std::string  FRAGMENT_FILE;
};

#endif
