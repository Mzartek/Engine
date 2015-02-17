#ifndef OCTREESYSTEM_HEADER
#define OCTREESYSTEM_HEADER

#include "Object.hpp"

namespace Engine
{
	class Camera;
	class Model;
	class ParticlesManager;
	class GBuffer;

	struct Octree;

	class DLLAPI OctreeSystem : public Object
	{
	private:
		GLuint _maxDepth;
		Octree *_octree;
		void initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim) const;
		void destroyOctree(const GLuint &depth, Octree *octree) const;
		GLboolean addModelOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim) const;
		void removeModelOctree(const GLuint &depth, Octree *octree, Model *model) const;
		void getModelOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam, std::vector<Model *> *modelVector) const;
	public:
		OctreeSystem(const GLuint &maxDepth, const glm::vec3 &pos, const GLfloat &dim);
		~OctreeSystem(void);
		void addModel(Model *model, const GLfloat &dim) const;
		void removeModel(Model *model) const;
		void getModel(GBuffer *gbuffer, Camera *cam, std::vector<Model *> *modelVector) const;
	};
}

#endif