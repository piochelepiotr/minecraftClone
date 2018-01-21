#include "player.h"
#include "renderEngine/objloader.h"
#include "SFML/Window.hpp"
#include "world/chunk.h"
#include "world/world.h"
#include "toolbox/mousepicker.h"
#include <iostream>
#include <math.h>

const std::string Player::OBJECT_NAME = "objects/steve.obj";
const std::string Player::TEXTURE_NAME = "textures/skin.png";
const float Player::ACCEL = -9.81;
const long Player::DELAY_RUN = 200;
const long Player::DELAY_REFRESH_WORLD = 1000;

Player::Player(glm::vec3 position, Loader *loader, World *world, MousePicker *mousePicker) : Entity(),
    m_mousePicker(mousePicker),
    m_walkSpeed(5),
    m_runSpeed(15),
    m_ForwardPressed(false),
    m_fly(true),
    m_lastTimeWorldRefreshed(0)
{
    m_timeLastUpdate = -1;
    m_inAir = true;
    m_world = world;
    m_rawModel = OBJLoader::loadObjModel(OBJECT_NAME, loader);
    m_texture = new ModelTexture(loader->loadTexture(TEXTURE_NAME));
    m_model = new TexturedModel(m_rawModel, m_texture);
    m_position = position;
    m_rotX = 0;
    m_rotY = 0;
    m_rotZ = 0;
    m_scale = 1;
    m_lastForwardPressed = 0;
    std::cout << "pos y = " << m_position.y << std::endl;
}

Player::~Player()
{
    delete m_texture;
    delete m_rawModel;
    delete m_model;
}

void Player::move(long currentTime)
{
    if(currentTime - m_lastTimeWorldRefreshed > DELAY_REFRESH_WORLD)
    {
        m_lastTimeWorldRefreshed = currentTime;
        m_world->loadChunks(this);
    }
    double delta = (double) (currentTime - m_timeLastUpdate) / 1000.0;
    glm::mat4 mat(1.0);
    mat = glm::rotate   (mat, m_rotY, glm::vec3(0, 1, 0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        if(!m_ForwardPressed)
        {
            if(currentTime - m_lastForwardPressed < DELAY_RUN)
            {
                m_speed = m_runSpeed;
            }

            else
            {
                m_speed = m_walkSpeed;
            }
        }
        glm::vec3 forward(0, 0, -delta*m_speed);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        //std::cout << "move : " << movement.x << ";"<<movement.y << ";" << movement.z << std::endl;
        double place = placeInFront(movement, mat);
        double usedPlace = glm::length(movement);
        //std::cout <<"place : " << place << std::endl;
        if(usedPlace > place)
        {
            //std::cout << "NO PLACE" << std::endl;
            //std::cout <<"used : " << usedPlace << std::endl;
            double r = place / usedPlace;
            movement = glm::vec3(movement.x*r, movement.y*r, movement.z*r);
        }
        m_position.x += movement.x;
        m_position.z += movement.z;
        m_lastForwardPressed = currentTime;
        m_ForwardPressed = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        glm::vec3 forward(0, 0, delta*m_walkSpeed);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        m_position.x += movement.x;
        m_position.z += movement.z;
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        m_ForwardPressed = false;
    }
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        glm::vec3 forward(speed, 0, 0);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        m_position.x += movement.x;
        m_position.z += movement.z;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        glm::vec3 forward(-speed, 0, 0);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        m_position.x += movement.x;
        m_position.z += movement.z;
    }*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if(!m_spacePressed)
        {
            if(currentTime - m_lastSpacePressed < DELAY_RUN)
            {
                m_fly = !m_fly;
                m_speedY = 0;
            }
        }
        if(!m_fly)
        {
            if(!m_inAir)
            {
                m_inAir = true;
                m_speedY = 5;
            }
        }
        else
        {
            m_position.y += m_runSpeed * delta;
        }
        m_lastSpacePressed = currentTime;
        m_spacePressed = true;
    }
    else
    {
        m_spacePressed = false;
    }
    if(!m_fly)
    {
        fall(delta, mat);
    }
    m_timeLastUpdate = currentTime;
}


double Player::placeInFront(glm::vec3 const& forward, glm::mat4 const& rot)
{
    glm::vec3 shiftBR = rot * glm::vec4(0.5 , 0, -0.25, 1);
    glm::vec3 shiftBM = rot * glm::vec4(0   , 0, -0.25, 1);
    glm::vec3 shiftBL = rot * glm::vec4(-0.5, 0, -0.25, 1);
    glm::vec3 shiftUR = rot * glm::vec4(0.5 , 1.9, -0.25, 1);
    glm::vec3 shiftUM = rot * glm::vec4(0   , 1.9, -0.25, 1);
    glm::vec3 shiftUL = rot * glm::vec4(-0.5, 1.9, -0.25, 1);
    double p1 = m_mousePicker->placeInFront(m_position.x + shiftBR.x, m_position.y + shiftBR.y, m_position.z + shiftBR.z, forward);
    double p2 = m_mousePicker->placeInFront(m_position.x + shiftBM.x, m_position.y + shiftBM.y, m_position.z + shiftBM.z, forward);
    double p3 = m_mousePicker->placeInFront(m_position.x + shiftBL.x, m_position.y + shiftBL.y, m_position.z + shiftBL.z, forward);
    double p4 = m_mousePicker->placeInFront(m_position.x + shiftUR.x, m_position.y + shiftUR.y, m_position.z + shiftUR.z, forward);
    double p5 = m_mousePicker->placeInFront(m_position.x + shiftUM.x, m_position.y + shiftUM.y, m_position.z + shiftUM.z, forward);
    double p6 = m_mousePicker->placeInFront(m_position.x + shiftUL.x, m_position.y + shiftUL.y, m_position.z + shiftUL.z, forward);
    return std::min(std::min(p1,p2), std::min(std::min(p3,p4), std::min(p5,p6)));
}

void Player::fall(double delta, glm::mat4 const& rot)
{
    glm::vec3 shiftBFR = rot * glm::vec4(0.5 , 0, -0.25, 1);
    glm::vec3 shiftBFM = rot * glm::vec4(0   , 0, -0.25, 1);
    glm::vec3 shiftBFL = rot * glm::vec4(-0.5, 0, -0.25, 1);
    glm::vec3 shiftBBR = rot * glm::vec4(0.5 , 0,  0.25, 1);
    glm::vec3 shiftBBM = rot * glm::vec4(0   , 0,  0.25, 1);
    glm::vec3 shiftBBL = rot * glm::vec4(-0.5, 0,  0.25, 1);
    double g1 = m_world->height(m_position.x + shiftBFR.x, m_position.z + shiftBFR.y);
    double g2 = m_world->height(m_position.x + shiftBFM.x, m_position.z + shiftBFM.y);
    double g3 = m_world->height(m_position.x + shiftBFL.x, m_position.z + shiftBFL.y);
    double g4 = m_world->height(m_position.x + shiftBBR.x, m_position.z + shiftBBR.y);
    double g5 = m_world->height(m_position.x + shiftBBM.x, m_position.z + shiftBBM.y);
    double g6 = m_world->height(m_position.x + shiftBBL.x, m_position.z + shiftBBL.y);
    double ground = std::max(std::max(g1, g2), std::max(std::max(g3,g4), std::max(g5, g6)));
    std::cout << "ground = " << ground << std::endl;

    if(ground < m_position.y)
    {
        m_inAir = true;
    }
    if(m_inAir)
    {
        m_speedY += ACCEL*delta;
    }
    m_position.y += m_speedY*delta;
    if(m_position.y < ground)
    {
        m_position.y = ground;
        m_inAir = false;
        m_speedY = 0;
    }
}
