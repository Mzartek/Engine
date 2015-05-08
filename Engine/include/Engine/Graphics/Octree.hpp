#ifndef OCTREE_HEADER
#define OCTREE_HEADER

#include "../Object.hpp"

#include "Model.hpp"

namespace Engine
{
	struct DLLAPI Octree : public Object
	{
	private:
		glm::vec3 _position;
		std::vector<glm::vec3> _vertex;

		GLfloat _dim;
		GLfloat _dim_2;
		GLfloat _radius;

		std::set<std::shared_ptr<Model>> _modelContainer;

		std::vector<Octree *> _children;

		bool checkCamInCube(const std::shared_ptr<Engine::PerspCamera> &cam) const;
		bool checkCamInSphere(const std::shared_ptr<Engine::PerspCamera> &cam) const;
		bool checkInCamFrus(const std::shared_ptr<Engine::PerspCamera> &cam) const;

	public:
		Octree(GLuint depth, const glm::vec3 &position, GLfloat dim);
		~Octree(void);

		bool addModel(const std::shared_ptr<Model> &model, GLfloat dim);
		void removeModel(const std::shared_ptr<Model> &model);
		void getModels(const std::shared_ptr<PerspCamera> &cam, std::set<std::shared_ptr<Model>> &set_model);
	};
}
#endif