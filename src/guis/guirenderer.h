#ifndef GUIRENDERER_H
#define GUIRENDERER_H

#include "renderEngine/loader.h"
#include <vector>
#include "guis/guitexture.h"
#include "shaders/guishader.h"

class GuiRenderer
{
public:
    GuiRenderer(Loader *loader);
    ~GuiRenderer();
    void render(std::vector<GuiTexture *> const& guis);
private:
    RawModel *m_model;
    GuiShader *m_shader;
};

#endif // GUIRENDERER_H
