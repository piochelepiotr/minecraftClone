#include <iostream>
#include "displayManager.h"
#include "toolbox/mousepicker.h"
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
#include <chrono>

using namespace glm;
using namespace std;

DisplayManager::DisplayManager(int width, int height, std::string title) : m_width(width),
                                                                           m_height(height),
                                                                           m_title(title),
                                                                           m_window(0),
																		   m_gameState()
{
    m_projection = perspective(70.0, (double)m_width / m_height, 1.0, 100.0);
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
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error glew" << std::endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    return true;
}

void DisplayManager::mainLoop()
{
    m_window->setMouseCursorVisible(false);
    World world(&m_loader);
    Camera camera(vec3(0, 8, 10));
    MasterRenderer masterRenderer(m_width, m_height, &m_loader);
    MousePicker mousePicker(&camera, &world, masterRenderer.projectionMatrix(), m_width, m_height);
    Player player(vec3(10, 50, 10), &m_loader, &world, &mousePicker);
    GuiTexture gui(m_loader.loadTexture("textures/cursor.png"), glm::vec2(0.02, 0.03), glm::vec2(0, 0));

    bool running = true;
    sf::Vector2i center(m_window->getSize().x / 2, m_window->getSize().y / 2);
    while (running)
    {
        // events
        sf::Event event;
        bool firstMouseMove = true;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // exit code
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust window size
                m_width = event.size.width;
                m_height = event.size.height;
                glViewport(0, 0, event.size.width, event.size.height);
                center = sf::Vector2i(m_window->getSize().x / 2, m_window->getSize().y / 2);
                mousePicker.updateWindowSize(m_width, m_height);
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                int moveY = event.mouseMove.y - center.y;
                int moveX = -(event.mouseMove.x - center.x);
                if (moveX != 0 or moveY != 0)
                {
                    if (!firstMouseMove)
                    {
                        float pitch = moveY;
                        pitch /= 100;
                        float roY = moveX;
                        roY /= 200;
                        camera.setPitch(camera.pitch() + pitch);
                        player.setrotY(player.getrotY() + roY);
                    }
                    sf::Mouse::setPosition(center, *m_window);
                }
                firstMouseMove = false;
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                //mousePicker.update();
                //glm::vec3 mouseRay = mousePicker.currentRay();
                //std::cout << "mouse Ray : " << mouseRay.x << ";" << mouseRay.y << ";" << mouseRay.z << std::endl;
                int x, y, z;
                if (mousePicker.getAimedBlock(x, y, z))
                {
                    world.setBlock(x, y, z, Block::AIR);
                }
                else
                {
                }
            }
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					//m_gameState.changeState();
				}
			}
        }

        //glm::vec3 mouseRay = mousePicker.currentRay();
        //std::cout << "mouse Ray : " << mouseRay.x << ";" << mouseRay.y << ";" << mouseRay.z << std::endl;

        player.move(getCurrentTime());
        camera.lockOnPlayer(&player);

        masterRenderer.processEntity(&player);
        masterRenderer.processEntities(world.getChunks());
        masterRenderer.processGui(&gui);
        masterRenderer.render(camera);
        m_window->display();
    }
}

DisplayManager::~DisplayManager()
{
    delete m_window;
}

long DisplayManager::getCurrentTime()
{
    long t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return t;
}
