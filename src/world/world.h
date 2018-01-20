#ifndef WORLD_H
#define WORLD_H

#include "entities/player.h"
#include <vector>
#include <map>
#include "world/chunk.h"

class World
{
public:
    World(Loader *loader);
    ~World();
    std::vector<Entity *> getChunks() const;
    float height(float x, float z) const;
    Block::ID block(int x, int y, int z) const;
    void setBlock(int x, int y, int z, Block::ID b);
private:
    std::map<std::pair<int, int>, Chunk *>m_chunks;
    ModelTexture *m_texture;
    const static std::string OBJECT_NAME;
    const static std::string TEXTURE_NAME;
};

#endif // WORLD_H
