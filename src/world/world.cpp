#include "world.h"
#include "renderEngine/objloader.h"

const std::string World::OBJECT_NAME = "objects/cube.obj";
const std::string World::TEXTURE_NAME = "textures/textures.png";

World::World(Loader *loader)
{
    m_chunks = new Chunk(0, 0, loader);
    m_texture = new ModelTexture(loader->loadTexture(TEXTURE_NAME));
    m_texture->setNumberRows(2);
    m_rawModel = m_chunks->getModel();// OBJLoader::loadObjModel(OBJECT_NAME, loader);
    m_texturedModel = new TexturedModel(m_rawModel, m_texture);
    m_blocks.push_back(new Entity(glm::vec3(0,0,0), m_texturedModel, 0, 0, 0, 1, 1));
    /*int worldSize = 8;
    float size = 2;
    for(int i = -worldSize; i < worldSize; i++)
    {
        for(int j = -worldSize; j < worldSize; j++)
        {
            //float height = rand() % 5 + 1;
            int height = 16;
            for(int z = 1; z <= height; z++)
            {
                m_blocks.push_back(new Entity(glm::vec3((float) i*size,(z - 2)*size,(float) j*size), m_texturedModel, 0, 0, 0, size, 1));
            }
        }
    }*/
}

World::~World()
{
    delete m_texturedModel;
    delete m_texture;
    delete m_rawModel;
    delete m_chunks;
    for(auto & block : m_blocks)
    {
        delete block;
    }
}
