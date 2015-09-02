#ifndef SKELETALMODEL_HEADER
#define SKELETALMODEL_HEADER

#define SKELETAL_MODEL_MAX_BONES 200

#include "../Model.hpp"

#include "SkeletalMesh.hpp"

namespace Engine
{
	namespace Graphics
	{
		struct Skeleton;
		struct Bone;

		class DLLAPI SkeletalModel : public Model
		{
		private:
			struct
			{
				glm::mat4 MVP;
				glm::mat4 projection;
				glm::mat4 view;
				glm::mat4 model;
				glm::mat4 normal;
				glm::mat4 bones[SKELETAL_MODEL_MAX_BONES];
			} _matrix;

			std::shared_ptr<Skeleton> _skeleton;
			std::vector<std::shared_ptr<Bone>> _bones;

		public:
			SkeletalModel(const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			SkeletalModel(const std::shared_ptr<SkeletalModel> &model, const std::shared_ptr<ShaderProgram> &gProgram, const std::shared_ptr<ShaderProgram> &smProgram);
			~SkeletalModel(void);
			void loadFromFile(const GLchar *inFile, const GLchar *node_name = NULL);

			void display(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam);
			void displayTransparent(const std::shared_ptr<GBuffer> &gbuf, const std::shared_ptr<PerspCamera> &cam);
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<Camera> &cam);
			void displayDepthMap(const std::shared_ptr<DepthMap> &depthMap, const std::shared_ptr<SpotLight> &light);
			void displayDepthMaps(const std::vector<std::shared_ptr<DepthMap>> &depthMaps, const std::shared_ptr<DirLight> &light);
		};
	}
}

#endif