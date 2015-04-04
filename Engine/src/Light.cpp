#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/DepthMap.hpp>

Engine::Light::Light(ShaderProgram *program)
	: _program(program)
{
	_vertexBuffer = new Buffer;
	_mainInfoBuffer = new Buffer;
	_lightInfoBuffer = new Buffer;

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

Engine::Light::~Light(void)
{
	delete _vertexBuffer;
	delete _mainInfoBuffer;
	delete _lightInfoBuffer;
}
