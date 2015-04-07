#include <Engine/Material.hpp>
#include <Engine/Texture2D.hpp>
#include <Engine/Buffer.hpp>

Engine::Material::Material(void)
	: _diffuseTexture(NULL), _specularTexture(NULL), _ambientTexture(NULL), _emissiveTexture(NULL), _shininessTexture(NULL),
	_opacityTexture(NULL), _bumpMap(NULL), _normalMap(NULL), _displacementMap(NULL), _lightMap(NULL)
{
	_matBuffer = new Buffer;
	_stateBuffer = new Buffer;

	_matBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _mat, GL_STATIC_DRAW);
	_stateBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _state, GL_STATIC_DRAW);

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

void Engine::Material::setbumpMap(Texture2D *map)
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

GLboolean Engine::Material::hasDiffuseTexture(void)
{
	return (GLboolean)_state.hasDiffuseTexture;
}

GLboolean Engine::Material::hasSpecularTexture(void)
{
	return (GLboolean)_state.hasSpecularTexture;
}

GLboolean Engine::Material::hasAmbientTexture(void)
{
	return (GLboolean)_state.hasAmbientTexture;
}

GLboolean Engine::Material::hasEmissiveTexture(void)
{
	return (GLboolean)_state.hasEmissiveTexture;
}

GLboolean Engine::Material::hasShininessTexture(void)
{
	return (GLboolean)_state.hasShininessTexture;
}

GLboolean Engine::Material::hasOpacityTexture(void)
{
	return (GLboolean)_state.hasOpacityTexture;
}

GLboolean Engine::Material::hasBumpMap(void)
{
	return (GLboolean)_state.hasBumpMap;
}

GLboolean Engine::Material::hasNormalMap(void)
{
	return (GLboolean)_state.hasNormalMap;
}

GLboolean Engine::Material::hasDisplacementMap(void)
{
	return (GLboolean)_state.hasDisplacementMap;
}

GLboolean Engine::Material::hasLightMap(void)
{
	return (GLboolean)_state.hasLightMap;
}

Engine::Texture2D *Engine::Material::getDiffuseTexture(void)
{
	return _diffuseTexture;
}

Engine::Texture2D *Engine::Material::getSpecularTexture(void)
{
	return _specularTexture;
}

Engine::Texture2D *Engine::Material::getAmbientTexture(void)
{
	return _ambientTexture;
}

Engine::Texture2D *Engine::Material::getEmissiveTexture(void)
{
	return _emissiveTexture;
}

Engine::Texture2D *Engine::Material::getShininessTexture(void)
{
	return _shininessTexture;
}

Engine::Texture2D *Engine::Material::getOpacityTexture(void)
{
	return _opacityTexture;
}

Engine::Texture2D *Engine::Material::getBumpMap(void)
{
	return _bumpMap;
}

Engine::Texture2D *Engine::Material::getNormalMap(void)
{
	return _normalMap;
}

Engine::Texture2D *Engine::Material::getDisplacementMap(void)
{
	return _displacementMap;
}

Engine::Texture2D *Engine::Material::getLightMap(void)
{
	return _lightMap;
}

GLuint Engine::Material::getMatBuffer(void)
{
	return _matBuffer->getId();
}

GLuint Engine::Material::getStateBuffer(void)
{
	return _stateBuffer->getId();
}