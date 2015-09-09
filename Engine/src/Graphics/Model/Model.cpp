#include <Engine/Graphics/Model/Model.hpp>

void Engine::Graphics::Model::checkMatrix(void)
{
	if (_needMatrix == GL_TRUE)
	{
		_matrix.model = glm::translate(_position) * glm::toMat4(_rotation) * glm::scale(_scale);
		_matrix.normal = glm::inverseTranspose(_matrix.model);
		_needMatrix = GL_FALSE;
	}
}

Engine::Graphics::Model::Model(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: _needMatrix(GL_TRUE), _isMirror(GL_FALSE), _cubeTexture(nullptr), _gProgram(gProgram), _smProgram(smProgram)
{
	_position = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_rotation = glm::quat();

	_tMesh = std::make_shared<std::vector<std::shared_ptr<Mesh>>>();
	_matrixBuffer = std::make_shared<Buffer>();

	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, nullptr, sizeof _matrix, GL_DYNAMIC_DRAW);

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

Engine::Graphics::Model::Model(const std::shared_ptr<Model> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram)
	: _needMatrix(GL_TRUE), _isMirror(GL_TRUE), _cubeTexture(nullptr), _gProgram(gProgram), _smProgram(smProgram)
{
	_position = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1, 1, 1);
	_rotation = glm::quat();

	_tMesh = model->_tMesh;

	_matrixBuffer = std::make_shared<Buffer>();
	_matrixBuffer->createStore(GL_UNIFORM_BUFFER, nullptr, sizeof _matrix, GL_DYNAMIC_DRAW);

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

Engine::Graphics::Model::~Model(void)
{
}

void Engine::Graphics::Model::addMesh(const std::shared_ptr<Mesh> &mesh)
{
	if (_isMirror == GL_TRUE)
	{
		throw std::exception("Error Model configuration");
	}

	_tMesh->push_back(mesh);
}

void Engine::Graphics::Model::sortMesh(void)
{
	std::sort(_tMesh->begin(), _tMesh->end(), CompareMesh());
}

void Engine::Graphics::Model::setPosition(const glm::vec3 &position)
{
	_position = position;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::setScale(const glm::vec3 &scale)
{
	_scale = scale;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::setRotation(const glm::vec3 &rotation)
{
	_rotation = glm::quat(rotation);
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::setRotation(const glm::vec3 &axis, GLfloat angle)
{
	_rotation = glm::angleAxis(fmodf(angle, glm::pi<GLfloat>() * 2), axis);
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::addPosition(const glm::vec3 &position)
{
	_position += position;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::addScale(const glm::vec3 &scale)
{
	_scale += scale;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::addRotation(const glm::vec3 &rotation)
{
	_rotation = glm::quat(rotation) * _rotation;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::addRotation(const glm::vec3 &axis, GLfloat angle)
{
	_rotation = glm::angleAxis(fmodf(angle, glm::pi<GLfloat>() * 2), axis) * _rotation;
	_needMatrix = GL_TRUE;
}

void Engine::Graphics::Model::setCubeTexture(const std::shared_ptr<TextureCube> &cubeTexture)
{
	_cubeTexture = cubeTexture;
}

const glm::vec3 &Engine::Graphics::Model::getPosition(void) const
{
	return _position;
}

const glm::vec3 &Engine::Graphics::Model::getScale(void) const
{
	return _scale;
}

std::pair<const glm::vec3 &, GLfloat> Engine::Graphics::Model::getAxisAngleRotation(void) const
{
	return std::pair<const glm::vec3 &, GLfloat>(glm::vec3(glm::axis(_rotation)), glm::angle(_rotation));
}

const std::shared_ptr<Engine::Graphics::Mesh> &Engine::Graphics::Model::getMesh(GLuint num) const
{
	if (num >= _tMesh->size())
	{
		throw std::invalid_argument("Bad num Mesh");
	}
	return (*_tMesh)[num];
}
