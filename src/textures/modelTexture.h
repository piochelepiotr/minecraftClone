#ifndef MODEL_TEXTURE_H
#define MODEL_TEXTURE_H

#include <GL/glew.h>

class ModelTexture
{
    public:
        ModelTexture(GLuint textID, int numberRows);
        ModelTexture(GLuint textID);
        GLuint getTextID() const { return m_textID; }
        float getShineDamper() const;
        void setShineDamper(float shineDamper);
        float getReflectivity() const;
        void setReflectivity(float reflectivity);

        int getNumberRows() const;
        void setNumberRows(int numberRows);

private:
        GLuint m_textID;
        float m_shineDamper;
        float m_reflectivity;
        int m_numberRows;
};

#endif
