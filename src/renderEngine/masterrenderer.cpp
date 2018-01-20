#include "masterrenderer.h"

const float MasterRenderer::m_fov = 50;
const float MasterRenderer::m_farPlane = 1000;
const float MasterRenderer::m_nearPlane = 0.1;
const glm::vec3 MasterRenderer::m_skyColour = glm::vec3(5.0/256.0, 189.0/256.0, 206.0/256.0);

MasterRenderer::MasterRenderer(int width, int height, Loader *loader) :
    m_width(width),
    m_height(height)
{
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    createProjectionMatrix();
    m_entityShader = new StaticShader();
    m_terrainShader = new TerrainShader();
    m_entityRenderer = new EntityRenderer(m_entityShader, m_projectionMatrix);
    m_terrainRenderer = new TerrainRenderer(m_terrainShader, m_projectionMatrix);
    m_guiRenderer = new GuiRenderer(loader);
}

MasterRenderer::~MasterRenderer()
{
    delete m_entityShader;
    delete m_terrainShader;
    delete m_entityRenderer;
    delete m_terrainRenderer;
    delete m_guiRenderer;
}

void MasterRenderer::render(Light const& sun, Camera const& camera)
{
    prepare();
    m_entityShader->start();
    m_entityShader->loadSkyColour(m_skyColour);
    m_entityShader->loadLight(sun);
    m_entityShader->loadViewMatrix(camera);
    m_entityRenderer->render(m_entities);
    m_entityShader->stop();
    m_entities.clear();
    m_terrainShader->start();
    m_terrainShader->loadLight(sun);
    m_terrainShader->loadSkyColour(m_skyColour);
    m_terrainShader->loadViewMatrix(camera);
    m_terrainRenderer->render(m_terrains);
    m_terrainShader->stop();
    m_terrains.clear();
    m_guiRenderer->render(m_guis);
    m_guis.clear();
}

void MasterRenderer::processEntity(Entity *entity)
{
    TexturedModel *texturedModel = entity->getmodel();
    if(m_entities.find(texturedModel) == m_entities.end())
    {
        std::vector<Entity*> tab;
        m_entities[texturedModel] = tab;
    }
    m_entities[texturedModel].push_back(entity);
}

void MasterRenderer::processEntities(std::vector<Entity *> const& entities)
{
    for(auto & entity : entities)
    {
        processEntity(entity);
    }
}

void MasterRenderer::processTerrain(Terrain *terrain)
{
    m_terrains.push_back(terrain);
}

void MasterRenderer::processGui(GuiTexture* gui)
{
    m_guis.push_back(gui);
}

void MasterRenderer::prepare()
{
    glClearColor(m_skyColour.r, m_skyColour.g, m_skyColour.b, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::createProjectionMatrix()
{
    m_projectionMatrix = glm::perspective(glm::radians(m_fov), (float) m_width / m_height, m_nearPlane, m_farPlane);
}

glm::mat4 MasterRenderer::projectionMatrix() const
{
    return m_projectionMatrix;
}
