#include <Engine/SkeletalMesh.hpp>
#include <Engine/Buffer.hpp>

Engine::SkeletalMesh::SkeletalMesh(void)
{
}

Engine::SkeletalMesh::~SkeletalMesh(void)
{
}

void Engine::SkeletalMesh::load(const GLsizei &numVertex, const Vertex *vertexArray, const GLsizei &numIndex, const GLuint *indexArray)
{
	unsigned int stride = 27 * sizeof(GLfloat);

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
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glEnableVertexAttribArray(6);
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(5 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(8 * sizeof(GLfloat)));
	glVertexAttribPointer(4, 4, GL_INT, GL_FALSE, stride, BUFFER_OFFSET(11 * sizeof(GLfloat)));
	glVertexAttribPointer(5, 4, GL_INT, GL_FALSE, stride, BUFFER_OFFSET(15 * sizeof(GLfloat)));
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(19 * sizeof(GLfloat)));
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(23 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Engine::SkeletalMesh::load(std::vector<Vertex> vertices, std::vector<GLuint> indices)
{
	load((GLsizei)vertices.size(), vertices.data(), (GLsizei)indices.size(), indices.data());
}

Engine::MeshType Engine::SkeletalMesh::getType(void) const
{
	return SKELETAL_MESH;
}