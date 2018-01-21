#include "world.h"
#include "renderEngine/objloader.h"
#include <iostream>
#include "entities/player.h"

const std::string World::TEXTURE_NAME = "textures/textures.png";
const int World::DELETE_CHUNK_DISTANCE = 100;
const int World::DISPLAY_CHUNK_DISTANCE = 100;
const int World::LOAD_SIZE = 5;

World::World(Loader *loader) :
    m_loader(loader)
{
    m_texture = new ModelTexture(loader->loadTexture(TEXTURE_NAME));
    m_texture->setNumberRows(2);
    int size = 0;
    for(int x = 0; x < size; x++)
    {
        for(int y = 0; y < Chunk::WORLD_HEIGHT; y++)
        {
            for(int z = 0; z < size; z++)
            {
                Chunk *chunk = new Chunk(x*CHUNK_SIZE, y*CHUNK_SIZE, z*CHUNK_SIZE, m_texture, loader);
                m_chunks[P(x,y,z)] = chunk;
            }
        }
    }
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
    for(int chunkY = Chunk::WORLD_HEIGHT-1; chunkY >= 0; chunkY--)
    {
        P p(chunkX, chunkY, chunkZ);
        if(chunkLoaded(p))
        {
            Chunk *chunk = m_chunks.at(p);
            float h = chunk->height(X,Z);
            if(h > 0)
            {
                return h + chunkY*CHUNK_SIZE;
            }
        }
        else
        {
            return 40;
        }
    }
    return 0;
}

Block::ID World::block(int x, int y, int z) const
{
    int chunkX = (int) floor((double) x / CHUNK_SIZE);
    int chunkY = (int) floor((double) y / CHUNK_SIZE);
    int chunkZ = (int) floor((double) z / CHUNK_SIZE);
    int X = x % CHUNK_SIZE;
    int Y = y % CHUNK_SIZE;
    int Z = z % CHUNK_SIZE;
    P p(chunkX, chunkY, chunkZ);
    if(chunkLoaded(p))
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
    P p(chunkX, chunkY, chunkZ);
    if(chunkLoaded(p))
    {
        Chunk *chunk = m_chunks.at(p);
        chunk->setBlock(X,Y,Z,b);
    }
    else
    {
        std::cout << "ERROR, IMPOSSIBLE TO SET BLOCK" << std::endl;
    }
}

bool World::chunkLoaded(P const& p) const
{
    return m_chunks.find(p) != m_chunks.end();
}

void World::loadChunk(P const& p)
{
    if(!chunkLoaded(p))
    {
        std::cout << "loading..." << std::endl;
        m_chunks[p] = new Chunk(p.x*CHUNK_SIZE, p.y*CHUNK_SIZE, p.z*CHUNK_SIZE, m_texture, m_loader);
        std::cout << "loaded" << std::endl;
    }
}

void World::loadChunks(Player *player)
{

    //every second, check what chunks should be deleted, delete them,
    glm::vec3 pos = player->getposition();
    int chunkX = (int) floor((double) pos.x / CHUNK_SIZE);
    //int chunkY = (int) floor((double) pos.y / CHUNK_SIZE);
    int chunkZ = (int) floor((double) pos.z / CHUNK_SIZE);
    for(auto & chunk : m_chunks)
    {
        float d = distance(chunk.first*CHUNK_SIZE + CHUNK_SIZE/2, pos);
        if(d > DELETE_CHUNK_DISTANCE)
        {

        }
    }
    //then check the chunks to load, loads them
    for(int x = chunkX - LOAD_SIZE; x < chunkX + LOAD_SIZE; x++)
    {
        for(int y = 0; y < Chunk::WORLD_HEIGHT; y++)
        {
            for(int z = chunkZ - LOAD_SIZE; z < chunkZ + LOAD_SIZE; z++)
            {
                std::cout << "load chunk "<< x << ";" << y << ";" << z << std::endl;
                loadChunk(P(x,y,z));
            }
        }
    }
}
