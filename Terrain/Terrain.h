#pragma once
#include <vector>

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class Terrain
{
public:
    Terrain();
    ~Terrain();

    void Render();
private:

    // VAO, EBO and VBO
    VertexArray* vao;
    IndexBuffer* ebo;
    VertexBuffer* vbo;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};

std::vector<float> GenVertices();
std::vector<unsigned int> GenIndices(int x, int y);
std::vector<float> GenHeightMap(int x_, int y_);

glm::vec2 randomGradient(int ix, int iy);
float dotGridGradient(int ix, int iy, float x, float y);
float interpolate(float a0, float a1, float w);
float perlin(float x, float y);
