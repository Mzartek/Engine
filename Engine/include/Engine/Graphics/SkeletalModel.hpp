#ifndef SKELETALMODEL_HEADER
#define SKELETALMODEL_HEADER

#define SKELETAL_MODEL_MAX_BONES 200

#include "Model.hpp"
#include "SkeletalMesh.hpp"

namespace Engine
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

		Skeleton *_skeleton;
		std::vector<Bone *> *_bones;

	public:
		SkeletalModel(ShaderProgram *gProgram, ShaderProgram *smProgram);
		SkeletalModel(SkeletalModel *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
		~SkeletalModel(void);
		void loadFromFile(const GLchar *inFile, const GLchar *node_name = NULL);

		void display(const GBuffer &gbuf, const PerspCamera &cam);
		void displayTransparent(const GBuffer &gbuf, const PerspCamera &cam);
		void displayDepthMap(const DepthMap &depthMap, const Camera &cam);
		void displayDepthMap(const std::array<std::shared_ptr<Engine::DepthMap>, CSM_NUM> &array_depthMap, DirLight *light);
		void displayDepthMap(const DepthMap &depthMap, SpotLight *light);
	};
}

#endif