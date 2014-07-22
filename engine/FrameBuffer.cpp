#include <Engine/FrameBuffer.hpp>

engine::FrameBuffer::FrameBuffer(void)
{
	_idFBO = 0;
}

engine::FrameBuffer::~FrameBuffer(void)
{
	if(glIsFramebuffer(_idFBO))
		glDeleteFramebuffers(1, &_idFBO);
}

GLuint engine::FrameBuffer::getWidth(void) const
{
	return _width;
}

GLuint engine::FrameBuffer::getHeight(void) const
{
	return _height;
}

GLuint engine::FrameBuffer::getIdFBO(void) const
{
	return _idFBO;
}
