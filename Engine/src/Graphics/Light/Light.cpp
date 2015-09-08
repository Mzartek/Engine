#include <Engine/Graphics/Light/Light.hpp>

Engine::Graphics::Light::Light(const std::shared_ptr<ShaderProgram> &program)
	: _program(program)
{
	_mainInfoBuffer = std::make_shared<Buffer>();
	_lightInfoBuffer = std::make_shared<Buffer>();

	_mainInfoBuffer->createStore(GL_UNIFORM_BUFFER, nullptr, sizeof _mainInfo, GL_DYNAMIC_DRAW);
}

Engine::Graphics::Light::~Light(void)
{
}
