#ifndef PLAYER_H
#define PLAYER_H

#include "glm/glm.hpp"
#include "entities/Entity.h"
#include "renderEngine/loader.h"

class Player : public Entity
{
public:
    Player(glm::vec3 position, Loader *loader);
    ~Player();
    void move();
private:
    const static std::string OBJECT_NAME;
    const static std::string TEXTURE_NAME;
    RawModel *m_rawModel;
    ModelTexture *m_texture;
    bool m_inTheAir;
    float m_speedY;
    static const float ACCEL;
};

#endif // PLAYER_H
