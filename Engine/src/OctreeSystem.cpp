#include <Engine/OctreeSystem.hpp>
#include <Engine/Camera.hpp>
#include <Engine/Model.hpp>
#include <Engine/GBuffer.hpp>

struct Engine::Octree
{
	glm::vec3 position;
	GLfloat dim;
	std::vector<Engine::Model *> container;
	struct Octree *next;
};

void Engine::OctreeSystem::initOctree(const GLuint &depth, Octree *octree, const glm::vec3 &position, const GLfloat &dim)
{
	if (depth >= _maxDepth)	return;

	octree->position = position;
	octree->dim = dim;
	octree->next = new Octree[8];

	GLfloat newDim = dim / 2;

	initOctree(depth + 1, &octree->next[0], glm::vec3(position.x - newDim, position.y - newDim, position.z - newDim), newDim);
	initOctree(depth + 1, &octree->next[1], glm::vec3(position.x - newDim, position.y - newDim, position.z + newDim), newDim);
	initOctree(depth + 1, &octree->next[2], glm::vec3(position.x - newDim, position.y + newDim, position.z - newDim), newDim);
	initOctree(depth + 1, &octree->next[3], glm::vec3(position.x - newDim, position.y + newDim, position.z + newDim), newDim);
	initOctree(depth + 1, &octree->next[4], glm::vec3(position.x + newDim, position.y - newDim, position.z - newDim), newDim);
	initOctree(depth + 1, &octree->next[5], glm::vec3(position.x + newDim, position.y - newDim, position.z + newDim), newDim);
	initOctree(depth + 1, &octree->next[6], glm::vec3(position.x + newDim, position.y + newDim, position.z - newDim), newDim);
	initOctree(depth + 1, &octree->next[7], glm::vec3(position.x + newDim, position.y + newDim, position.z + newDim), newDim);
}

void Engine::OctreeSystem::destroyOctree(const GLuint &depth, Octree *octree)
{
	if (depth >= _maxDepth)	return;

	for (GLuint i = 0; i < 8; i++) 
		destroyOctree(depth + 1, &(octree->next[i]));
	delete[] octree->next;
}

GLboolean Engine::OctreeSystem::addOctree(const GLuint &depth, Octree *octree, Model *model, const GLfloat &dim)
{
	if (depth >= _maxDepth || dim > octree->dim) return GL_FALSE;

	glm::vec3 octree_pos = octree->position;
	glm::vec3 model_pos = model->getPosition();

	// Check the position
	if (model_pos.x < (octree_pos.x - octree->dim) || model_pos.y >= (octree_pos.x + octree->dim)) return GL_FALSE;
	if (model_pos.y < (octree_pos.y - octree->dim) || model_pos.y >= (octree_pos.y + octree->dim)) return GL_FALSE;
	if (model_pos.z < (octree_pos.z - octree->dim) || model_pos.z >= (octree_pos.z + octree->dim)) return GL_FALSE;

	// Recursive call
	if (addOctree(depth + 1, &octree->next[0], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[1], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[2], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[3], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[4], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[5], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[6], model, dim)) return GL_TRUE;
	if (addOctree(depth + 1, &octree->next[7], model, dim)) return GL_TRUE;

	octree->container.push_back(model);

	return GL_TRUE;
}

void Engine::OctreeSystem::displayOctree(const GLuint &depth, Octree *octree, GBuffer *gbuffer, Camera *cam)
{
	if (depth >= _maxDepth)	return;

	for (GLuint i = 0; i < octree->container.size(); i++)
		octree->container[i]->display(gbuffer, cam);

	for (GLuint i = 0; i < 8; i++)
		displayOctree(depth + 1, &(octree->next[i]), gbuffer, cam);
}

Engine::OctreeSystem::OctreeSystem(const GLuint &maxDepth, const glm::vec3 &position, const GLfloat &dim)
{
	_maxDepth = maxDepth;
	_octree = new Octree;
	initOctree(0, _octree, position, dim);
}

Engine::OctreeSystem::~OctreeSystem()
{
	destroyOctree(0, _octree);
	delete _octree;
}

void Engine::OctreeSystem::addModel(Model *model, const GLfloat &dim)
{
	if (!addOctree(0, _octree, model, dim))
		std::cerr << "Unable to add model on the OctreeSystem" << std::endl;
}

void Engine::OctreeSystem::display(GBuffer *gbuffer, Camera *cam)
{
	displayOctree(0, _octree, gbuffer, cam);
}