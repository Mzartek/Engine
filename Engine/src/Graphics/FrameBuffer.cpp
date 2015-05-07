#include <Engine/Graphics/FrameBuffer.hpp>

Engine::FrameBuffer::FrameBuffer(void)
{
	glGenFramebuffers(1, &_idFBO);
}

Engine::FrameBuffer::~FrameBuffer(void)
{
	glDeleteFramebuffers(1, &_idFBO);
}

void Engine::FrameBuffer::config(GLuint width, GLuint height)
{
	_width = width;
	_height = height;
}

GLuint Engine::FrameBuffer::getWidth(void) const
{
	return _width;
}

GLuint Engine::FrameBuffer::getHeight(void) const
{
	return _height;
}

GLuint Engine::FrameBuffer::getIdFBO(void) const
{
	return _idFBO;
}
