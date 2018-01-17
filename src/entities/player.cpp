#include "player.h"
#include "renderEngine/objloader.h"
#include "SFML/Window.hpp"
#include "world/chunk.h"

const std::string Player::OBJECT_NAME = "objects/steve.obj";
const std::string Player::TEXTURE_NAME = "textures/skin.png";
const float Player::ACCEL = -9.81;

Player::Player(glm::vec3 position, Loader *loader) : Entity()
{
    m_rawModel = OBJLoader::loadObjModel(OBJECT_NAME, loader);
    m_texture = new ModelTexture(loader->loadTexture(TEXTURE_NAME));
    m_texture->setShineDamper(20);
    m_texture->setReflectivity(0.3);
    m_model = new TexturedModel(m_rawModel, m_texture);
    m_position = position;
    m_rotX = 0;
    m_rotY = 0;
    m_rotZ = 0;
    m_scale = 1;
}

Player::~Player()
{
    delete m_texture;
    delete m_rawModel;
    delete m_model;
}

void Player::move()
{
    float ground = 16*Chunk::BLOCK_SIZE;
    float speed = 1;
    glm::mat4 mat(1.0);
    mat = glm::rotate   (mat, m_rotY, glm::vec3(0, 1, 0));
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        glm::vec3 forward(0, 0, -speed);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        m_position.x += movement.x;
        m_position.z += movement.z;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        glm::vec3 forward(0, 0, speed);
        glm::vec3 movement = mat * glm::vec4(forward, 1);
        m_position.x += movement.x;
        m_position.z += movement.z;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::L))
    {
        m_rotY -= speed/10.0;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
    {
        m_rotY += speed/10.0;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        m_position = glm::vec3(0,0,-10);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        m_speedY = 0.3;
    }
    float step = 0.002;
    m_speedY += ACCEL*step;
    m_position.y += m_speedY;
    if(m_position.y < ground)
        m_position.y = ground;
}
