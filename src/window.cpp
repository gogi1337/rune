#include <stdexcept>
#include <vulkan/vulkan.h>

#include "window.h"
#include "const.h"

void Window::init_window() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    inner = glfwCreateWindow(rune::WIDTH, rune::HEIGHT, "Rune", nullptr, nullptr);
}

void Window::create_surface(VkInstance instance, VkSurfaceKHR *surface) {
    if (glfwCreateWindowSurface(instance, inner, nullptr, surface) != VK_SUCCESS)
        throw std::runtime_error("failed to create window surface!");
}

void Window::deinit() {
    glfwDestroyWindow(inner);
    glfwTerminate();
}