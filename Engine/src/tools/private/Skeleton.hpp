#ifndef SKELETON_HEADER
#define SKELETON_HEADER

#include <Engine/Object.hpp>
#include <Engine/tools/ControllerMemory.hpp>

namespace Engine
{
	struct Skeleton : public Object
	{
		std::string name;
		glm::mat4 matrix;

		Skeleton *parent;
		std::vector<Skeleton *> children;

		Skeleton(void);
		Skeleton(const std::string &name);
		~Skeleton(void);
	};
}

#endif