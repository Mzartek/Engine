#include <Engine/Buffer.hpp>
#include <Engine/tools/ControllerMemory.hpp>

Engine::Buffer::Buffer(void)
	: _target(GL_ARRAY_BUFFER), _idBuffer(0), _size(0)
{
}

Engine::Buffer::~Buffer(void)
{
	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
}

GLenum Engine::Buffer::getTarget(void) const
{
	return _target;
}

GLuint Engine::Buffer::getId(void) const
{
	return _idBuffer;
}

void Engine::Buffer::createStore(const GLenum &target, const GLvoid *data, const GLsizeiptr &size, const GLenum &usage)
{
	_target = target;
	_size = size;

	if (_target == GL_UNIFORM_BUFFER)
	{
		if ((size % 16) != 0)
		{
			std::cerr << "Need a power of 16 for Uniform Buffer" << std::endl;
			abort();
		}
	}

	if (glIsBuffer(_idBuffer)) glDeleteBuffers(1, &_idBuffer);
	glGenBuffers(1, &_idBuffer);
	glBindBuffer(_target, _idBuffer);
	glBufferData(_target, _size, data, usage);
	glBindBuffer(_target, 0);
}

void Engine::Buffer::updateStoreSub(const GLvoid *data) const
{
	glBindBuffer(_target, _idBuffer);
	glBufferSubData(_target, 0, _size, data);
	glBindBuffer(_target, 0);
}

void Engine::Buffer::updateStoreMap(const GLvoid *data) const
{
	glBindBuffer(_target, _idBuffer);
	memcpy(glMapBuffer(_target, GL_WRITE_ONLY), data, _size);
	glUnmapBuffer(_target);
	glBindBuffer(_target, 0);
}
