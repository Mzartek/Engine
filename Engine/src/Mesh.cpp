#include <Engine/Mesh.hpp>
#include <Engine/Texture.hpp>
#include <Engine/Buffer.hpp>

engine::Mesh::Mesh(void)
{
	_colorTexture = new Texture;
	_NMTexture = new Texture;
	glGenVertexArrays(1, &_idVAO);
	_vertexBuffer = new Buffer;
	_indexBuffer = new Buffer;
	_materialBuffer = new Buffer;

	_materialBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _material, GL_DYNAMIC_DRAW);
};

engine::Mesh::~Mesh(void)
{
	delete _colorTexture;
	delete _NMTexture;
	glDeleteVertexArrays(1, &_idVAO);
	delete _vertexBuffer;
	delete _indexBuffer;
	delete _materialBuffer;
}

void engine::Mesh::setColorTexture(const GLchar *path)
{
	_colorTexture->load2DTextureFromFile(path);
}

void engine::Mesh::setNMTexture(const GLchar *path)
{
	_NMTexture->load2DTextureFromFile(path);
}

void engine::Mesh::setAmbient(const glm::vec4 &ambient)
{
	_material.ambient = ambient;
}

void engine::Mesh::setDiffuse(const glm::vec4 &diffuse)
{
	_material.diffuse = diffuse;
}

void engine::Mesh::setSpecular(const glm::vec4 &specular)
{
	_material.specular = specular;
}

void engine::Mesh::setShininess(const GLfloat &shininess)
{
	_material.shininess = shininess;
}

GLfloat engine::Mesh::getTransparency(void)
{
	return _material.diffuse.w;
}

#define BUFFER_OFFSET(i) ((GLbyte *)NULL + i)

void engine::Mesh::load(const GLsizei &sizeVertexArray, const GLfloat *vertexArray,
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
	glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Mesh::display(void) const
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

void engine::Mesh::displayShadow(void) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _colorTexture->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

int engine::comparMesh(const void *p1, const void *p2)
{
	Mesh **obj1 = (engine::Mesh **)p1;
	Mesh **obj2 = (engine::Mesh **)p2;

	if ((*obj1)->_material.diffuse.w < (*obj2)->_material.diffuse.w)
		return 1;
	if ((*obj1)->_material.diffuse.w > (*obj2)->_material.diffuse.w)
		return -1;
	return 0;
}
