#pragma once
#include <glad/glad.h>

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <cmath>

#include <iostream>

class VertexArray
{
private:
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int StartVertexAttribIndex);

	void Bind() const;
	void Unbind() const;
	void Delete() const;
};
