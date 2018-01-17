#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "shaders/staticShader.h"
#include "renderEngine/renderer.h"
#include "renderEngine/terrainrenderer.h"
#include "shaders/terrainshader.h"
#include "entities/Entity.h"
#include "entities/camera.h"
#include "entities/light.h"
#include <map>
#include <vector>

class MasterRenderer
{
public:
    MasterRenderer(int width, int height);
    ~MasterRenderer();
    void render(Light const& sun, Camera const& camera);
    void processEntity(Entity *entity);
    void processEntities(std::vector<Entity *> const& entities);
    void processTerrain(Terrain *terrain);
    void prepare();
private:
    void createProjectionMatrix();
    int m_width;
    int m_height;
    static const float m_fov;
    static const float m_farPlane;
    static const float m_nearPlane;
    static const glm::vec3 m_skyColour;
    glm::mat4 m_projectionMatrix;
    StaticShader *m_entityShader;
    TerrainShader *m_terrainShader;
    EntityRenderer *m_entityRenderer;
    TerrainRenderer *m_terrainRenderer;
    std::map<TexturedModel*, std::vector<Entity*>> m_entities;
    std::vector<Terrain*> m_terrains;
};

#endif // MASTERRENDERER_H
