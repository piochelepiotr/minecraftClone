#include "shaderProgram.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>

ShaderProgram::ShaderProgram(std::string const& vertexFile, std::string const& fragmentFile)
{
    m_vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
    m_fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
}

void ShaderProgram::start()
{
    glUseProgram(m_programID);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

ShaderProgram::~ShaderProgram()
{
    stop();
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
    glDeleteProgram(m_programID);
}

void ShaderProgram::bindAttribute(int attribute, std::string const& name)
{
    glBindAttribLocation(m_programID, attribute, name.c_str());
}

int ShaderProgram::loadShader(std::string file, int type)
{
    // Création du shader
    int shaderID = glCreateShader(type);
    // Vérification du shader
    if(shaderID == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return 0;
    }

    // Flux de lecture
    std::ifstream fichier(file.c_str());

    // Test d'ouverture
    if(!fichier)
    {
        std::cout << "Erreur le fichier " << file << " est introuvable" << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }

    // Strings permettant de lire le code source
    std::string ligne;
    std::string codeSource;

    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';

    // Fermeture du fichier
    fichier.close();

    // Récupération de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource.c_str();


    // Envoi du code source au shader
    glShaderSource(shaderID, 1, &chaineCodeSource, 0);
    // Compilation du shader
    glCompileShader(shaderID);
    // Vérification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur
    if(erreurCompilation != GL_TRUE)
    {
        // Récupération de la taille de l'erreur
        GLint tailleErreur(0);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &tailleErreur);

        // Allocation de mémoire
        char *erreur = new char[tailleErreur + 1];
        // Récupération de l'erreur
        glGetShaderInfoLog(shaderID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';
        // Affichage de l'erreur
        std::cout << erreur << std::endl;
        // Libération de la mémoire et retour du booléen false
        delete[] erreur;
        glDeleteShader(shaderID);
        return 0;
    }
    // Sinon c'est que tout s'est bien passé
    else
        return shaderID;
}

int ShaderProgram::getUniformLocation(std::string const& uniformName)
{
    return glGetUniformLocation(m_programID, uniformName.c_str());
}

void ShaderProgram::loadFloat(int location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadBool(int location, bool value)
{
    float toLoad = value ? 1 : 0;
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadVector(int location, glm::vec3 const& vector)
{
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadVector2(int location, glm::vec2 const& vector)
{
    glUniform2f(location, vector.x, vector.y);
}

void ShaderProgram::loadMatrix(int location, const glm::mat4 &matrix)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
}
