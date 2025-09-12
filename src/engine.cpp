#include <GLFW/glfw3.h>

#include "engine.h"

void Engine::init() {
    window = new Window();
    renderer = new Renderer();
    
    window->init_window();
    renderer->init_renderer(window);
    loop();
    deinit();
}

void Engine::loop() {
    while (!glfwWindowShouldClose(window->inner)) {
        glfwSetKeyCallback(window->inner, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);

            if (key == GLFW_KEY_W && action == GLFW_PRESS)
                std::cout << "W pressed!" << std::endl;
        });

        glfwPollEvents();
        renderer->draw();
    }
    renderer->device_wait_idle();
}

void Engine::deinit() {
    renderer->deinit();
    window->deinit();
}