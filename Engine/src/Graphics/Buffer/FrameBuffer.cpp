#include <Engine/Graphics/Buffer/FrameBuffer.hpp>

Engine::Graphics::FrameBuffer::FrameBuffer(void)
	: _width(0), _height(0)
{
	glGenFramebuffers(1, &_idFBO);
}

Engine::Graphics::FrameBuffer::~FrameBuffer(void)
{
	glDeleteFramebuffers(1, &_idFBO);
}

void Engine::Graphics::FrameBuffer::config(GLuint width, GLuint height)
{
	_width = width;
	_height = height;
}

GLuint Engine::Graphics::FrameBuffer::getWidth(void) const
{
	return _width;
}

GLuint Engine::Graphics::FrameBuffer::getHeight(void) const
{
	return _height;
}

GLuint Engine::Graphics::FrameBuffer::getIdFBO(void) const
{
	return _idFBO;
}
