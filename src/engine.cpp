#include "engine.h"

#include <GLFW/glfw3.h>
#include <iostream>

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
                std::cout << "W pressed\n";
            if (key == GLFW_KEY_S && action == GLFW_PRESS)
                std::cout << "S pressed\n";
            if (key == GLFW_KEY_A && action == GLFW_PRESS)
                std::cout << "A pressed\n";
            if (key == GLFW_KEY_D && action == GLFW_PRESS)
                std::cout << "D pressed\n";
        });

        glfwPollEvents();
        renderer->draw();
        // std::cout << "drawed a frame\n";
    }
    renderer->device_wait_idle();
}

void Engine::deinit() {
    renderer->deinit();
    window->deinit();
}