#ifndef SKELETON_HEADER
#define SKELETON_HEADER

#include "../../../Object.hpp"

namespace Engine
{
	namespace Graphics
	{
		struct Skeleton
		{
			std::string name;
			glm::mat4 matrix;

			Skeleton *parent;
			std::vector<Skeleton *> children;

			Skeleton(void);
			Skeleton(const std::string &name);
			~Skeleton(void);

			Skeleton *searchByName(const std::string &searchName);
		};

		struct Bone
		{
			glm::mat4 offsetMatrix;
			Skeleton *ptr_in_skeleton;
		};
	}
}

#endif