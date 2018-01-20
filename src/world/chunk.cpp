#include "chunk.h"
#include <iostream>
#include "toolbox/perlinnoise.h"

using namespace std;

const int Chunk::m_numberRowsTextures = 2;

Chunk::Chunk(int startX, int startZ, ModelTexture *texture, Loader *loader) : Entity()
{
    m_position = glm::vec3(startX, 0, startZ);
    m_loader = loader;
    std::cout << startX << " " << startZ << std::endl;
    for(int x = 0; x < CHUNK_SIZE; x++)
    {
        for(int z = 0; z < CHUNK_SIZE; z++)
        {
            int height = (int) (PerlinNoise::noise((float) (x+startX) / BIOME_SIZE, (float) (z+startZ) / BIOME_SIZE)*CHUNK_SIZE);
            for(int y = 0; y < height-1; y++)
            {
                m_blocks[x][y][z] = Block::DIRT;
            }
            if(height > 0)
            {
                m_blocks[x][height-1][z] = Block::GRASS;
            }
            for(int y = height; y < CHUNK_SIZE; y++)
            {
                m_blocks[x][y][z] = Block::AIR;
            }
        }
    }
    buildFaces(loader);
    m_model = new TexturedModel(m_rawModel, texture);
}

Chunk::~Chunk()
{
    delete m_model;
    delete m_rawModel;
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
                    //std::cout << "up" << std::endl;
                    glm::vec3 n(0,1,0);
                    glm::vec3 p1(x  , y+1, z  );
                    glm::vec3 p2(x+1, y+1, z  );
                    glm::vec3 p3(x+1, y+1, z+1);
                    glm::vec3 p4(x  , y+1, z+1);
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
                //bottom
                if(!(b == a || (y - 1 > 0 && m_blocks[x][y-1][z] != a)))
                {
                    //std::cout << "bottom" << std::endl;
                    glm::vec3 n(0,-1,0);
                    glm::vec3 p1(x  , y, (z  ));
                    glm::vec3 p2(x+1, y, (z  ));
                    glm::vec3 p3(x+1, y, (z+1));
                    glm::vec3 p4(x  , y, (z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
                //right
                if(!(b == a || (x + 1 < CHUNK_SIZE && m_blocks[x+1][y][z] != a)))
                {
                    //std::cout << "right" << std::endl;
                    glm::vec3 n(1,0,0);
                    glm::vec3 p1((x+1), (y+1), (z+1));
                    glm::vec3 p2((x+1), (y+1), (z  ));
                    glm::vec3 p3((x+1), (y  ), (z  ));
                    glm::vec3 p4((x+1), (y  ), (z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
                //left
                if(!(b == a || (x - 1 > 0 && m_blocks[x-1][y][z] != a)))
                {
                    //std::cout << "left" << std::endl;
                    glm::vec3 n(-1,0,0);
                    glm::vec3 p1((x), (y+1), (z  ));
                    glm::vec3 p2((x), (y+1), (z+1));
                    glm::vec3 p3((x), (y  ), (z+1));
                    glm::vec3 p4((x), (y  ), (z  ));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
                //front
                if(!(b == a || (z + 1 < CHUNK_SIZE && m_blocks[x][y][z+1] != a)))
                {
                    //std::cout << "front" << std::endl;
                    glm::vec3 n(0,0,1);
                    glm::vec3 p1((x  ), (y+1), (z+1));
                    glm::vec3 p2((x+1), (y+1), (z+1));
                    glm::vec3 p3((x+1), (y  ), (z+1));
                    glm::vec3 p4((x  ), (y  ), (z+1));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
                //back
                if(!(b == a || (z - 1 > 0 && m_blocks[x][y][z-1] != a)))
                {
                    //std::cout << "back" << std::endl;
                    glm::vec3 n(0,0,-1);
                    glm::vec3 p1((x+1), (y+1), (z));
                    glm::vec3 p2((x  ), (y+1), (z));
                    glm::vec3 p3((x  ), (y  ), (z));
                    glm::vec3 p4((x+1), (y  ), (z));
                    addFace(vertices, textures, normals, indexes, p1, p2, p3, p4, n, b);
                }
            }
        }
    }
    buildRawModel(loader, vertices, textures, normals, indexes);
}

void Chunk::addFace(std::vector<glm::vec3> &vertices, std::vector<glm::vec2> &textures,
                    std::vector<glm::vec3> &normals, std::vector<int> &indexes,
                    const glm::vec3 &p1, const glm::vec3 &p2, const glm::vec3 &p3,
                    const glm::vec3 &p4, const glm::vec3 &n,
                    Block::ID b)
{
    if(b == Block::GRASS)
    {
        if(n == glm::vec3(0,-1,0))
        {
            b = Block::DIRT;
        }
        else if(n != glm::vec3(0,1,0))
        {
            b = Block::GRASS_SIDE;
        }
    }
    int textureX = (int) b % m_numberRowsTextures;
    int textureY = (int) b / m_numberRowsTextures;
    float offsetTextureX = (float) textureX / (float) m_numberRowsTextures;
    float offsetTextureY = (float) textureY / (float) m_numberRowsTextures;
    glm::vec2 offsetTexture(offsetTextureX, offsetTextureY);
    glm::vec2 t1(0,0);
    glm::vec2 t2(1,0);
    glm::vec2 t3(1,1);
    glm::vec2 t4(0,1);
    t1 = t1/((float) m_numberRowsTextures)  + offsetTexture;
    t2 = t2/((float) m_numberRowsTextures) + offsetTexture;
    t3 = t3/((float) m_numberRowsTextures) + offsetTexture;
    t4 = t4/((float) m_numberRowsTextures) + offsetTexture;
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
    for(int i = 0; i < size; i++)
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
    for(int i = 0; i < ind_size; i++)
    {
        indexesArray[i] = indexes[i];
    }
    m_rawModel = loader->loadToVao(verticesArray, size*3, texturesArray, size*2 ,indexesArray, ind_size, normalsArray, size*3);
}


float Chunk::height(float x, float z) const
{
    int X = (int) x;
    int Z = (int) z;
    for(int y = CHUNK_SIZE; y > 0; y--)
    {
        if(m_blocks[X][y-1][Z] != Block::AIR)
        {
            return y;
        }
    }
    return 0;
}

void Chunk::setBlock(int x, int y, int z, Block::ID b)
{
    std::cout << "SETTING BLOCK !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    m_blocks[x][y][z] = b;
    delete m_rawModel;
    buildFaces(m_loader);
    m_model->setModel(m_rawModel);
}
