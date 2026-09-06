#include "Mesh.h"

#include <cstddef>



Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
	: vertices(vertices), indices(indices), m_vertexBuffer(vertices), m_elementBuffer(indices)
{
	m_vertexArray.Bind();

	m_vertexBuffer.Bind();
	m_elementBuffer.Bind();

	m_vertexArray.LinkAttrib(m_vertexBuffer, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
	m_vertexArray.LinkAttrib(m_vertexBuffer, 1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
	m_vertexArray.LinkAttrib(m_vertexBuffer, 2, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, color));
	m_vertexArray.LinkAttrib(m_vertexBuffer, 3, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, texUV));

	m_vertexArray.Unbind();
	m_vertexBuffer.Unbind();
}

void Mesh::Draw() const
{
	if (indices.empty())
		return;

	m_vertexArray.Bind();
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, nullptr);
	m_vertexArray.Unbind();
}
