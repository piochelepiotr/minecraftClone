#ifndef STATIC_SHADER_H
#define STATIC_SHADER_H

#include "shaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "entities/camera.h"
#include "entities/light.h"

class StaticShader : public ShaderProgram
{
    public:
        StaticShader();
        void loadTransformationMatrix(glm::mat4 & transformationMatrix);
        void loadProjectionMatrix(glm::mat4 & projectionMatrix);
        void loadViewMatrix(Camera const& camera);
        void loadLight(Light const& light);
        void loadShineVariables(float shineDamper, float reflectivity);
        void loadSkyColour(glm::vec3 const& skyColour);
        void loadTextureOffset(float xOffset, float yOffset);
        void loadNumberOfRows(int numberOfRows);
    protected:
        void bindAttributes();
        virtual void getAllUniformLocations();
    private:
        int m_location_transforamtionMatrix;
        int m_location_projectionMatrix;
        int m_location_viewMatrix;
        int m_location_lightPosition;
        int m_location_lightColour;
        int m_location_shineDamper;
        int m_location_reflectivity;
        int m_location_skyColour;
        int m_location_textureOffset;
        int m_location_numberOfRows;
        static const std::string VERTEX_FILE;
        static const std::string  FRAGMENT_FILE;
};

#endif
