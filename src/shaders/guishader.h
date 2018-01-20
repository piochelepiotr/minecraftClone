#ifndef GUISHADER_H
#define GUISHADER_H

#include "shaders/shaderProgram.h"

class GuiShader : public ShaderProgram
{
public:
    GuiShader();
    void loadTransformationMatrix(glm::mat4 & transformationMatrix);
protected:
    void bindAttributes();
    virtual void getAllUniformLocations();
private:
    int m_location_transforamtionMatrix;
    static const std::string VERTEX_FILE;
    static const std::string FRAGMENT_FILE;
};

#endif // GUISHADER_H
