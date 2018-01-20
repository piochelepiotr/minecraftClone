#include "displayManager.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "shaders/shaderProgram.h"
#include "textures/modelTexture.h"
#include "entities/camera.h"
#include "renderEngine/objloader.h"
#include "renderEngine/masterrenderer.h"
#include "terrain/terrain.h"
#include <vector>
#include "entities/player.h"
#include "world/world.h"
#include "guis/guitexture.h"
#include "toolbox/mousepicker.h"

using namespace glm;
using namespace std;

DisplayManager::DisplayManager(int width, int height, std::string title) :
    m_width(width),
    m_height(height),
    m_title(title),
    m_window(0)
{
    m_projection = perspective(70.0, (double) m_width / m_height, 1.0, 100.0);
    m_modelview = mat4(1.0);
}

bool DisplayManager::createDisplay()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 5;

    m_window = new sf::Window(sf::VideoMode(m_width, m_height), "OpenGL", sf::Style::Default, settings);
	m_window->setVerticalSyncEnabled(true);
    m_window->setActive(true);
    glewExperimental=GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cout << "error glew" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    return true;
}


void DisplayManager::mainLoop()
{
    World world(&m_loader);
    Camera camera(vec3(0,8,10));
    Light light(vec3(0,5000,3000), vec3(1,1,1));
    Player player(vec3(0,17,0), &m_loader, &world);
    MasterRenderer masterRenderer(m_width, m_height, &m_loader);
    m_window->setMouseCursorVisible(false);
    GuiTexture gui(m_loader.loadTexture("textures/cursor.png"), glm::vec2(0.02, 0.03), glm::vec2(0,0));
    MousePicker mousePicker(&camera, &world, masterRenderer.projectionMatrix(), m_width, m_height);

    bool running = true;
    sf::Vector2i center(m_window->getSize().x/2, m_window->getSize().y/2);
    while (running)
    {
        // gestion des évènements
        sf::Event event;
        bool firstMouseMove = true;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // on stoppe le programme
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // on ajuste le viewport lorsque la fenêtre est redimensionnée
                m_width = event.size.width;
                m_height = event.size.height;
                glViewport(0, 0, event.size.width, event.size.height);
                center = sf::Vector2i(m_window->getSize().x/2, m_window->getSize().y/2);
                mousePicker.updateWindowSize(m_width, m_height);
            }
            else if(event.type == sf::Event::MouseMoved)
            {
                int moveY = event.mouseMove.y - center.y;
                int moveX = -(event.mouseMove.x - center.x);
                if(moveX != 0 or moveY != 0)
                {
                    if(!firstMouseMove)
                    {
                        float pitch = moveY;
                        pitch /= 100;
                        float roY = moveX;
                        roY /= 200;
                        camera.setPitch(camera.pitch() + pitch);
                        player.setrotY(player.getrotY()+roY);
                    }
                    sf::Mouse::setPosition(center, *m_window);
                }
                firstMouseMove = false;
            }
            else if(event.type == sf::Event::MouseButtonPressed)
            {
                int x,y,z;
                if(mousePicker.getAimedBlock(x, y, z))
                {
                    std::cout << "got it !!" << std::endl;
                    world.setBlock(x, y, z, Block::AIR);
                }
                else
                {
                    std::cout << "sorry, not today" << std::endl;
                }
            }
        }

        //glm::vec3 mouseRay = mousePicker.currentRay();
        //std::cout << "mouse Ray : " << mouseRay.x << ";" << mouseRay.y << ";" << mouseRay.z << std::endl;

        player.move();
        camera.lockOnPlayer(&player);

        masterRenderer.processEntity(&player);
        masterRenderer.processEntities(world.getChunks());
        masterRenderer.processGui(&gui);
        masterRenderer.render(light, camera);
        m_window->display();
    }
}

DisplayManager::~DisplayManager()
{
    delete m_window;
}
