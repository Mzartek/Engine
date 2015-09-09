#ifndef OCTREE_HEADER
#define OCTREE_HEADER

#include "../Object.hpp"

#include "Model/Model.hpp"

namespace Engine
{
	namespace Graphics
	{
		class DLLAPI Octree : public Object
		{
			glm::vec3 _position;
			std::vector<glm::vec3> _vertex;

			GLfloat _dim;
			GLfloat _dim_2;
			GLfloat _radius;

			std::set<Model *> _modelContainer;
			std::vector<Octree *> _children;

			bool checkCamInCube(const std::shared_ptr<PerspCamera> &cam) const;
			bool checkCamInSphere(const std::shared_ptr<PerspCamera> &cam) const;
			bool checkInCamFrus(const std::shared_ptr<PerspCamera> &cam) const;

		public:
			Octree(GLuint depth, const glm::vec3 &position, GLfloat dim);
			~Octree(void);

			bool addModel(Model *model, GLfloat dim);
			bool removeModel(Model *model);
			void getModels(const std::shared_ptr<PerspCamera> &cam, std::set<Model *> &set_model);
		};
	}
}
#endif