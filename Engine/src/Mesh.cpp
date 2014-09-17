#include <Engine/Mesh.hpp>

engine::Mesh::Mesh(void)
	: _idColorTexture(0), _idNMTexture(0),
	_idVAO(0), _idVBO(0), _idIBO(0)
{
	glGenBuffers(1, &_idMaterialBuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, _idMaterialBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof _material, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
};

engine::Mesh::~Mesh(void)
{
	if (glIsTexture(_idColorTexture)) glDeleteTextures(1, &_idColorTexture);
	if (glIsTexture(_idNMTexture)) glDeleteTextures(1, &_idNMTexture);
	if (glIsVertexArray(_idVAO)) glDeleteVertexArrays(1, &_idVAO);
	if (glIsBuffer(_idVBO)) glDeleteBuffers(1, &_idVBO);
	if (glIsBuffer(_idIBO)) glDeleteBuffers(1, &_idIBO);
	glDeleteBuffers(1, &_idMaterialBuffer);
}

void engine::Mesh::setColorTexture(const GLuint &id)
{
	if (glIsTexture(_idColorTexture)) glDeleteTextures(1, &_idColorTexture);

	_idColorTexture = id;
}

void engine::Mesh::setNMTexture(const GLuint &id)
{
	if (glIsTexture(_idNMTexture)) glDeleteTextures(1, &_idNMTexture);

	_idNMTexture = id;
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
	if (glIsVertexArray(_idVAO)) glDeleteVertexArrays(1, &_idVAO);
	if (glIsBuffer(_idVBO)) glDeleteBuffers(1, &_idVBO);
	if (glIsBuffer(_idIBO)) glDeleteBuffers(1, &_idIBO);

	_numElement = sizeIndexArray/(GLsizei)sizeof(GLuint);

	// Vertex Array, Vertex Buffer Object and Index Buffer Object
	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);

	glGenBuffers(1, &_idVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _idVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeVertexArray, vertexArray, GL_STATIC_DRAW);

	glGenBuffers(1, &_idIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexArray, indexArray, GL_STATIC_DRAW);

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

void engine::Mesh::display(const GLint &colorTextureLocation, const GLint &nmTextureLocation, const GLuint &materialBlockIndex) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idColorTexture);
	glUniform1i(colorTextureLocation, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _idNMTexture);
	glUniform1i(nmTextureLocation, 1);
	
	updateDynamicBuffer(_idMaterialBuffer, &_material, sizeof _material);
	glBindBufferBase(GL_UNIFORM_BUFFER, materialBlockIndex, _idMaterialBuffer);

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void engine::Mesh::displayShadow(const GLint &colorLocation) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _idColorTexture);
	glUniform1i(colorLocation, 0);

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
