#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "models/texturedModel.h"
#include "entities/Entity.h"
#include "shaders/staticShader.h"

class Renderer
{
    public:
        Renderer();
        ~Renderer();
        void prepare();
        void render(Entity *entity, StaticShader & shader);
    private:
};

#endif
