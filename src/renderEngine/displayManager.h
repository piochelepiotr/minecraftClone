#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "loader.h"
#include "renderer.h"
#include "models/rawModel.h"

class DisplayManager
{
    public:
        DisplayManager(int width, int height, std::string title);
        ~DisplayManager();
        bool createDisplay();
        void mainLoop();

    private:
        void display();
        int m_width;
        int m_height;
        std::string m_title;
        glm::mat4 m_projection;
        glm::mat4 m_modelview;
        sf::Window *m_window;
        Loader m_loader;
        Renderer m_renderer;
};

#endif
