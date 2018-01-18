#include "hash.h"

using namespace glm;

Hash::Hash(int seed)
{
    //this is certainly not good at all
    for(int i = 0; i < SIZE_HASH_TABLE; i++)
    {
        m_hash_table[i] = seed;
        seed *= 2;
        if(seed > 100000000)
        {
            seed /= 15;
        }
    }
}

int Hash::hash(int x)
{
    if(x < 0) x = -x;
    x = x % SIZE_HASH_TABLE;
    return m_hash_table[x];
}

int Hash::hash(int x, int y)
{
    return hash(hash(hash(x)) + hash(y));
}

glm::vec2 Hash::hashToVec(int hash)
{
    switch(hash & 3)
    {
    case 0:
        return vec2(1,1);
    case 1:
        return vec2(1,-1);
    case 2:
        return vec2(-1,1);
    case 3:
        return vec2(-1,-1);
    }
}
