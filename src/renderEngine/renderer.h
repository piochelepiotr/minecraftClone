#pragma once

#include "models/texturedModel.h"
#include "shaders/staticShader.h"
#include "entities/Entity.h"
#include <map>
#include "entities/camera.h"
#include <GL/glew.h>
#include <vector>

class EntityRenderer
{
    public:
        EntityRenderer(StaticShader *shader, glm::mat4 const& projectionMatrix);
        ~EntityRenderer();
        void render(std::map<TexturedModel*, std::vector<Entity*> > const& entities);
    private:
        void prepareTexturedModel(TexturedModel *texturedModel);
        void unbindTexturedModel();
        void prepareEntity(Entity *entity);
        StaticShader *m_shader;
        glm::mat4 m_projectionMatrix;
};

