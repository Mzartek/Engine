#include <Engine/Graphics/Light.hpp>

Engine::Light::Light(ShaderProgram *program)
	: _program(program)
{
	_vertexBuffer = new_ptr(Buffer);
	_mainInfoBuffer = new_ptr(Buffer);
	_lightInfoBuffer = new_ptr(Buffer);

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
	release_ptr(_vertexBuffer);
	release_ptr(_mainInfoBuffer);
	release_ptr(_lightInfoBuffer);
}
