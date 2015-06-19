#include <Engine/Graphics/Light.hpp>

Engine::Graphics::Light::Light(const std::shared_ptr<ShaderProgram> &program)
	: _program(program)
{
	_mainInfoBuffer = std::shared_ptr<Buffer>(new Buffer);
	_lightInfoBuffer = std::shared_ptr<Buffer>(new Buffer);

	_mainInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _mainInfo, GL_DYNAMIC_DRAW);
}

Engine::Graphics::Light::~Light(void)
{
}
