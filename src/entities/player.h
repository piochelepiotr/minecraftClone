#ifndef PLAYER_H
#define PLAYER_H

#include "glm/glm.hpp"
#include "entities/Entity.h"
#include "renderEngine/loader.h"

class World;
class MousePicker;

class Player : public Entity
{
public:
    Player(glm::vec3 position, Loader *loader, World *world, MousePicker *mousePicker);
    ~Player();
    void move(long currentTime);
private:
    void fall(double delta, const glm::mat4 &rot);
    double placeInFront(glm::vec3 const& forward, const glm::mat4 &rot);
    const static std::string OBJECT_NAME;
    const static std::string TEXTURE_NAME;
    const static long DELAY_RUN;
    const static long DELAY_REFRESH_WORLD;
    RawModel *m_rawModel;
    ModelTexture *m_texture;
    bool m_inTheAir;
    float m_speedY;
    static const float ACCEL;
    World *m_world;
    MousePicker *m_mousePicker;
    double m_inAir;
    long m_timeLastUpdate;
    double m_walkSpeed;
    double m_runSpeed;
    long m_lastForwardPressed;
    bool m_ForwardPressed;
    double m_speed;
    bool m_fly;
    bool m_spacePressed;
    long m_lastSpacePressed;
    long m_lastTimeWorldRefreshed;
};

#endif // PLAYER_H
