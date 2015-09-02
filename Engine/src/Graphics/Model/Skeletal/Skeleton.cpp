#include <Engine/Graphics/Model/Skeletal/Skeleton.hpp>

Engine::Graphics::Skeleton::Skeleton(void)
{
	name = "";
	parent = NULL;
}

Engine::Graphics::Skeleton::Skeleton(const std::string &name)
{
	this->name = name;
}

Engine::Graphics::Skeleton::~Skeleton(void)
{
	for (std::vector<Skeleton *>::iterator it = children.begin(); it != children.end(); it++)
		delete *it;
}

Engine::Graphics::Skeleton *Engine::Graphics::Skeleton::searchByName(const std::string &searchName)
{
	if (searchName == name)
		return this;

	for (std::vector<Skeleton *>::iterator it = children.begin(); it != children.end(); it++)
	{
		Skeleton *tmp_skeleton = (*it)->searchByName(searchName);
		if (tmp_skeleton != NULL) return tmp_skeleton;
	}

	return NULL;
}