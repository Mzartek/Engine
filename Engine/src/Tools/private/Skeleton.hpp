#ifndef SKELETON_HEADER
#define SKELETON_HEADER

#include <Engine/Object.hpp>
#include <Engine/tools/ControllerMemory.hpp>

namespace Engine
{
	struct Skeleton : public Object
	{
		std::string name;
		std::shared_ptr<glm::mat4> matrix;

		Skeleton *parent;
		std::shared_ptr<std::vector<Skeleton *>> children;

		Skeleton(void);
		Skeleton(const std::string &name);
		~Skeleton(void);

		Skeleton *searchByName(const std::string &name);
	};

	struct Bone : public Object
	{
		std::shared_ptr<glm::mat4> offsetMatrix;
		Skeleton *ptr_in_skeleton;
	};
}

#endif