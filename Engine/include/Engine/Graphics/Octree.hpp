#ifndef OCTREE_HEADER
#define OCTREE_HEADER

#include "../Object.hpp"

#include "Model.hpp"

namespace Engine
{
	struct DLLAPI Octree : public Object
	{
	private:
		GLboolean _isRoot;
		std::map<Model *, Octree *> *_map_model;

		glm::vec3 _position;
		std::vector<glm::vec3> _vertex;

		GLfloat _dim;
		GLfloat _dim_2;
		GLfloat _radius;

		std::set<Model *> _modelContainer;
		std::vector<Octree *> _children;

		bool checkCamInCube(const std::shared_ptr<Engine::PerspCamera> &cam) const;
		bool checkCamInSphere(const std::shared_ptr<Engine::PerspCamera> &cam) const;
		bool checkInCamFrus(const std::shared_ptr<Engine::PerspCamera> &cam) const;

		Octree(GLuint depth, const glm::vec3 &position, GLfloat dim, std::map<Model *, Octree *> *map_model);

	public:
		Octree(GLuint depth, const glm::vec3 &position, GLfloat dim);
		~Octree(void);

		bool addModel(Model *model, GLfloat dim);
		void removeModel(Model *model);
		void getModels(const std::shared_ptr<PerspCamera> &cam, std::set<Model *> &set_model);
	};
}
#endif