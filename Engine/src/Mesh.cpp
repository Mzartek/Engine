#include <Engine/Mesh.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/TextureCube.hpp>
#include <Engine/Buffer.hpp>

Engine::Mesh::Mesh(void)
	: _numElement(0)
{
	_colorTexture = new Texture2D;
	_NMTexture = new Texture2D;
	_vertexBuffer = new Buffer;
	_indexBuffer = new Buffer;
	_materialBuffer = new Buffer;

	_materialBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _material, GL_DYNAMIC_DRAW);

	glGenVertexArrays(1, &_idVAO);
};

Engine::Mesh::~Mesh(void)
{
	delete _colorTexture;
	delete _NMTexture;
	delete _vertexBuffer;
	delete _indexBuffer;
	delete _materialBuffer;
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Mesh::loadColorTexture(const GLchar *path) const
{
	_colorTexture->loadFromFile(path);
}

void Engine::Mesh::loadNMTexture(const GLchar *path) const
{
	_NMTexture->loadFromFile(path);
}

void Engine::Mesh::setAmbient(const glm::vec4 &ambient)
{
	_material.ambient = ambient;
}

void Engine::Mesh::setDiffuse(const glm::vec4 &diffuse)
{
	_material.diffuse = diffuse;
}

void Engine::Mesh::setSpecular(const glm::vec4 &specular)
{
	_material.specular = specular;
}

void Engine::Mesh::setShininess(const GLfloat &shininess)
{
	_material.shininess = shininess;
}

GLfloat Engine::Mesh::getTransparency(void) const
{
	return _material.diffuse.w;
}

void Engine::Mesh::load(const GLsizei &numVertex, const Vertex *vertexArray,
	const GLsizei &numIndex, const GLuint *indexArray)
{
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(5 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), BUFFER_OFFSET(8 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

void Engine::Mesh::display(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _NMTexture->getId());

	_materialBuffer->updateStoreMap(&_material);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _materialBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::Mesh::display(TextureCube *cubeTexture) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _NMTexture->getId());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, cubeTexture->getId());

	_materialBuffer->updateStoreMap(&_material);
	glBindBufferBase(GL_UNIFORM_BUFFER, 2, _materialBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Engine::Mesh::displayShadow(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

bool Engine::CompareMesh::operator()(const Mesh *first, const Mesh *second)
{
	if (first->_material.diffuse.z > second->_material.diffuse.z)
		return true;
	return false;
}
