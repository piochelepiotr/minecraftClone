#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#include <GL/glew.h>

class ModelTexture
{
    public:
        ModelTexture(GLuint textID);
        GLuint getTextID() const { return m_textID; }
    private:
        GLuint m_textID;
};

#endif
