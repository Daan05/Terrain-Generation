#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];

		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, unsigned int StartVertexAttribIndex)
{
	Bind();
	vb.Bind();

	glDisableVertexAttribArray(StartVertexAttribIndex + 0);
	glDisableVertexAttribArray(StartVertexAttribIndex + 1);
	glDisableVertexAttribArray(StartVertexAttribIndex + 2);
	glDisableVertexAttribArray(StartVertexAttribIndex + 3);

	glEnableVertexAttribArray(StartVertexAttribIndex + 0);
	glVertexAttribPointer(StartVertexAttribIndex + 0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(StartVertexAttribIndex + 1);
	glVertexAttribPointer(StartVertexAttribIndex + 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(1 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(StartVertexAttribIndex + 2);
	glVertexAttribPointer(StartVertexAttribIndex + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(StartVertexAttribIndex + 3);
	glVertexAttribPointer(StartVertexAttribIndex + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(StartVertexAttribIndex + 0, 1);
	glVertexAttribDivisor(StartVertexAttribIndex + 1, 1);
	glVertexAttribDivisor(StartVertexAttribIndex + 2, 1);
	glVertexAttribDivisor(StartVertexAttribIndex + 3, 1);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::Delete() const
{
	glDeleteVertexArrays(1, &m_RendererID);
}
