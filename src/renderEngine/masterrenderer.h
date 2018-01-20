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
#include "guis/guirenderer.h"

class MasterRenderer
{
public:
    MasterRenderer(int width, int height, Loader *loader);
    ~MasterRenderer();
    void render(Light const& sun, Camera const& camera);
    void processEntity(Entity *entity);
    void processEntities(std::vector<Entity *> const& entities);
    void processTerrain(Terrain *terrain);
    void processGui(GuiTexture* gui);
    void prepare();
    glm::mat4 projectionMatrix() const;
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
    GuiRenderer *m_guiRenderer;
    std::map<TexturedModel*, std::vector<Entity*>> m_entities;
    std::vector<Terrain*> m_terrains;
    std::vector<GuiTexture*>m_guis;
};

#endif // MASTERRENDERER_H
