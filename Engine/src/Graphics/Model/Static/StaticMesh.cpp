#include <Engine/Graphics/Model/Static/StaticMesh.hpp>

Engine::Graphics::StaticMesh::StaticMesh(void)
{
}

Engine::Graphics::StaticMesh::~StaticMesh(void)
{
}

void Engine::Graphics::StaticMesh::load(GLsizei numVertex, const Vertex *vertexArray, GLsizei numIndex, const GLuint *indexArray)
{
	unsigned int stride = 11 * sizeof(GLfloat);

	_numElement = numIndex;

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertexArray, numVertex * sizeof *vertexArray, GL_STATIC_DRAW);
	_indexBuffer->createStore(GL_ELEMENT_ARRAY_BUFFER, indexArray, numIndex * sizeof *indexArray, GL_STATIC_DRAW);

	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getId());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(5 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(8 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Engine::Graphics::StaticMesh::load(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices)
{
	load((GLsizei)vertices.size(), vertices.data(), (GLsizei)indices.size(), indices.data());
}

Engine::Graphics::MeshType Engine::Graphics::StaticMesh::getType(void) const
{
	return STATIC_MESH;
}