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
    Player player(vec3(0,17*Chunk::BLOCK_SIZE,0), &m_loader);

    MasterRenderer masterRenderer(m_width, m_height);

    bool running = true;
    while (running)
    {
        // gestion des évènements
        sf::Event event;
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
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }

        //entity.increasePosition(0, 0, -0.01);
        //entity.increaseRotation(0.00, 0.02, 0.00);
        //camera.move();
        player.move();
        camera.lockOnPlayer(&player);

        //masterRenderer.processEntity(&entity);
        masterRenderer.processEntity(&player);
        masterRenderer.processEntities(world.getBlocks());
        masterRenderer.render(light, camera);
        m_window->display();
    }
}

DisplayManager::~DisplayManager()
{
    delete m_window;
}
