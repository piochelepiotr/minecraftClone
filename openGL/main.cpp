#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

sf::Window *m_window;

// Define some of the global variables we're using for this sample
GLuint program;
GLuint vao;

// This is the callback we'll be registering with GLFW for errors.
// It'll just print out the error to the STDERR stream.
void error_callback(int error, const char* description) {
  fputs(description, stderr);
}

// This is the callback we'll be registering with GLFW for keyboard handling.
// The only thing we're doing here is setting up the window to close when we press ESC
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

int main() {
  // Initialize GLFW, and if it fails to initialize for any reason, print it out to STDERR.

  sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 4;
    settings.minorVersion = 5;
  m_window = new sf::Window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

  m_window->setActive(true);
  glewExperimental=GL_TRUE;

  if(glewInit() != GLEW_OK)
  {
      std::cout << "error glew" << std::endl;
      return false;
  }
  bool running = true;
  while (running)
    {
        sf::Event event;
        while (m_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                glViewport(0, 0, event.size.width, event.size.height);
            }
        }
        m_window->display();
    }

  /*if (!glfwInit()) {
    fprintf(stderr, "Failed initialize GLFW.");
    exit(EXIT_FAILURE);
  }

  // Set the error callback, as mentioned above.
  glfwSetErrorCallback(error_callback);

  // Set up OpenGL options.
  // Use OpenGL verion 4.1,
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // GLFW_OPENGL_FORWARD_COMPAT specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed.
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Indicate we only want the newest core profile, rather than using backwards compatible and deprecated features.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // Make the window resize-able.
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  // Create a window to put our stuff in.
  GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);

  // If the window fails to be created, print out the error, clean up GLFW and exit the program.
  if(!window) {
    fprintf(stderr, "Failed to create GLFW window.");
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Use the window as the current context (everything that's drawn will be place in this window).
  glfwMakeContextCurrent(window);

  // Set the keyboard callback so that when we press ESC, it knows what to do.
  glfwSetKeyCallback(window, key_callback);

  printf("OpenGL version supported by this platform (%s): \n", glGetString(GL_VERSION));

  // Makes sure all extensions will be exposed in GLEW and initialize GLEW.
  glewExperimental = GL_TRUE;
  glewInit();


  // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
  while(!glfwWindowShouldClose(window))
  {
    // Set up our green background color
    static const GLfloat green[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    // Clear the entire buffer with our green color (sets the background to be green).
    glClearBufferfv(GL_COLOR, 0, green);

    // Draw our triangles

    glfwPollEvents();
  }*/

}
