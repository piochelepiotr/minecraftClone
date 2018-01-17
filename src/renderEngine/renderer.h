#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "models/texturedModel.h"
#include "entities/Entity.h"
#include "shaders/staticShader.h"
#include "entities/camera.h"
#include <map>
#include <vector>

class EntityRenderer
{
    public:
        EntityRenderer(StaticShader *shader, glm::mat4 const& projectionMatrix);
        ~EntityRenderer();
        void render(std::map<TexturedModel*, std::vector<Entity*>> const& entities);
    private:
        void prepareTexturedModel(TexturedModel *texturedModel);
        void unbindTexturedModel();
        void prepareEntity(Entity *entity);
        StaticShader *m_shader;
        glm::mat4 m_projectionMatrix;
};

#endif
