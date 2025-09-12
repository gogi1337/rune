#pragma once

#include <cstdint>
#include <GLFW/glfw3.h>

struct Window {
    uint32_t width;
    uint32_t height;
    GLFWwindow* inner = nullptr;

    void init_window();
    void loop();
    void deinit();
};