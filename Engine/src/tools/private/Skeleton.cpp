#include "Skeleton.hpp"
#include <Engine/tools/ControllerMemory.hpp>

Engine::Skeleton::Skeleton(void)
{
	_parent = NULL;
}

Engine::Skeleton::~Skeleton(void)
{
	for (std::vector<Skeleton *>::iterator it = _children.begin(); it != _children.end(); it++)
		release_ref(*it);
}