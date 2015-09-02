#include <Engine/Graphics/Buffer/Buffer.hpp>

Engine::Graphics::Buffer::Buffer(void)
	: _target(GL_ARRAY_BUFFER), _idBuffer(0), _size(0)
{
}

Engine::Graphics::Buffer::~Buffer(void)
{
	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
}

GLenum Engine::Graphics::Buffer::getTarget(void) const
{
	return _target;
}

GLuint Engine::Graphics::Buffer::getId(void) const
{
	return _idBuffer;
}

void Engine::Graphics::Buffer::createStore(GLenum target, const GLvoid *data, GLsizeiptr size, GLenum usage)
{
	_target = target;
	_size = size;

	if (_target == GL_UNIFORM_BUFFER)
	{
		if ((size % 16) != 0)
		{
			throw std::invalid_argument("Need a power of 16 for Uniform Buffer");
		}
	}

	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
	glGenBuffers(1, &_idBuffer);
	glBindBuffer(_target, _idBuffer);
	glBufferData(_target, _size, data, usage);
	glBindBuffer(_target, 0);
}

void Engine::Graphics::Buffer::updateStoreSub(const GLvoid *data) const
{
	glBindBuffer(_target, _idBuffer);
	glBufferSubData(_target, 0, _size, data);
	glBindBuffer(_target, 0);
}

void Engine::Graphics::Buffer::updateStoreMap(const GLvoid *data) const
{
	glBindBuffer(_target, _idBuffer);
	memcpy(glMapBuffer(_target, GL_WRITE_ONLY), data, _size);
	glUnmapBuffer(_target);
	glBindBuffer(_target, 0);
}
