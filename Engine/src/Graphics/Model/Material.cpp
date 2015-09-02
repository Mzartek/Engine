#include <Engine/Graphics/Model/Material.hpp>

Engine::Graphics::Material::Material(void)
	: _diffuseTexture(NULL), _specularTexture(NULL), _ambientTexture(NULL), _emissiveTexture(NULL), _shininessTexture(NULL),
	_opacityTexture(NULL), _bumpMap(NULL), _normalMap(NULL), _displacementMap(NULL), _lightMap(NULL)
{
	_matBuffer = std::shared_ptr<Buffer>(new Buffer);
	_stateBuffer = std::shared_ptr<Buffer>(new Buffer);

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

Engine::Graphics::Material::~Material(void)
{
}

void Engine::Graphics::Material::setDiffuse(const glm::vec3 &color)
{
	_mat.diffuse = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setSpecular(const glm::vec3 &color)
{
	_mat.specular = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setAmbient(const glm::vec3 &color)
{
	_mat.ambient = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setEmissive(const glm::vec3 &color)
{
	_mat.emissive = color;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setShininess(GLfloat shininess)
{
	_mat.shininess = shininess;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setOpacity(GLfloat opacity)
{
	_mat.opacity = opacity;
	_matBuffer->updateStoreSub(&_mat);
}

void Engine::Graphics::Material::setDiffuseTexture(const std::shared_ptr<Texture2D> &tex)
{
	_diffuseTexture = tex;

	if (_diffuseTexture)
		_state.hasDiffuseTexture = GL_TRUE;
	else
		_state.hasDiffuseTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setSpecularTexture(const std::shared_ptr<Texture2D> &tex)
{
	_specularTexture = tex;

	if (_diffuseTexture)
		_state.hasSpecularTexture = GL_TRUE;
	else
		_state.hasSpecularTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setAmbientTexture(const std::shared_ptr<Texture2D> &tex)
{
	_ambientTexture = tex;

	if (_diffuseTexture)
		_state.hasAmbientTexture = GL_TRUE;
	else
		_state.hasAmbientTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setEmissiveTexture(const std::shared_ptr<Texture2D> &tex)
{
	_emissiveTexture = tex;

	if (_diffuseTexture)
		_state.hasEmissiveTexture = GL_TRUE;
	else
		_state.hasEmissiveTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setShininessTexture(const std::shared_ptr<Texture2D> &tex)
{
	_shininessTexture = tex;

	if (_diffuseTexture)
		_state.hasShininessTexture = GL_TRUE;
	else
		_state.hasShininessTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setOpacityTexture(const std::shared_ptr<Texture2D> &tex)
{
	_opacityTexture = tex;

	if (_diffuseTexture)
		_state.hasOpacityTexture = GL_TRUE;
	else
		_state.hasOpacityTexture = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setBumpMap(const std::shared_ptr<Texture2D> &tex)
{
	_bumpMap = tex;

	if (_diffuseTexture)
		_state.hasBumpMap = GL_TRUE;
	else
		_state.hasBumpMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setNormalMap(const std::shared_ptr<Texture2D> &tex)
{
	_normalMap = tex;

	if (_diffuseTexture)
		_state.hasNormalMap = GL_TRUE;
	else
		_state.hasNormalMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setDisplacementMap(const std::shared_ptr<Texture2D> &tex)
{
	_displacementMap = tex;

	if (_diffuseTexture)
		_state.hasDisplacementMap = GL_TRUE;
	else
		_state.hasDisplacementMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

void Engine::Graphics::Material::setLightMap(const std::shared_ptr<Texture2D> &tex)
{
	_lightMap = tex;

	if (_diffuseTexture)
		_state.hasLightMap = GL_TRUE;
	else
		_state.hasLightMap = GL_FALSE;

	_stateBuffer->updateStoreSub(&_state);
}

const glm::vec3 &Engine::Graphics::Material::getDiffuse(void) const
{
	return _mat.diffuse;
}

const glm::vec3 &Engine::Graphics::Material::getSpecular(void) const
{
	return _mat.specular;
}

const glm::vec3 &Engine::Graphics::Material::getAmbient(void) const
{
	return _mat.ambient;
}

const glm::vec3 &Engine::Graphics::Material::getEmissive(void) const
{
	return _mat.emissive;
}

GLfloat Engine::Graphics::Material::getShininess(void) const
{
	return _mat.shininess;
}

GLfloat Engine::Graphics::Material::getOpacity(void) const
{
	return _mat.opacity;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getDiffuseTexture(void) const
{
	return _diffuseTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getSpecularTexture(void) const
{
	return _specularTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getAmbientTexture(void) const
{
	return _ambientTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getEmissiveTexture(void) const
{
	return _emissiveTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getShininessTexture(void) const
{
	return _shininessTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getOpacityTexture(void) const
{
	return _opacityTexture;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getBumpMap(void) const
{
	return _bumpMap;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getNormalMap(void) const
{
	return _normalMap;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getDisplacementMap(void) const
{
	return _displacementMap;
}

const std::shared_ptr<Engine::Graphics::Texture2D> &Engine::Graphics::Material::getLightMap(void) const
{
	return _lightMap;
}

GLboolean Engine::Graphics::Material::hasDiffuseTexture(void) const
{
	return (GLboolean)_state.hasDiffuseTexture;
}

GLboolean Engine::Graphics::Material::hasSpecularTexture(void) const
{
	return (GLboolean)_state.hasSpecularTexture;
}

GLboolean Engine::Graphics::Material::hasAmbientTexture(void) const
{
	return (GLboolean)_state.hasAmbientTexture;
}

GLboolean Engine::Graphics::Material::hasEmissiveTexture(void) const
{
	return (GLboolean)_state.hasEmissiveTexture;
}

GLboolean Engine::Graphics::Material::hasShininessTexture(void) const
{
	return (GLboolean)_state.hasShininessTexture;
}

GLboolean Engine::Graphics::Material::hasOpacityTexture(void) const
{
	return (GLboolean)_state.hasOpacityTexture;
}

GLboolean Engine::Graphics::Material::hasBumpMap(void) const
{
	return (GLboolean)_state.hasBumpMap;
}

GLboolean Engine::Graphics::Material::hasNormalMap(void) const
{
	return (GLboolean)_state.hasNormalMap;
}

GLboolean Engine::Graphics::Material::hasDisplacementMap(void) const
{
	return (GLboolean)_state.hasDisplacementMap;
}

GLboolean Engine::Graphics::Material::hasLightMap(void) const
{
	return (GLboolean)_state.hasLightMap;
}

GLuint Engine::Graphics::Material::getMatBuffer(void) const
{
	return _matBuffer->getId();
}

GLuint Engine::Graphics::Material::getStateBuffer(void) const
{
	return _stateBuffer->getId();
}
