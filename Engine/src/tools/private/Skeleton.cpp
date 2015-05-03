#include "Skeleton.hpp"
#include <Engine/tools/ControllerMemory.hpp>

Engine::Skeleton::Skeleton(void)
{
	name = "";
	parent = NULL;
}

Engine::Skeleton::Skeleton(const std::string &name)
{
	this->name = name;
}

Engine::Skeleton::~Skeleton(void)
{
	for (std::vector<Skeleton *>::iterator it = children.begin(); it != children.end(); it++)
		release_ptr(*it);
}