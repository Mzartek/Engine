#include <Engine/Model.hpp>
#include <Engine/Mesh.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/ShaderProgram.hpp>
#include <Engine/GBuffer.hpp>
#include <Engine/PerspCamera.hpp>
#include <Engine/DirLight.hpp>
#include <Engine/SpotLight.hpp>
#include <Engine/DepthMap.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/TextureCube.hpp>
#include <Engine/Material.hpp>

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

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
	: _isMirror(GL_FALSE), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = new std::vector < Mesh * > ;
	_tObject = new std::vector < Object * > ;
	_matrixBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_position = new glm::vec3;
	_scale = new glm::vec3;
	_rotation = new glm::quat;
	_modelMatrix = new glm::mat4;
	_normalMatrix = new glm::mat4;

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
	: _isMirror(GL_TRUE), _needMatModel(GL_TRUE), _needMatNormal(GL_TRUE), _cubeTexture(NULL), _gProgram(gProgram), _smProgram(smProgram)
{
	_tMesh = model->_tMesh;
	_tObject = new std::vector < Object * > ;
	_matrixBuffer = new Buffer;
	_cameraBuffer = new Buffer;
	_position = new glm::vec3;
	_scale = new glm::vec3;
	_rotation = new glm::quat;
	_modelMatrix = new glm::mat4;
	_normalMatrix = new glm::mat4;

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
	if (!_isMirror) delete _tMesh;

	for (std::vector<Object *>::iterator it = _tObject->begin(); it != _tObject->end(); it++)
		delete *it;
	delete _tObject;

	delete _matrixBuffer;
	delete _cameraBuffer;
	delete _position;
	delete _scale;
	delete _rotation;
	delete _modelMatrix;
	delete _normalMatrix;
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
	*_rotation = glm::angleAxis(fmod(angle, glm::pi<GLfloat>() * 2), axis);
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
