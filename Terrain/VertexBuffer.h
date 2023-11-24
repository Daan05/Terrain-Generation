#pragma once
#include <glad/glad.h>

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, bool isStatic);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void Delete() const;

	void UpdateData(const void* data, unsigned int size, bool isStatic);
};
