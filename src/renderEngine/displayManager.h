#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Window.hpp>
#include "loader.h"
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SFML/OpenGL.hpp>
#include "renderer.h"
#include "models/rawModel.h"
#include "shaders/staticShader.h"
#include "game/gameState.h"


class DisplayManager
{
    public:
        DisplayManager(int width, int height, std::string title);
        ~DisplayManager();
        bool createDisplay();
        void mainLoop();

    private:
        long getCurrentTime();
        int m_width;
        int m_height;
        std::string m_title;
        glm::mat4 m_projection;
        glm::mat4 m_modelview;
        sf::Window *m_window;
        Loader m_loader;
		GameState m_gameState;
};

#endif
