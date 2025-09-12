#include "window.h"
#include "const.h"

void Window::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    inner = glfwCreateWindow(rune::WIDTH, rune::HEIGHT, "Rune", nullptr, nullptr);
}

void Window::deinit() {
    glfwDestroyWindow(inner);
    glfwTerminate();
}