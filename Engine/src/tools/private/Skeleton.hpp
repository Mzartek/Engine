#ifndef SKELETON_HEADER
#define SKELETON_HEADER

#include <Engine/Object.hpp>

namespace Engine
{
	struct Skeleton : public Object
	{
		std::string _name;
		glm::mat4 _matrix;

		Skeleton *_parent;
		std::vector<Skeleton *> _children;

		Skeleton(void);
		Skeleton(const std::string &name);
		~Skeleton(void);
	};
}

#endif