#pragma once

#include "window.h"
#include "renderer/renderer.h"

struct Engine {
    Window* window = nullptr;
    Renderer* renderer = nullptr;

    void init();
    void loop();
    void deinit();
};