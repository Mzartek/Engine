#ifndef OCTREESYSTEM_HEADER
#define OCTREESYSTEM_HEADER

#include "Object.hpp"

namespace Engine
{
	class Camera;
	class Model;
	class GBuffer;

	struct Octree;

	class DLLAPI OctreeSystem : public Object
	{
	private:
		GLuint _maxDepth;
		Octree *_octree;
		void initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim);
		void destroyOctree(const GLuint &depth, Octree *octree);
		GLboolean addOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim);
		void displayOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam);
	public:
		OctreeSystem(const GLuint &maxDepth, const glm::vec3 &position, const GLfloat &dim);
		~OctreeSystem(void);
		void addModel(Model *model, const GLfloat &dim);
		void display(GBuffer *gbuffer, Camera *cam);
	};
}

#endif