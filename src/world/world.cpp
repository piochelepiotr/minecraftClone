#include "world.h"
#include "renderEngine/objloader.h"
#include <iostream>

const std::string World::OBJECT_NAME = "objects/cube.obj";
const std::string World::TEXTURE_NAME = "textures/textures.png";

World::World(Loader *loader)
{
    m_texture = new ModelTexture(loader->loadTexture(TEXTURE_NAME));
    m_texture->setNumberRows(2);
    for(int x = 0; x < 10; x++)
    {
        for(int z = 0; z < 10; z++)
        {
            m_chunks[std::make_pair(x,z)] =new Chunk(x*CHUNK_SIZE, z*CHUNK_SIZE, m_texture, loader);
            glm::vec3 pos = m_chunks[std::make_pair(x,z)]->getposition();
            std::cout << "translation : " << pos.x << " " << pos.y << " " << pos.z << std::endl;
        }
    }
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
    delete m_texture;
    for(auto & chunk : m_chunks)
    {
        delete chunk.second;
    }
}

std::vector<Entity *> World::getChunks() const
{
    std::vector<Entity *> entities;
    for(auto & chunk : m_chunks)
    {
        entities.push_back((Entity*) chunk.second);
    }
    return entities;
}

float World::height(float x, float z) const
{
    int ix = (int) x;
    int iz = (int) z;
    int chunkX = (int) floor(x / CHUNK_SIZE);
    int chunkZ = (int) floor(z / CHUNK_SIZE);
    int X = ix % CHUNK_SIZE;
    int Z = iz % CHUNK_SIZE;
    std::pair<int,int> p(chunkX, chunkZ);
    if(m_chunks.find(p) != m_chunks.end())
    {
        Chunk *chunk = m_chunks.at(p);
        float h = chunk->height(X,Z);
        return h;
    }
    else
        return 40;
}

Block::ID World::block(int x, int y, int z) const
{
    int chunkX = (int) floor((double) x / CHUNK_SIZE);
    int chunkY = (int) floor((double) y / CHUNK_SIZE);
    int chunkZ = (int) floor((double) z / CHUNK_SIZE);
    int X = x % CHUNK_SIZE;
    int Y = y % CHUNK_SIZE;
    int Z = z % CHUNK_SIZE;
    std::pair<int,int> p(chunkX, chunkZ);
    if(m_chunks.find(p) != m_chunks.end() && chunkY == 0)
    {
        Chunk *chunk = m_chunks.at(p);
        return chunk->block(X,Y,Z);
    }
    else
        return Block::AIR;
}

void World::setBlock(int x, int y, int z, Block::ID b)
{
    int chunkX = (int) floor((double) x / CHUNK_SIZE);
    int chunkY = (int) floor((double) y / CHUNK_SIZE);
    int chunkZ = (int) floor((double) z / CHUNK_SIZE);
    int X = x % CHUNK_SIZE;
    int Y = y % CHUNK_SIZE;
    int Z = z % CHUNK_SIZE;
    std::pair<int,int> p(chunkX, chunkZ);
    if(m_chunks.find(p) != m_chunks.end() && chunkY == 0)
    {
        Chunk *chunk = m_chunks.at(p);
        chunk->setBlock(X,Y,Z,b);
    }
    else
    {
        std::cout << "ERROR, IMPOSSIBLE TO SET BLOCK" << std::endl;
    }
}
