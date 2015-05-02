#include <Engine/Object.hpp>
#include <Engine/tools/ControllerMemory.hpp>

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
