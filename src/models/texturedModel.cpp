#include "texturedModel.h"

TexturedModel::TexturedModel(RawModel *model, ModelTexture *texture) :
    m_model(model),
    m_texture(texture)
{
}

void TexturedModel::setModel(RawModel *model)
{
    m_model = model;
}
