#include <Engine/FrameBuffer.hpp>

Engine::FrameBuffer::FrameBuffer(void)
{
	glGenFramebuffers(1, &_idFBO);
}

Engine::FrameBuffer::~FrameBuffer(void)
{
	glDeleteFramebuffers(1, &_idFBO);
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
