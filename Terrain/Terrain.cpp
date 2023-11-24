#include "Terrain.h"

Terrain::Terrain()
{
    vertices = GenVertices();
    indices = GenIndices(5001, 5001);
    //std::cout << vertices.size() << " " << indices.size() << "\n";

    vao = new VertexArray;
    ebo = new IndexBuffer(indices.data(), indices.size());

    vao->Bind();
    ebo->Bind();

    vbo = new VertexBuffer(vertices.data(), sizeof(float) * vertices.size(), 1);  // Static
    std::cout << indices.size() << " " << vertices.size() << "\n";

    VertexBufferLayout layout1;
    layout1.Push<float>(3);  // positions
    layout1.Push<float>(3);  // colors
    vao->AddBuffer(*vbo, layout1);
}

Terrain::~Terrain()
{
    // VAO, EBO and VBO
    delete vao;
    vao = NULL;
    delete ebo;
    ebo = NULL;
    delete vbo;
    vbo = NULL;
}

void Terrain::Render()
{
    vao->Bind();
    ebo->Bind();
    vbo->Bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (const void*)0);
}

std::vector<float> GenVertices()
{
    std::vector<float> vertices;
    std::vector<float> height = GenHeightMap(5001, 5001);
    int index = 0;
    // this will be the ground
    float minX = -2500.0;
    float maxX = 2500.0;
    float minZ = -2500.0;
    float maxZ = 2500.0;

    float size = 1.0;
    float width = maxX - minX;

    for (float i = minZ; i <= maxZ; i += size)
    {
        for (float j = minX; j <= maxX; j += size)
        {
            // position
            vertices.push_back(j);                          // x
            vertices.push_back(height[index]);              // y
            vertices.push_back(i);                          // z

            // color
            vertices.push_back(height[index] * 0.01 + 0.5); // r
            vertices.push_back(height[index] * 0.01 + 0.5); // g
            vertices.push_back(height[index] * 0.01 + 0.5); // b

            index++;
        }
    }

    return vertices;
}

std::vector<unsigned int> GenIndices(int x, int y)
{
    std::vector<unsigned int> indices;

    for (int i = 0; i < y - 1; i++)
    {
        for (int j = 0; j < x - 1; j++)
        {
            indices.push_back(i * y + j);
            indices.push_back(i * y + j + 1);
            indices.push_back((i + 1) * y + j);

            indices.push_back((i + 1) * y + j + 1);
            indices.push_back(i * y + j + 1);
            indices.push_back((i + 1) * y + j);
        }
    }

    return indices;
}

std::vector<float> GenHeightMap(int x_, int y_)
{
    std::vector<float> map;
    const int width = x_;
    const int height = y_;

    const int GRID_SIZE = 400;


    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            int index = (y * width + x) * 4;


            float val = 0;

            float freq = 1.2f;
            float amp = 2.0f;

            for (int i = 0; i < 12; i++)
            {
                val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;

                freq *= 2;
                amp /= 2;

            }

            val *= 5;

            map.push_back(val);
        }
    }
    return map;
}

glm::vec2 randomGradient(int ix, int iy)
{
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;

    b ^= a << s | a >> w - s;
    b *= 1911520717;

    a ^= b << s | b >> w - s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]

    // Create the vector from the angle
    glm::vec2 v;
    v.x = sin(random);
    v.y = cos(random);

    return v;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    glm::vec2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx * gradient.x + dy * gradient.y);
}

float interpolate(float a0, float a1, float w)
{
    return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}


// Sample Perlin noise at coordinates x, y
float perlin(float x, float y) {

    // Determine grid cell corner coordinates
    int x0 = (int)x;
    int y0 = (int)y;
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    // Compute Interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Compute and interpolate top two corners
    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = interpolate(n0, n1, sx);

    // Compute and interpolate bottom two corners
    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = interpolate(n0, n1, sx);

    // Final step: interpolate between the two previously interpolated values, now in y
    float value = interpolate(ix0, ix1, sy);

    return value * 8;
}
