#ifndef WORLD_H
#define WORLD_H

#include "entities/player.h"
#include <vector>
#include "world/chunk.h"

class World
{
public:
    World(Loader *loader);
    ~World();
    std::vector<Entity *> getBlocks() const { return m_blocks; }
private:
    std::vector<Entity *>m_blocks;
    Chunk *m_chunks;
    ModelTexture *m_texture;
    RawModel *m_rawModel;
    TexturedModel *m_texturedModel;
    const static std::string OBJECT_NAME;
    const static std::string TEXTURE_NAME;
};

#endif // WORLD_H
