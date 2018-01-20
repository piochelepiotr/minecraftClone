#include "guishader.h"
#include <GL/glew.h>

const std::string GuiShader::VERTEX_FILE = "shaders/shaderGui.vert";
const std::string GuiShader::FRAGMENT_FILE = "shaders/shaderGui.frag";

GuiShader::GuiShader() : ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
    bindAttributes();
    glLinkProgram(m_programID);
    glValidateProgram(m_programID);
    getAllUniformLocations();
}

void GuiShader::bindAttributes()
{
    bindAttribute(0, "position");
}

void GuiShader::getAllUniformLocations()
{
    m_location_transforamtionMatrix = getUniformLocation("transformationMatrix");
}

void GuiShader::loadTransformationMatrix(glm::mat4 & transformationMatrix)
{
    loadMatrix(m_location_transforamtionMatrix, transformationMatrix);
}
