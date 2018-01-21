#ifndef CHUNK_H
#define CHUNK_H

#include "models/rawModel.h"
#include "renderEngine/loader.h"
#include "world/block.h"
#include <vector>
#include "entities/Entity.h"
#include <glm/glm.hpp>
#define CHUNK_SIZE 16
#define BIOME_SIZE 32


class Chunk : public Entity
{
public:
    Chunk(int startX, int startY, int startZ, ModelTexture * texture, Loader *loader);
    virtual ~Chunk();
    RawModel *getModel() const { return m_rawModel; }
    float height(float x, float z) const;
    Block::ID block(int x, int y, int z) const { return m_blocks[x][y][z]; }
    void setBlock(int x, int y, int z, Block::ID b);
    static const int WORLD_HEIGHT;
private:
    static void addFace(std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & textures,
                        std::vector<glm::vec3> & normals, std::vector<int> & indexes,
                        glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, glm::vec3 const& p4,
                        glm::vec3 const& n, Block::ID b);
    void buildRawModel(Loader *loader, std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & textures,
                        std::vector<glm::vec3> & normals, std::vector<int> & indexes);
    void buildFaces(Loader *loader);
    RawModel *m_rawModel;
    Loader *m_loader;
    Block::ID m_blocks [CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    static const int m_numberRowsTextures;
};

#endif // CHUNK_H
