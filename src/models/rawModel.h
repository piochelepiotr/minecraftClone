#ifndef RAW_MODEL_H
#define RAW_MODEL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class RawModel
{
    public:
        RawModel(GLuint vaoID, int vertexCount);
        GLuint getVaoID() const { return m_vaoID; }
        int getVertexCount() const { return m_vertexCount; }

    private:
        GLuint m_vaoID;
        int m_vertexCount;
};

#endif
