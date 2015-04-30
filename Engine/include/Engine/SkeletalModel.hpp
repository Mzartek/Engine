#ifndef SKELETALMODEL_HEADER
#define SKELETALMODEL_HEADER

#define SKELETAL_MODEL_MAX_BONES 200

#include "Model.hpp"

namespace Engine
{
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

		struct Skeleton
		{
			glm::mat4 *_matrix;
			Skeleton *_parent;
			std::vector<Skeleton *> _children;

			Skeleton(glm::mat4 *matrix);
			~Skeleton(void);
		};
		Skeleton *_skeleton;

	public:
		SkeletalModel(ShaderProgram *gProgram, ShaderProgram *smProgram);
		SkeletalModel(SkeletalModel *model, ShaderProgram *gProgram, ShaderProgram *smProgram);
		~SkeletalModel(void);

		void loadFromFile(const GLchar *inFile);
		void display(GBuffer *g, PerspCamera *cam);
		void displayTransparent(GBuffer *gbuf, PerspCamera *cam);
		void displayDepthMap(DepthMap *dmap, Camera *cam);
		void displayDepthMap(DepthMap *dmaps, DirLight *light);
		void displayDepthMap(DepthMap *dmap, SpotLight *light);
	};
}

#endif