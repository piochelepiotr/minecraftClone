#include "chunk.h"
#include <iostream>
#include "toolbox/perlinnoise.h"

using namespace std;

const float Chunk::BLOCK_SIZE = 1;

Chunk::Chunk(int startX, int startZ, Loader *loader)
{
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            int height = (int) (PerlinNoise::noise((float) (x+startX) / BIOME_SIZE, (float) (z+startZ) / BIOME_SIZE)*CHUNK_SIZE);
            for(int y = 0; y < height; y++)
            {
                m_blocks[x][y][z] = Block::STONE;
            }
            for(int y = height; y < CHUNK_SIZE; y++)
            {
                m_blocks[x][y][z] = Block::AIR;
            }
        }
    }
    /*
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int y = 0; y < CHUNK_SIZE; y++)
        {

            int height = ;
            for(int z = CHUNK_SIZE-height; z < CHUNK_SIZE; z++)
            {
                m_blocks[x][y][z] = Block::AIR;
            }
        }
    }*/
    buildFaces(loader);
}

void Chunk::buildFaces(Loader *loader)
{
    vector<glm::vec3> vertices;
    vector<glm::vec2> textures;
    vector<glm::vec3> normals;
    vector<int> indexes;
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int y = 0; y < CHUNK_SIZE; y++)
        {
            for(int z = 0; z < CHUNK_SIZE; z++)
            {
                Block::ID b = m_blocks[x][y][z];
                Block::ID a = Block::AIR;
                //add face if not block isn't air and the block next to it is air
                /*faces are :
                 * up ( + y)
                 * bottom (-y)
                 * right (+x)
                 * left (-x)
                 * front (+z)
                 * back (-z)
                 * 0 point is : bottom, left, back
                 */
                //up
                if(!(b == a || (y + 1 < CHUNK_SIZE && m_blocks[x][y+1][z] != a)))
                {
                    glm::vec3 n(0,1,0);
                    glm::vec3 p1(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z  ));
                    glm::vec3 p2(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z  ));
                    glm::vec3 p3(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
                //bottom
                if(!(b == a || (y - 1 > 0 && m_blocks[x][y-1][z] != a)))
                {
                    glm::vec3 n(0,-1,0);
                    glm::vec3 p1(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y), BLOCK_SIZE*(z  ));
                    glm::vec3 p2(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y), BLOCK_SIZE*(z  ));
                    glm::vec3 p3(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
                //right
                if(!(b == a || (x + 1 < CHUNK_SIZE && m_blocks[x+1][y][z] != a)))
                {
                    glm::vec3 n(1,0,0);
                    glm::vec3 p1(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z  ));
                    glm::vec3 p2(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z  ));
                    glm::vec3 p3(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
                //left
                if(!(b == a || (x - 1 > 0 && m_blocks[x-1][y][z] != a)))
                {
                    glm::vec3 n(-1,0,0);
                    glm::vec3 p1(BLOCK_SIZE*(x), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z  ));
                    glm::vec3 p2(BLOCK_SIZE*(x), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z  ));
                    glm::vec3 p3(BLOCK_SIZE*(x), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
                //front
                if(!(b == a || (z + 1 < CHUNK_SIZE && m_blocks[x][y][z+1] != a)))
                {
                    glm::vec3 n(0,0,1);
                    glm::vec3 p1(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    glm::vec3 p2(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    glm::vec3 p3(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
                //back
                if(!(b == a || (z - 1 > 0 && m_blocks[x][y][z-1] != a)))
                {
                    glm::vec3 n(0,0,-1);
                    glm::vec3 p1(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    glm::vec3 p2(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y  ), BLOCK_SIZE*(z+1));
                    glm::vec3 p3(BLOCK_SIZE*(x+1), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    glm::vec3 p4(BLOCK_SIZE*(x  ), BLOCK_SIZE*(y+1), BLOCK_SIZE*(z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n);
                }
            }
        }
    }
    buildRawModel(loader, vertices, textures, normals, indexes);
}

void Chunk::addFace(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &textures,
                    std::vector<glm::vec3> &normals, std::vector<int> &indexes,
                    const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
                    const glm::vec3 &p4, const glm::vec3 &n)
{
    glm::vec2 t1(0,0);
    glm::vec2 t2(1,0);
    glm::vec2 t3(1,1);
    glm::vec2 t4(0,1);
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
    vertices.push_back(p4);
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    normals.push_back(n);
    textures.push_back(t1);
    textures.push_back(t2);
    textures.push_back(t3);
    textures.push_back(t4);
    int start_index = 0;
    if(indexes.size() > 0)
    {
        start_index = indexes.back() + 1;
    }
    indexes.push_back(start_index);
    indexes.push_back(start_index + 1);
    indexes.push_back(start_index + 2);

    indexes.push_back(start_index);
    indexes.push_back(start_index + 2);
    indexes.push_back(start_index + 3);
}

void Chunk::buildRawModel(Loader *loader, std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &textures,
                          std::vector<glm::vec3> &normals, std::vector<int> &indexes)
{
    int size = vertices.size();
    int ind_size = indexes.size();
    float *verticesArray = new float[size*3];
    float *texturesArray = new float[size*2];
    float *normalsArray = new float[size*3];
    int *indexesArray = new int[ind_size];
    for(uint i = 0; i < size; i++)
    {
        verticesArray[3*i] = vertices[i].x;
        verticesArray[3*i+1] = vertices[i].y;
        verticesArray[3*i+2] = vertices[i].z;
        texturesArray[2*i] = textures[i].x;
        texturesArray[2*i+1] = textures[i].y;
        normalsArray[3*i] = normals[i].x;
        normalsArray[3*i+1] = normals[i].y;
        normalsArray[3*i+2] = normals[i].z;
    }
    for(uint i = 0; i < ind_size; i++)
    {
        indexesArray[i] = indexes[i];
    }
    m_rawModel = loader->loadToVao(verticesArray, size*3, texturesArray, size*2 ,indexesArray, ind_size, normalsArray, size*3);
}
