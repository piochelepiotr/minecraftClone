#ifndef LOADER_H
#define LOADER_H

#include "models/rawModel.h"
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

class Loader
{
    public:
        Loader();
        ~Loader();
        RawModel *loadToVao(float *positions, int size_position, float *textCoor, int sizeTextCoor,
                            int *indices, int size_indices, float *normals, int size_normals);
        GLuint loadTexture(std::string const& fileName);
    private:
        GLuint createVao();
        void storeDataInAttributeList(int attribute,int coordSize, float *data, int size);
        void bindIndicesBuffer(int *indices, int size);
        void unbindVao();
        std::vector<GLuint> m_vaoIDs;
        std::vector<GLuint> m_vboIDs;
        std::vector<GLuint> m_textIDs;
};

#endif
