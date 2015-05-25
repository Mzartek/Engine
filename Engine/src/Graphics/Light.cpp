#include <Engine/Graphics/Light.hpp>

Engine::Graphics::Light::Light(const std::shared_ptr<ShaderProgram> &program)
	: _program(program)
{
	_vertexBuffer = std::shared_ptr<Buffer>(new Buffer);
	_mainInfoBuffer = std::shared_ptr<Buffer>(new Buffer);
	_lightInfoBuffer = std::shared_ptr<Buffer>(new Buffer);

	GLfloat vertex[] =
	{
		-1, -1,
		1, -1,
		-1, 1,
		1, 1,
	};
	_vertexBuffer->createStore(GL_ARRAY_BUFFER, vertex, sizeof vertex, GL_STATIC_DRAW);
	_mainInfoBuffer->createStore(GL_UNIFORM_BUFFER, NULL, sizeof _mainInfo, GL_DYNAMIC_DRAW);
}

Engine::Graphics::Light::~Light(void)
{
}
