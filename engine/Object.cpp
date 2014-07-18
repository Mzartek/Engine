#include <Engine/Object.hpp>

GLint _memState = 0;
static std::vector<void *> _tmem;

engine::Object::Object(void)
{
}

engine::Object::~Object(void)
{
}

void *engine::Object::operator new(size_t sz)
{
	void *p = malloc(sz);
	if (p == NULL)
	{
		fprintf(stderr, "Error alloc\n");
		exit(1);
	}
	_memState++;
	_tmem.push_back(p);

	return p;
}

void *engine::Object::operator new[](size_t sz)
{
	void *p = malloc(sz);
	if (p == NULL)
	{
		fprintf(stderr, "Error alloc\n");
		exit(1);
	}
	_memState++;
	_tmem.push_back(p);

	return p;
}

void engine::Object::operator delete(void *p)
{
	GLuint i;
	for (i = 0; i < _tmem.size(); i++)
	{
		if (_tmem[i] == p)
		{
			_tmem.erase(_tmem.begin() + i);
			_memState--;
			free(p);
			return;
		}
	}
	std::cout << "Error Delete" << std::endl;
}

void engine::Object::operator delete[](void *p)
{
	GLuint i;
	for (i = 0; i < _tmem.size(); i++)
	{
		if (_tmem[i] == p)
		{
			_tmem.erase(_tmem.begin() + i);
			_memState--;
			free(p);
			return;
		}
	}
	std::cout << "Error Delete" << std::endl;
}

GLint engine::Object::getMemoryState(void)
{
	return _memState;
}

void engine::Object::displayMemoryInfo(void)
{
	unsigned int i;
	for (i = 0; i<_tmem.size(); i++)
		std::cout << _tmem[i] << std::endl;
}