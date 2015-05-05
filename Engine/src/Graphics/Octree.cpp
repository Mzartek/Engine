#include <Engine/Graphics/Octree.hpp>

inline bool Engine::Octree::checkCamInCube(const PerspCamera &cam) const
{
	const glm::vec3 p = cam.getCameraPosition();

	if (p.x >= _vertex[0].x && p.x < _vertex[7].x &&
		p.y >= _vertex[0].y && p.y < _vertex[7].y &&
		p.z >= _vertex[0].z && p.z < _vertex[7].z)
		return true;
	return false;
}

inline bool Engine::Octree::checkCamInSphere(const PerspCamera &cam) const
{
	const GLfloat distance = glm::length(cam.getCameraPosition() - cam.getFrusSpherePosition());

	if (distance < _radius + cam.getFrusSphereRadius())
		return true;
	return false;
}

inline bool Engine::Octree::checkInCamFrus(const PerspCamera &cam) const
{
	const glm::vec3 camera_position = cam.getCameraPosition();
	const glm::vec3 forward_vector = cam.getForwardVector();
	const GLfloat fov_2 = cam.getFOV() / 2;

	glm::vec3 position = *_position;
	glm::vec3 direction = glm::normalize(position - camera_position);
	GLfloat dot = glm::dot(forward_vector, direction);

	if (acosf(dot) < fov_2) return true;
	for (GLint i = 0; i < 8; i++)
	{
		position = _vertex[i];
		direction = glm::normalize(position - camera_position);
		dot = glm::dot(forward_vector, direction);

		if (acosf(dot) < fov_2) return true;
	}
	return false;
}

Engine::Octree::Octree(const GLuint &depth, const glm::vec3 &position, const GLfloat &dim)
{
	_position = new_ptr(glm::vec3(position));
	_vertex = new_ptr_tab(glm::vec3, 8);
	_modelContainer = new_ptr(std::set<Model *>);
	_children = new_ptr(std::vector<Octree *>);

	GLfloat newDim = dim / 2;
	GLfloat tmp = newDim / 2;

	_dim = dim;
	_dim_2 = newDim;
	_radius = glm::length(glm::vec3(newDim));

	_vertex[0] = glm::vec3(position.x - newDim, position.y - newDim, position.z - newDim);
	_vertex[1] = glm::vec3(position.x - newDim, position.y - newDim, position.z + newDim);
	_vertex[2] = glm::vec3(position.x - newDim, position.y + newDim, position.z - newDim);
	_vertex[3] = glm::vec3(position.x - newDim, position.y + newDim, position.z + newDim);
	_vertex[4] = glm::vec3(position.x + newDim, position.y - newDim, position.z - newDim);
	_vertex[5] = glm::vec3(position.x + newDim, position.y - newDim, position.z + newDim);
	_vertex[6] = glm::vec3(position.x + newDim, position.y + newDim, position.z - newDim);
	_vertex[7] = glm::vec3(position.x + newDim, position.y + newDim, position.z + newDim);

	if (depth > 0)
	{
		glm::vec3 newPositions[] = {
			glm::vec3(position.x - tmp, position.y - tmp, position.z - tmp),
			glm::vec3(position.x - tmp, position.y - tmp, position.z + tmp),
			glm::vec3(position.x - tmp, position.y + tmp, position.z - tmp),
			glm::vec3(position.x - tmp, position.y + tmp, position.z + tmp),
			glm::vec3(position.x + tmp, position.y - tmp, position.z - tmp),
			glm::vec3(position.x + tmp, position.y - tmp, position.z + tmp),
			glm::vec3(position.x + tmp, position.y + tmp, position.z - tmp),
			glm::vec3(position.x + tmp, position.y + tmp, position.z + tmp),
		};

		for (GLuint i = 0; i < 8; i++)
			_children->push_back(new_ptr(Octree(depth - 1, newPositions[i], newDim)));
	}
}

Engine::Octree::~Octree(void)
{
	for (std::vector<Octree *>::iterator it = _children->begin(); it != _children->end(); it++)
		release_ptr(*it);

	release_ptr(_position);
	release_ptr(_vertex);
	release_ptr(_modelContainer);
	release_ptr(_children);
}

bool Engine::Octree::addModel(Model *model, const GLfloat &dim)
{
	if (dim > _dim)	return false;

	glm::vec3 model_pos = model->getPosition();

	// Check the position
	if (model_pos.x < (_position->x - _dim_2) || model_pos.x >= (_position->x + _dim_2) ||
		model_pos.y < (_position->y - _dim_2) || model_pos.y >= (_position->y + _dim_2) ||
		model_pos.z < (_position->z - _dim_2) || model_pos.z >= (_position->z + _dim_2))
		return false;

	unsigned int res = 0;

	for (std::vector<Octree *>::iterator it = _children->begin(); it != _children->end(); it++)
		res += (*it)->addModel(model, dim);
	
	if (res == 0)
		_modelContainer->insert(model);

	return true;
}

void Engine::Octree::removeModel(Model *model)
{
	_modelContainer->erase(model);

	for (std::vector<Octree *>::iterator it = _children->begin(); it != _children->end(); it++)
		(*it)->removeModel(model);
}

void Engine::Octree::getModels(const PerspCamera &cam, std::set<Model *> *set_model)
{
	if (!checkCamInCube(cam))
	{
		if (!checkCamInSphere(cam)) return;
		if (!checkInCamFrus(cam)) return;
	}

	set_model->insert(_modelContainer->begin(), _modelContainer->end());

	for (std::vector<Octree *>::iterator it = _children->begin(); it != _children->end(); it++)
		(*it)->getModels(cam, set_model);
}