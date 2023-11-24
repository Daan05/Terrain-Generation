#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <iostream>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include <ctime>

#include "Terrain.h"
#include "Camera.h"

#include "ShaderClass.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


class Renderer
{
public:
	Renderer(unsigned int wWidth, unsigned int wHeight);
	~Renderer();

	void Loop();
private:
	void InitializeGLFW();
	void InitializeGLAD();

	void processInput();

	void ClearScreen();

	// -------------------

	unsigned int width;
	unsigned height;

	GLFWwindow* window;
	Terrain* terrain;
	Camera* camera;

	Shader* shader;
};
