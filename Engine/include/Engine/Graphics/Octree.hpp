#ifndef OCTREE_HEADER
#define OCTREE_HEADER

#include "../Object.hpp"
#include "../tools/ControllerMemory.hpp"

#include "Model.hpp"

namespace Engine
{
	struct DLLAPI Octree : public Object
	{
	private:
		glm::vec3 *_position;
		glm::vec3 *_vertex;

		GLfloat _dim;
		GLfloat _dim_2;
		GLfloat _radius;

		std::set<Model *> *_modelContainer;

		std::vector<Octree *> *_children;

		bool checkCamInCube(const Engine::PerspCamera &cam) const;
		bool checkCamInSphere(const Engine::PerspCamera &cam) const;
		bool checkInCamFrus(const Engine::PerspCamera &cam) const;

	public:
		Octree(const GLuint &depth, const glm::vec3 &position, const GLfloat &dim);
		~Octree(void);

		bool addModel(Model *model, const GLfloat &dim);
		void removeModel(Model *model);
		void getModels(const PerspCamera &cam, std::set<Model *> *set_model);
	};
}
#endif