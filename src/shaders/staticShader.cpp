#include "staticShader.h"
#include <iostream>
#include <GL/glew.h>
#include "toolbox/maths.h"

const std::string StaticShader::VERTEX_FILE = "shaders/shaderEntity.vert";
const std::string StaticShader::FRAGMENT_FILE = "shaders/shaderEntity.frag";

StaticShader::StaticShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    bindAttributes();
    glLinkProgram(m_programID);
    glValidateProgram(m_programID);
    getAllUniformLocations();
}

void StaticShader::bindAttributes()
{
    bindAttribute(0, "position");
    bindAttribute(1, "textureCoords");
    bindAttribute(2, "normal");
}

void StaticShader::getAllUniformLocations()
{
    m_location_transforamtionMatrix = getUniformLocation("transformationMatrix");
    m_location_projectionMatrix = getUniformLocation("projectionMatrix");
    m_location_viewMatrix = getUniformLocation("viewMatrix");
    m_location_lightPosition = getUniformLocation("lightPosition");
    m_location_lightColour = getUniformLocation("lightColour");
    m_location_shineDamper = getUniformLocation("shineDamper");
    m_location_reflectivity = getUniformLocation("shineReflectivity");
    m_location_skyColour = getUniformLocation("skyColour");
    m_location_numberOfRows = getUniformLocation("numberOfRows");
    m_location_textureOffset = getUniformLocation("textureOffset");
}

void StaticShader::loadTransformationMatrix(glm::mat4 & transformationMatrix)
{
    loadMatrix(m_location_transforamtionMatrix, transformationMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 & projectionMatrix)
{
    loadMatrix(m_location_projectionMatrix, projectionMatrix);
}


void StaticShader::loadViewMatrix(Camera const& camera)
{
    glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
    loadMatrix(m_location_viewMatrix, viewMatrix);
}

void StaticShader::loadLight(Light const& light)
{
    glm::vec3 pos = light.position();
    glm::vec3 colour = light.colour();
    loadVector(m_location_lightPosition, pos);
    loadVector(m_location_lightColour, colour);
}

void StaticShader::loadShineVariables(float shineDamper, float reflectivity)
{
    loadFloat(m_location_shineDamper, shineDamper);
    loadFloat(m_location_reflectivity, reflectivity);
}

void StaticShader::loadSkyColour(glm::vec3 const& skyColour)
{
    loadVector(m_location_skyColour, skyColour);
}

void StaticShader::loadTextureOffset(float xOffset, float yOffset)
{
    loadVector2(m_location_textureOffset, glm::vec2(xOffset, yOffset));
}

void StaticShader::loadNumberOfRows(int numberOfRows)
{
    loadFloat(m_location_numberOfRows, (float) numberOfRows);
}
