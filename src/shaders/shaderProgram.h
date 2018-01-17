#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
    public:
        ShaderProgram(std::string const& vertexFile, std::string const& fragmentFile);
        virtual ~ShaderProgram();
        void start();
        void stop();
        void bindAttribute(int attribute, std::string const& name);
    
    protected:
        void loadFloat(int location, float value);
        void loadVector(int location, const glm::vec3 &vector);
        void loadVector2(int location, const glm::vec2 &vector);
        void loadMatrix(int location, glm::mat4 const& matrix);
        void loadBool(int location, bool value);
        virtual void getAllUniformLocations() = 0;
        int getUniformLocation(std::string const& uniformName);
        virtual void bindAttributes() = 0;
        static int loadShader(std::string file, int type);
        int m_programID;
        int m_vertexShaderID;
        int m_fragmentShaderID;
};

#endif
