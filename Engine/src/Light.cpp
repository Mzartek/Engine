#include <Engine/Light.hpp>
#include <Engine/Buffer.hpp>
#include <Engine/DepthMap.hpp>
#include <Engine/tools/ControllerMemory.hpp>

Engine::Light::Light(ShaderProgram *program)
	: _program(program)
{
	_vertexBuffer = new_ref(Buffer);
	_mainInfoBuffer = new_ref(Buffer);
	_lightInfoBuffer = new_ref(Buffer);

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
	release_ref(_vertexBuffer);
	release_ref(_mainInfoBuffer);
	release_ref(_lightInfoBuffer);
}
