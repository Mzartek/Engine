#include <Engine/FrameBuffer.hpp>

engine::FrameBuffer::FrameBuffer(void)
{
	_idFBO = 0;
	_program = NULL;
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

GLuint engine::FrameBuffer::getProgramId(void) const
{
	return _program->getId();
}

void engine::FrameBuffer::clear(void) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, _idFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glViewport(0, 0, _width, _height);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
