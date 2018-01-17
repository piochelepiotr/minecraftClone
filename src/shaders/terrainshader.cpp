#include "terrainshader.h"
#include <iostream>
#include <GL/glew.h>
#include "toolbox/maths.h"

const std::string TerrainShader::VERTEX_FILE = "shaders/shaderTerrain.vert";
const std::string TerrainShader::FRAGMENT_FILE = "shaders/shaderTerrain.frag";

TerrainShader::TerrainShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    bindAttributes();
    glLinkProgram(m_programID);
    glValidateProgram(m_programID);
    getAllUniformLocations();
}

void TerrainShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void TerrainShader::getAllUniformLocations()
{
    m_location_transforamtionMatrix = getUniformLocation("transformationMatrix");
    m_location_projectionMatrix = getUniformLocation("projectionMatrix");
    m_location_viewMatrix = getUniformLocation("viewMatrix");
    m_location_lightPosition = getUniformLocation("lightPosition");
    m_location_lightColour = getUniformLocation("lightColour");
    m_location_shineDamper = getUniformLocation("shineDamper");
    m_location_reflectivity = getUniformLocation("shineReflectivity");
    m_location_skyColour = getUniformLocation("skyColour");
}

void TerrainShader::loadTransformationMatrix(glm::mat4 & transformationMatrix)
{
    loadMatrix(m_location_transforamtionMatrix, transformationMatrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4 & projectionMatrix)
{
    loadMatrix(m_location_projectionMatrix, projectionMatrix);
}


void TerrainShader::loadViewMatrix(Camera const& camera)
{
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    loadMatrix(m_location_viewMatrix, viewMatrix);
}

void TerrainShader::loadLight(Light const& light)
{
    glm::vec3 pos = light.position();
    glm::vec3 colour = light.colour();
    loadVector(m_location_lightPosition, pos);
    loadVector(m_location_lightColour, colour);
}

void TerrainShader::loadShineVariables(float shineDamper, float reflectivity)
{
    loadFloat(m_location_shineDamper, shineDamper);
    loadFloat(m_location_reflectivity, reflectivity);
}

void TerrainShader::loadSkyColour(glm::vec3 const& skyColour)
{
    loadVector(m_location_skyColour, skyColour);
}
