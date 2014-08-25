#include <Engine/Object.hpp>

GLint engine::Object::_memState = 0;
std::vector<void *> _tmemNew;
std::vector<void *> _tmemDelete;
std::vector<void *> _tmem;

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
	_tmemNew.push_back(p);
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
	_tmemNew.push_back(p);
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
			_tmemDelete.push_back(p);
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
			_tmemDelete.push_back(p);
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

void engine::Object::saveMemoryInfo(const GLchar *filename)
{
	std::ofstream file(filename, std::ifstream::out);
	unsigned int i;

	file << "Memory Alloc:" << std::endl;
	for (i = 0; i < _tmemNew.size(); i++)
		file << _tmemNew[i] << std::endl;
	file << std::endl;

	file << "Memory Free:" << std::endl;
	for (i = 0; i < _tmemDelete.size(); i++)
		file << _tmemDelete[i] << std::endl;
	file << std::endl;

	file << "Memory Last:" << std::endl;
	for (i = 0; i < _tmem.size(); i++)
		file << _tmem[i] << std::endl;
	file << std::endl;

	file.close();
}
