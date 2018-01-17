#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include "shaders/shaderProgram.h"
#include "entities/camera.h"
#include "entities/light.h"

class TerrainShader : public ShaderProgram
{
    public:
        TerrainShader();
        void loadTransformationMatrix(glm::mat4 & transformationMatrix);
        void loadProjectionMatrix(glm::mat4 & projectionMatrix);
        void loadViewMatrix(Camera const& camera);
        void loadLight(Light const& light);
        void loadShineVariables(float shineDamper, float reflectivity);
        void loadSkyColour(glm::vec3 const& skyColour);
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
        static const std::string VERTEX_FILE;
        static const std::string  FRAGMENT_FILE;
};

#endif // TERRAINSHADER_H
