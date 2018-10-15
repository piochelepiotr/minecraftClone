#include "loader.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Loader::Loader()
{
}

RawModel *Loader::loadToVao(float *positions, int size_position, float *textCoor, int sizeTextCoor, int *indices, int size_indices, float *normals, int size_normals)
{
    GLuint vaoID = createVao();
    bindIndicesBuffer(indices, size_indices);
    storeDataInAttributeList(0, 3, positions, size_position);
    storeDataInAttributeList(1, 2, textCoor, sizeTextCoor);
    storeDataInAttributeList(2, 3, normals, size_normals);
    unbindVao();
    return new RawModel(vaoID, size_indices);
}

RawModel *Loader::loadToVao(float *positions, int size_position)
{
    GLuint vaoID = createVao();
    storeDataInAttributeList(0, 2, positions, size_position);
    unbindVao();
    return new RawModel(vaoID, size_position / 2);
}

GLuint Loader::loadTexture(std::string const &fileName)
{
    GLuint id;
    sf::Image img_data;
    if (!img_data.loadFromFile(fileName.c_str()))
    {
        std::cout << "Could not load " << fileName.c_str() << std::endl;
        return 0;
    }
    //img_data.flipHorizontally();
    //img_data.flipVertically();

    glGenTextures(1, &id);
    m_textIDs.push_back(id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    //glGenerateMipmap(GL_TEXTURE_2D);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    return id;
}

GLuint Loader::createVao()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    m_vaoIDs.push_back(vaoID);
    glBindVertexArray(vaoID);
    return vaoID;
}

void Loader::bindIndicesBuffer(int *indices, int size)
{
    GLuint vboID;
    // glCreateBuffers(1, &vboID);
    glGenBuffers(1, &vboID);
    m_vboIDs.push_back(vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * size, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(int) * size, indices);
}

void Loader::storeDataInAttributeList(int attribute, int coordSize, float *data, int size)
{
    GLuint vboID;
    // glCreateBuffers(1, &vboID);
    glGenBuffers(1, &vboID);
    m_vboIDs.push_back(vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * size, data);
    glVertexAttribPointer(attribute, coordSize, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::unbindVao()
{
    glBindVertexArray(0);
}

Loader::~Loader()
{
    for (auto vaoID : m_vaoIDs)
    {
        glDeleteVertexArrays(1, &vaoID);
    }
    for (auto vboID : m_vboIDs)
    {
        glDeleteBuffers(1, &vboID);
    }
    for (auto textID : m_textIDs)
    {
        glDeleteTextures(1, &textID);
    }
}
