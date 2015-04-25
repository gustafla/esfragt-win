#include "gfx.h"
#include "esfragt.h"
#include "config.h"
#include <iostream>

void cleanup() {
    glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        exit(0);
}

int main (int argc, char* argv[]) {
    atexit(cleanup);

    if (!glfwInit()) {
        return -1;
    }
    Config* config = new Config(argc, argv);

    GLFWmonitor* primary = NULL;
    if (config->fullScreen)
        primary = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(config->w, config->h, "Esfragt4windows beta", primary, NULL);
    if (!window) {
        glfwTerminate();
        return -2;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetKeyCallback(window, key_callback);

    glewInit();

    glViewport(0, 0, config->w, config->h);

    Esfragt* esfragt = new Esfragt;
    float tLast = glfwGetTime();
    unsigned int frames = 0;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        esfragt->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
        if (config->fpsCounter) {
            frames++;
            if (frames > config->fpsIn) {
                std::cout << "FPS: " << (float(frames)/(glfwGetTime()-tLast)) << std::endl;
                tLast = glfwGetTime();
                frames=0;
            }
        }
    }
    delete config;
    delete esfragt;

    return 0;
}