#include <Engine/Graphics/Model.hpp>

void Engine::Model::genMatModel(void) const
{
	*_modelMatrix =
		glm::translate(*_position) *
		glm::toMat4(*_rotation) *
		glm::scale(*_scale);
}

void Engine::Model::genMatNormal(void) const
{
	*_normalMatrix = glm::transpose(glm::inverse(*_modelMatrix));
}

void Engine::Model::checkMatrix(void)
{
	if (_needMatModel == GL_TRUE)
	{
		genMatModel();
		_needMatModel = GL_FALSE;
	}
	if (_needMatNormal == GL_TRUE)
	{
		genMatNormal();
		_needMatNormal = GL_FALSE;
	}
}

Engine::Model::Model(ShaderProgram *gProgram, ShaderProgram *smProgram)
	: _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _isMirror(GL_FALSE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = new_ptr(std::vector < Mesh * >);
	_matrixBuffer = new_ptr(Buffer);
	_cameraBuffer = new_ptr(Buffer);
	_position = new_ptr(glm::vec3);
	_scale = new_ptr(glm::vec3);
	_rotation = new_ptr(glm::quat);
	_modelMatrix = new_ptr(glm::mat4);
	_normalMatrix = new_ptr(glm::mat4);

	*_position = glm::vec3(0, 0, 0);
	*_scale = glm::vec3(1, 1, 1);

	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _camera, GL_DYNAMIC_DRAW);

	glUseProgram(_gProgram->getId());
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "specularTex"), 1);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "ambiantTex"), 2);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "emissiveTex"), 3);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "shininessTex"), 4);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "opacityTex"), 5);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "bumpMap"), 6);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "normalMap"), 7);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "displacementMap"), 8);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "lightMap"), 9);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "reflectionTex"), 10);
	glUseProgram(_smProgram->getId());
	glUniform1i(glGetUniformLocation(_smProgram->getId(), "diffuseTex"), 0);
}

Engine::Model::Model(Model *model, ShaderProgram *gProgram, ShaderProgram *smProgram)
	: _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _isMirror(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = model->_tMesh;
	_matrixBuffer = new_ptr(Buffer);
	_cameraBuffer = new_ptr(Buffer);
	_position = new_ptr(glm::vec3);
	_scale = new_ptr(glm::vec3);
	_rotation = new_ptr(glm::quat);
	_modelMatrix = new_ptr(glm::mat4);
	_normalMatrix = new_ptr(glm::mat4);

	*_position = glm::vec3(0, 0, 0);
	*_scale = glm::vec3(1, 1, 1);

	_cameraBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _camera, GL_DYNAMIC_DRAW);

	glUseProgram(_gProgram->getId());
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "specularTex"), 1);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "ambiantTex"), 2);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "emissiveTex"), 3);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "shininessTex"), 4);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "opacityTex"), 5);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "bumpMap"), 6);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "normalMap"), 7);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "displacementMap"), 8);
	glUniform1i(glGetUniformLocation(_gProgram->getId(), "lightMap"), 9);
	glUseProgram(_smProgram->getId());
	glUniform1i(glGetUniformLocation(_smProgram->getId(), "diffuseTex"), 0);
}

Engine::Model::~Model(void)
{
	if (!_isMirror) release_ptr(_tMesh);

	release_ptr(_matrixBuffer);
	release_ptr(_cameraBuffer);
	release_ptr(_position);
	release_ptr(_scale);
	release_ptr(_rotation);
	release_ptr(_modelMatrix);
	release_ptr(_normalMatrix);
}

void Engine::Model::addMesh(Mesh *mesh)
{
	if (_isMirror == GL_TRUE)
	{
		std::cerr << "Error Model configuration" << std::endl;
		abort();
	}

	_tMesh->push_back(mesh);
}

void Engine::Model::sortMesh(void)
{
	std::sort(_tMesh->begin(), _tMesh->end(), CompareMesh());
}

void Engine::Model::setPosition(const glm::vec3 &position)
{
	*_position = position;
	_needMatModel = GL_TRUE;
}

void Engine::Model::setScale(const glm::vec3 &scale)
{
	*_scale = scale;
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setRotation(const glm::vec3 &rotation)
{
	*_rotation = glm::quat(rotation);
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setRotation(const glm::vec3 &axis, const GLfloat &angle)
{
	*_rotation = glm::angleAxis(fmodf(angle, glm::pi<GLfloat>() * 2), axis);
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setCubeTexture(TextureCube *cubeTexture)
{
	_cubeTexture = cubeTexture;
}

glm::vec3 Engine::Model::getPosition(void) const
{
	return *_position;
}

glm::vec3 Engine::Model::getScale(void) const
{
	return *_scale;
}

std::pair<glm::vec3, GLfloat> Engine::Model::getAxisAngleRotation(void) const
{
	return std::pair<glm::vec3, GLfloat>(glm::axis(*_rotation), glm::angle(*_rotation));
}

Engine::Mesh *Engine::Model::getMesh(const GLuint &num) const
{
	if (num >= _tMesh->size())
	{
		std::cerr << "Bad num Mesh" << std::endl;
		return NULL;
	}
	return (*_tMesh)[num];
}
