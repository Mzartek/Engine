#include <Engine/Object.hpp>
#include <Engine/Tools/ControllerMemory.hpp>

Engine::Object::Object(void)
{
	_tObject = new_ptr(std::set < Object * >);
}

Engine::Object::~Object(void)
{
	for (std::set<Object *>::iterator it = _tObject->begin(); it != _tObject->end(); it++)
		release_ptr(*it);
	release_ptr(_tObject);
}
