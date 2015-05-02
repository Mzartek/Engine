#include <Engine/Object.hpp>
#include <Engine/tools/ControllerMemory.hpp>

GLint Engine::Object::_memState = 0;
static std::set<void *> _tmem;

std::string Engine::getDir(const GLchar *file)
{
	GLuint size, i;
	std::string path;

	for (size = i = 0; file[i] != '\0'; i++)
		if (file[i] == '/')
			size = i + 1;

	path.insert(0, file, 0, size);

	return path;
}

Engine::Object::Object(void)
{
	_tObject = new_ref(std::set < Object * >);
}

Engine::Object::~Object(void)
{
	for (std::set<Object *>::iterator it = _tObject->begin(); it != _tObject->end(); it++)
		release_ref(*it);
	release_ref(_tObject);
}

void *Engine::Object::operator new(size_t sz)
{
	void *p = malloc(sz);
	if (p == NULL)
	{
		std::cerr << "Error alloc" << std::endl;
		abort();
	}
	_memState++;
	_tmem.insert(p);

	return p;
}

void *Engine::Object::operator new[](size_t sz)
{
	void *p = malloc(sz);
	if (p == NULL)
	{
		std::cerr << "Error alloc" << std::endl;
		abort();
	}
	_memState++;
	_tmem.insert(p);

	return p;
}

void Engine::Object::operator delete(void *p)
{
	std::set<void *>::iterator it = _tmem.find(p);

	if (it != _tmem.end())
	{
		_tmem.erase(it);
		_memState--;
		free(p);
		return;
	}

	std::cerr << "Error Delete" << std::endl;
}

void Engine::Object::operator delete[](void *p)
{
	std::set<void *>::iterator it = _tmem.find(p);

	if (it != _tmem.end())
	{
		_tmem.erase(it);
		_memState--;
		free(p);
		return;
	}

	std::cerr << "Error Delete" << std::endl;
}

GLint Engine::Object::getMemoryState(void)
{
	return _memState;
}
