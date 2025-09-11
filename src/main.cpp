#include "renderer.h"

int main() {
    Renderer app;

    try {
        app.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "Error: %s\n", e.what());
        return 1;
    }

    return 0;
}
