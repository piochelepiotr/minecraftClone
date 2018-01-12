#include "staticShader.h"
#include <iostream>
#include <GL/glew.h>

const std::string StaticShader::VERTEX_FILE = "shaders/shader2D.vert";
const std::string StaticShader::FRAGMENT_FILE = "shaders/shader2D.frag";

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
}

void StaticShader::getAllUniformLocations()
{
    m_location_transforamtionMatrix = getUniformLocation("transformationMatrix");
}

void StaticShader::loadTransformationMatrix(glm::mat4 & transformationMatrix)
{
    loadMatrix(m_location_transforamtionMatrix, transformationMatrix);
}
