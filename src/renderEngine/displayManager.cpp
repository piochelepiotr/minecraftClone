#include "displayManager.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "shaders/shaderProgram.h"
#include "textures/modelTexture.h"
#include "shaders/staticShader.h"

using namespace glm;

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

    m_window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
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
    float vertices [] = {
        -0.5, 0.5, 0,
        -0.5, -0.5, 0,
        0.5, -0.5, 0,
        0.5, 0.5, 0
    };

    float texCoo [] = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    int indices [] = {
        0, 1, 2,
        0, 2, 3,
    };
    RawModel *rawModel = m_loader.loadToVao(vertices, 12,texCoo, 8, indices, 6);
    StaticShader shader;
    ModelTexture texture(m_loader.loadTexture("textures/grass.png"));
    TexturedModel texturedModel(rawModel, &texture);

    Entity entity(vec3(-1,0,0),&texturedModel, 0.0, 0.0, 0.0, 1.0);

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

        m_renderer.prepare();
        shader.start();
        m_renderer.render(&entity, shader);
        shader.stop();

        m_window->display();
    }

    //delete rawModel;
}

void DisplayManager::display()
{
    m_modelview = lookAt(vec3(2, 2, 2), vec3(0, 0, 0), vec3(0, 1, 0));
}

DisplayManager::~DisplayManager()
{
    if(m_window)
        delete m_window;
}
