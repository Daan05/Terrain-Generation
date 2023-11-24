#include "Renderer.h"

int main()
{
    // Renderer
    Renderer renderer(1280, 720);
    renderer.Loop();

    glfwTerminate();
    return 0;
}
