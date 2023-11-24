#include "Renderer.h"

Renderer::Renderer(unsigned int wWidth, unsigned int wHeight)
    : width(wWidth), height(wHeight)
{
    InitializeGLFW();
    InitializeGLAD();

    shader = new Shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader->use();

    terrain = new Terrain;
    camera = new Camera(width, height, glm::vec3(0.0f, 1.0f, -4.0f));
}

Renderer::~Renderer()
{
    delete terrain;
    terrain = NULL;

    delete shader;
    shader = NULL;
}

void Renderer::InitializeGLFW()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, "3D???", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwSetWindowShouldClose(window, true); // does this even work?
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0); // vsync off
}

void Renderer::InitializeGLAD()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Renderer::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    camera->Inputs(window);
}

void Renderer::Loop()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    std::chrono::steady_clock::time_point next_frame = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window))
    {
        next_frame += std::chrono::milliseconds(1000 / 144); // 144 fps??? when tested it's actually ~166?
        // input
        // -----
        processInput();

        // render
        // ------
        ClearScreen();

        camera->Matrix(60.f, 0.1f, 1000.f, shader);
        terrain->Render();

        // swap buffers
        // -----
        glfwSwapBuffers(window);
        glfwPollEvents();

        std::this_thread::sleep_until(next_frame);
    }
}

void Renderer::ClearScreen()
{
    glClearColor(0.2, 0.2, 0.2, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
