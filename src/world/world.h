#ifndef WORLD_H
#define WORLD_H

#include "entities/player.h"
#include <vector>
#include <map>
#include "world/chunk.h"
#include "toolbox/p.h"

class Player;

class World
{
public:
    World(Loader *loader);
    ~World();
    std::vector<Entity *> getChunks() const;
    float height(float x, float z) const;
    Block::ID block(int x, int y, int z) const;
    void setBlock(int x, int y, int z, Block::ID b);
    void loadChunks(Player *player);
private:
    bool chunkLoaded(P const& p) const;
    void loadChunk(P const& p);
    std::map<P, Chunk *>m_chunks;
    ModelTexture *m_texture;
    const static std::string TEXTURE_NAME;
    const static double DELETE_CHUNK_DISTANCE;
    const static double DISPLAY_CHUNK_DISTANCE;
    const static int LOAD_SIZE;
    Loader *m_loader;
};

#endif // WORLD_H
