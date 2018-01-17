#ifndef TEXTURED_MODEL_H
#define TEXTURED_MODEL_H

#include "rawModel.h"
#include "textures/modelTexture.h"

class TexturedModel
{
    public:
        TexturedModel(RawModel *model, ModelTexture *texure);
        ModelTexture *getTexture() const { return m_texture; }
        RawModel *getModel() const { return m_model; }

private:
        RawModel *m_model;
        ModelTexture *m_texture;
};

#endif
