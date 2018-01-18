#ifndef HASH_H
#define HASH_H
#define SIZE_HASH_TABLE 256

#include <string>
#include "glm/glm.hpp"

class Hash
{
public:
    Hash(int seed);
    int hash(int x);
    int hash(int x, int y);
    static glm::vec2 hashToVec(int hash);
private:
    static std::string FILE_NAME;
    int m_hash_table[SIZE_HASH_TABLE];
};

#endif // HASH_H
