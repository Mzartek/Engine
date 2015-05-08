#include <Engine/Graphics/Model.hpp>

void Engine::Model::genMatModel(void)
{
	_modelMatrix =
		glm::translate(_position) *
		glm::toMat4(_rotation) *
		glm::scale(_scale);
}

void Engine::Model::genMatNormal(void)
{
	_normalMatrix = glm::transpose(glm::inverse(_modelMatrix));
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

Engine::Model::Model(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _isMirror(GL_FALSE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_position = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_rotation = glm::quat();

	_tMesh = new std::vector < std::shared_ptr<Mesh> > ;
	_matrixBuffer = std::shared_ptr<Buffer>(new Buffer);
	_cameraBuffer = std::shared_ptr<Buffer>(new Buffer);

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

Engine::Model::Model(const std::shared_ptr<Model> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _isMirror(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_position = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_rotation = glm::quat();

	_tMesh = model->_tMesh;
	_matrixBuffer = std::shared_ptr<Buffer>(new Buffer);
	_cameraBuffer = std::shared_ptr<Buffer>(new Buffer);

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
	if (!_isMirror) delete _tMesh;
}

void Engine::Model::addMesh(const std::shared_ptr<Mesh> &mesh)
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
	_position = position;
	_needMatModel = GL_TRUE;
}

void Engine::Model::setScale(const glm::vec3 &scale)
{
	_scale = scale;
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setRotation(const glm::vec3 &rotation)
{
	_rotation = glm::quat(rotation);
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setRotation(const glm::vec3 &axis, GLfloat angle)
{
	_rotation = glm::angleAxis(fmodf(angle, glm::pi<GLfloat>() * 2), axis);
	_needMatModel = GL_TRUE;
	_needMatNormal = GL_TRUE;
}

void Engine::Model::setCubeTexture(const std::shared_ptr<TextureCube> &cubeTexture)
{
	_cubeTexture = cubeTexture;
}

const glm::vec3 &Engine::Model::getPosition(void) const
{
	return _position;
}

const glm::vec3 &Engine::Model::getScale(void) const
{
	return _scale;
}

std::pair<const glm::vec3 &, GLfloat> Engine::Model::getAxisAngleRotation(void) const
{
	return std::pair<const glm::vec3 &, GLfloat>(glm::vec3(glm::axis(_rotation)), glm::angle(_rotation));
}

const std::shared_ptr<Engine::Mesh> &Engine::Model::getMesh(GLuint num) const
{
	if (num >= _tMesh->size())
	{
		std::cerr << "Bad num Mesh" << std::endl;
		abort();
	}
	return (*_tMesh)[num];
}
