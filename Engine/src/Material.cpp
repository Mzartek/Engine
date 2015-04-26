#include <Engine/Material.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/Buffer.hpp>

Engine::Material::Material(void)
	: _diffuseTexture(NULL), _specularTexture(NULL), _ambientTexture(NULL), _emissiveTexture(NULL), _shininessTexture(NULL),
	_opacityTexture(NULL), _bumpMap(NULL), _normalMap(NULL), _displacementMap(NULL), _lightMap(NULL)
{
	_matBuffer = new Buffer;
	_stateBuffer = new Buffer;

	_mat.diffuse = glm::vec3(0.0f, 0.0f, 0.0f);
	_mat.specular = glm::vec3(0.0f, 0.0f, 0.0f);
    _mat.ambient = glm::vec3(0.0f, 0.0f, 0.0f);
    _mat.emissive = glm::vec3(0.0f, 0.0f, 0.0f);
    _mat.shininess = 1.0f;
    _mat.opacity = 1.0f;
	_matBuffer->createStore(GL_UNIFORM_BUFFER, &_mat, sizeof _mat, GL_STATIC_DRAW);

	_state.hasDiffuseTexture = GL_FALSE;
	_state.hasSpecularTexture = GL_FALSE;
	_state.hasAmbientTexture = GL_FALSE;
	_state.hasEmissiveTexture = GL_FALSE;
	_state.hasShininessTexture = GL_FALSE;
	_state.hasOpacityTexture = GL_FALSE;
	_state.hasBumpMap = GL_FALSE;
	_state.hasNormalMap = GL_FALSE;
	_state.hasDisplacementMap = GL_FALSE;
	_state.hasLightMap = GL_FALSE;
	_stateBuffer->createStore(GL_UNIFORM_BUFFER, &_state, sizeof _state, GL_STATIC_DRAW);
}

Engine::Material::~Material(void)
{
	delete _matBuffer;
	delete _stateBuffer;
}

void Engine::Material::setDiffuse(const glm::vec3 &color)
{
	_mat.diffuse = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setSpecular(const glm::vec3 &color)
{
	_mat.specular = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setAmbient(const glm::vec3 &color)
{
	_mat.ambient = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setEmissive(const glm::vec3 &color)
{
	_mat.emissive = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setShininess(const GLfloat &shininess)
{
	_mat.shininess = shininess;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setOpacity(const GLfloat &opacity)
{
	_mat.opacity = opacity;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Material::setDiffuseTexture(Texture2D *tex)
{
	_diffuseTexture = tex;

	if (_diffuseTexture)
		_state.hasDiffuseTexture = GL_TRUE;
	else
		_state.hasDiffuseTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setSpecularTexture(Texture2D *tex)
{
	_specularTexture = tex;

	if (_diffuseTexture)
		_state.hasSpecularTexture = GL_TRUE;
	else
		_state.hasSpecularTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setAmbientTexture(Texture2D *tex)
{
	_ambientTexture = tex;

	if (_diffuseTexture)
		_state.hasAmbientTexture = GL_TRUE;
	else
		_state.hasAmbientTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setEmissiveTexture(Texture2D *tex)
{
	_emissiveTexture = tex;

	if (_diffuseTexture)
		_state.hasEmissiveTexture = GL_TRUE;
	else
		_state.hasEmissiveTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setShininessTexture(Texture2D *tex)
{
	_shininessTexture = tex;

	if (_diffuseTexture)
		_state.hasShininessTexture = GL_TRUE;
	else
		_state.hasShininessTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setOpacityTexture(Texture2D *tex)
{
	_opacityTexture = tex;

	if (_diffuseTexture)
		_state.hasOpacityTexture = GL_TRUE;
	else
		_state.hasOpacityTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setBumpMap(Texture2D *map)
{
	_bumpMap = map;

	if (_diffuseTexture)
		_state.hasBumpMap = GL_TRUE;
	else
		_state.hasBumpMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setNormalMap(Texture2D *map)
{
	_normalMap = map;

	if (_diffuseTexture)
		_state.hasNormalMap = GL_TRUE;
	else
		_state.hasNormalMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setDisplacementMap(Texture2D *map)
{
	_displacementMap = map;

	if (_diffuseTexture)
		_state.hasDisplacementMap = GL_TRUE;
	else
		_state.hasDisplacementMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Material::setLightMap(Texture2D *map)
{
	_lightMap = map;

	if (_diffuseTexture)
		_state.hasLightMap = GL_TRUE;
	else
		_state.hasLightMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

glm::vec3 Engine::Material::getDiffuse(void) const
{
	return _mat.diffuse;
}

glm::vec3 Engine::Material::getSpecular(void) const
{
	return _mat.specular;
}

glm::vec3 Engine::Material::getAmbient(void) const
{
	return _mat.ambient;
}

glm::vec3 Engine::Material::getEmissive(void) const
{
	return _mat.emissive;
}

GLfloat Engine::Material::getShininess(void) const
{
	return _mat.shininess;
}

GLfloat Engine::Material::getOpacity(void) const
{
	return _mat.opacity;
}

Engine::Texture2D *Engine::Material::getDiffuseTexture(void) const
{
	return _diffuseTexture;
}

Engine::Texture2D *Engine::Material::getSpecularTexture(void) const
{
	return _specularTexture;
}

Engine::Texture2D *Engine::Material::getAmbientTexture(void) const
{
	return _ambientTexture;
}

Engine::Texture2D *Engine::Material::getEmissiveTexture(void) const
{
	return _emissiveTexture;
}

Engine::Texture2D *Engine::Material::getShininessTexture(void) const
{
	return _shininessTexture;
}

Engine::Texture2D *Engine::Material::getOpacityTexture(void) const
{
	return _opacityTexture;
}

Engine::Texture2D *Engine::Material::getBumpMap(void) const
{
	return _bumpMap;
}

Engine::Texture2D *Engine::Material::getNormalMap(void) const
{
	return _normalMap;
}

Engine::Texture2D *Engine::Material::getDisplacementMap(void) const
{
	return _displacementMap;
}

Engine::Texture2D *Engine::Material::getLightMap(void) const
{
	return _lightMap;
}

GLboolean Engine::Material::hasDiffuseTexture(void) const
{
	return (GLboolean)_state.hasDiffuseTexture;
}

GLboolean Engine::Material::hasSpecularTexture(void) const
{
	return (GLboolean)_state.hasSpecularTexture;
}

GLboolean Engine::Material::hasAmbientTexture(void) const
{
	return (GLboolean)_state.hasAmbientTexture;
}

GLboolean Engine::Material::hasEmissiveTexture(void) const
{
	return (GLboolean)_state.hasEmissiveTexture;
}

GLboolean Engine::Material::hasShininessTexture(void) const
{
	return (GLboolean)_state.hasShininessTexture;
}

GLboolean Engine::Material::hasOpacityTexture(void) const
{
	return (GLboolean)_state.hasOpacityTexture;
}

GLboolean Engine::Material::hasBumpMap(void) const
{
	return (GLboolean)_state.hasBumpMap;
}

GLboolean Engine::Material::hasNormalMap(void) const
{
	return (GLboolean)_state.hasNormalMap;
}

GLboolean Engine::Material::hasDisplacementMap(void) const
{
	return (GLboolean)_state.hasDisplacementMap;
}

GLboolean Engine::Material::hasLightMap(void) const
{
	return (GLboolean)_state.hasLightMap;
}

GLuint Engine::Material::getMatBuffer(void) const
{
	return _matBuffer->getId();
}

GLuint Engine::Material::getStateBuffer(void) const
{
	return _stateBuffer->getId();
}
