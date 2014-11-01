#include <Engine/Mesh.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>

Engine::Mesh::Mesh(void)
{
	_colorTexture = new Texture;
	_NMTexture = new Texture;
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

void Engine::Mesh::setColorTexture(const GLchar *path)
{
	_colorTexture->load2DTextureFromFile(path);
}

void Engine::Mesh::setNMTexture(const GLchar *path)
{
	_NMTexture->load2DTextureFromFile(path);
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

GLfloat Engine::Mesh::getTransparency(void)
{
	return _material.diffuse.w;
}

void Engine::Mesh::load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
			  const GLsizei &sizeIndexArray, const GLuint *indexArray)
{
	_numElement = sizeIndexArray/sizeof(GLuint);

	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertexArray, sizeVertexArray, GL_STATIC_DRAW);
	_indexBuffer->createStore(GL_ELEMENT_ARRAY_BUFFER, indexArray, sizeIndexArray, GL_STATIC_DRAW);

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
}

void Engine::Mesh::display(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _NMTexture->getId());

	_materialBuffer->updateStoreMap(&_material);
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, _materialBuffer->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
}

void Engine::Mesh::displayShadow(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
}

int Engine::comparMesh(const void *p1, const void *p2)
{
	Mesh **obj1 = (Engine::Mesh **)p1;
	Mesh **obj2 = (Engine::Mesh **)p2;

	if ((*obj1)->_material.diffuse.w < (*obj2)->_material.diffuse.w)
		return 1;
	if ((*obj1)->_material.diffuse.w > (*obj2)->_material.diffuse.w)
		return -1;
	return 0;
}
