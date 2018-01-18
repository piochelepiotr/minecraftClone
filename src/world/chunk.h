#ifndef CHUNK_H
#define CHUNK_H

#include "models/rawModel.h"
#include "renderEngine/loader.h"
#include "world/block.h"
#include <vector>
#include <glm/glm.hpp>
#define CHUNK_SIZE 16
#define BIOME_SIZE 32

class Chunk
{
public:
    Chunk(int startX, int startZ, Loader *loader);
    RawModel *getModel() const { return m_rawModel; }
    const static float BLOCK_SIZE;
private:
    static float perlinNoise2D(glm::vec2 const& p);
    static void addFace(std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & textures,
                        std::vector<glm::vec3> & normals, std::vector<int> & indexes,
                        glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, glm::vec3 const& p4,
                        glm::vec3 const& n);
    void buildRawModel(Loader *loader, std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & textures,
                        std::vector<glm::vec3> & normals, std::vector<int> & indexes);
    void buildFaces(Loader *loader);
    RawModel *m_rawModel;
    Block::ID m_blocks [CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
};

#endif // CHUNK_H
