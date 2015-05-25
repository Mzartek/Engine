#include <Engine/Graphics/SkyBox.hpp>

Engine::Graphics::SkyBox::SkyBox(const std::shared_ptr<ShaderProgram> &program)
	: _program(program)
{
	_cubeTexture = std::shared_ptr<TextureCube>(new TextureCube);
	_vertexBuffer = std::shared_ptr<Buffer>(new Buffer);
	_indexBuffer = std::shared_ptr<Buffer>(new Buffer);
	_MVPMatrixBuffer = std::shared_ptr<Buffer>(new Buffer);

	GLfloat vertexArray[] =
	{
		+SKYBOX_DIM, -SKYBOX_DIM, -SKYBOX_DIM,
		-SKYBOX_DIM, -SKYBOX_DIM, -SKYBOX_DIM,
		-SKYBOX_DIM, -SKYBOX_DIM, +SKYBOX_DIM,
		+SKYBOX_DIM, -SKYBOX_DIM, +SKYBOX_DIM,
		+SKYBOX_DIM, +SKYBOX_DIM, -SKYBOX_DIM,
		-SKYBOX_DIM, +SKYBOX_DIM, -SKYBOX_DIM,
		-SKYBOX_DIM, +SKYBOX_DIM, +SKYBOX_DIM,
		+SKYBOX_DIM, +SKYBOX_DIM, +SKYBOX_DIM
	};
	GLuint indexArray[] =
	{
		0, 1, 2, 0, 2, 3,
		4, 7, 6, 4, 6, 5,
		0, 4, 5, 0, 5, 1,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		0, 3, 7, 0, 7, 4
	};
	_numElement = sizeof indexArray / sizeof(GLuint);
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertexArray, sizeof vertexArray, GL_STATIC_DRAW);
	_indexBuffer->createStore(GL_ELEMENT_ARRAY_BUFFER, indexArray, sizeof indexArray, GL_STATIC_DRAW);
	_MVPMatrixBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof(glm::mat4), GL_DYNAMIC_DRAW);

	glUseProgram(_program->getId());
	glUniform1i(glGetUniformLocation(_program->getId(), "cubeMap"), 0);

	glGenVertexArrays(1, &_idVAO);
	glBindVertexArray(_idVAO);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer->getId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer->getId());
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GLsizei(3 * sizeof(GLfloat)), BUFFER_OFFSET(0));
	glBindVertexArray(0);
}

Engine::Graphics::SkyBox::~SkyBox(void)
{
	glDeleteVertexArrays(1, &_idVAO);
}

void Engine::Graphics::SkyBox::load(const GLchar *posx, const GLchar *negx,
	const GLchar *posy, const GLchar *negy,
	const GLchar *posz, const GLchar *negz) const
{
	_cubeTexture->loadFromFiles(posx, negx, posy, negy, posz, negz);
}

const std::shared_ptr<Engine::Graphics::TextureCube> &Engine::Graphics::SkyBox::getTexture(void) const
{
	return _cubeTexture;
}

void Engine::Graphics::SkyBox::display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam) const
{
	glm::mat4 pos = cam->getVPMatrix() * glm::translate(cam->getCameraPosition());

	gbuf->setSkyboxState();

	glUseProgram(_program->getId());

	_MVPMatrixBuffer->updateStoreMap(glm::value_ptr(pos));
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _MVPMatrixBuffer->getId());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeTexture->getId());

	glBindVertexArray(_idVAO);
	glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
