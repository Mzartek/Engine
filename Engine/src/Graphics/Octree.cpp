#include <Engine/Graphics/Octree.hpp>

inline bool Engine::Octree::checkCamInCube(const std::shared_ptr<Engine::PerspCamera> &cam) const
{
	const glm::vec3 &p = cam->getCameraPosition();

	if (p.x >= _vertex[0].x && p.x < _vertex[7].x &&
		p.y >= _vertex[0].y && p.y < _vertex[7].y &&
		p.z >= _vertex[0].z && p.z < _vertex[7].z)
		return true;
	return false;
}

inline bool Engine::Octree::checkCamInSphere(const std::shared_ptr<Engine::PerspCamera> &cam) const
{
	const GLfloat distance = glm::length(cam->getCameraPosition() - cam->getFrusSpherePosition());

	if (distance < _radius + cam->getFrusSphereRadius())
		return true;
	return false;
}

inline bool Engine::Octree::checkInCamFrus(const std::shared_ptr<Engine::PerspCamera> &cam) const
{
	const glm::vec3 &camera_position = cam->getCameraPosition();
	const glm::vec3 &forward_vector = cam->getForwardVector();
	const GLfloat fov_2 = cam->getFOV() / 2;

	glm::vec3 position = _position;
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

Engine::Octree::Octree(GLuint depth, const glm::vec3 &position, GLfloat dim, std::map<Model *, Octree *> *map_model)
	: _isRoot(GL_FALSE), _map_model(map_model), _position(position)
{
	GLfloat newDim = dim / 2;
	GLfloat tmp = newDim / 2;

	_dim = dim;
	_dim_2 = newDim;
	_radius = glm::length(glm::vec3(newDim));

	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y - newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y - newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y + newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y + newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y - newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y - newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y + newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y + newDim, _position.z + newDim) * glm::vec3(2, 2, 2));

	if (depth > 0)
	{
		glm::vec3 newPositions[] = {
			glm::vec3(_position.x - tmp, _position.y - tmp, _position.z - tmp),
			glm::vec3(_position.x - tmp, _position.y - tmp, _position.z + tmp),
			glm::vec3(_position.x - tmp, _position.y + tmp, _position.z - tmp),
			glm::vec3(_position.x - tmp, _position.y + tmp, _position.z + tmp),
			glm::vec3(_position.x + tmp, _position.y - tmp, _position.z - tmp),
			glm::vec3(_position.x + tmp, _position.y - tmp, _position.z + tmp),
			glm::vec3(_position.x + tmp, _position.y + tmp, _position.z - tmp),
			glm::vec3(_position.x + tmp, _position.y + tmp, _position.z + tmp),
		};

		for (GLuint i = 0; i < 8; i++)
			_children.push_back(new Octree(depth - 1, newPositions[i], newDim, _map_model));
	}
}

Engine::Octree::Octree(GLuint depth, const glm::vec3 &position, GLfloat dim)
	: _isRoot(GL_TRUE), _map_model(new std::map<Model *, Octree *>), _position(position)
{
	GLfloat newDim = dim / 2;
	GLfloat tmp = newDim / 2;

	_dim = dim;
	_dim_2 = newDim;
	_radius = glm::length(glm::vec3(newDim));

	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y - newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y - newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y + newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x - newDim, _position.y + newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y - newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y - newDim, _position.z + newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y + newDim, _position.z - newDim) * glm::vec3(2, 2, 2));
	_vertex.push_back(glm::vec3(_position.x + newDim, _position.y + newDim, _position.z + newDim) * glm::vec3(2, 2, 2));

	if (depth > 0)
	{
		glm::vec3 newPositions[] = {
			glm::vec3(_position.x - tmp, _position.y - tmp, _position.z - tmp),
			glm::vec3(_position.x - tmp, _position.y - tmp, _position.z + tmp),
			glm::vec3(_position.x - tmp, _position.y + tmp, _position.z - tmp),
			glm::vec3(_position.x - tmp, _position.y + tmp, _position.z + tmp),
			glm::vec3(_position.x + tmp, _position.y - tmp, _position.z - tmp),
			glm::vec3(_position.x + tmp, _position.y - tmp, _position.z + tmp),
			glm::vec3(_position.x + tmp, _position.y + tmp, _position.z - tmp),
			glm::vec3(_position.x + tmp, _position.y + tmp, _position.z + tmp),
		};

		for (GLuint i = 0; i < 8; i++)
			_children.push_back(new Octree(depth - 1, newPositions[i], newDim, _map_model));
	}
}

Engine::Octree::~Octree(void)
{
	if (_isRoot) delete _map_model;
	for (std::vector<Octree *>::iterator it = _children.begin(); it != _children.end(); it++)
		delete *it;
}

bool Engine::Octree::addModel(Model *model, GLfloat dim)
{
	if (dim > _dim)	return false;

	const glm::vec3 &model_pos = model->getPosition();

	// Check the position
	if (model_pos.x < (_position.x - _dim_2) || model_pos.x >= (_position.x + _dim_2) ||
		model_pos.y < (_position.y - _dim_2) || model_pos.y >= (_position.y + _dim_2) ||
		model_pos.z < (_position.z - _dim_2) || model_pos.z >= (_position.z + _dim_2))
		return false;

	for (std::vector<Octree *>::iterator it = _children.begin(); it != _children.end(); it++)
		if ((*it)->addModel(model, dim)) return true;
	
	_modelContainer.insert(model);
 	(*_map_model)[model] = this;

	return true;
}

void Engine::Octree::removeModel(Model *model)
{
	std::map<Model *, Octree *>::iterator map_it = _map_model->find(model);

	if (map_it != _map_model->end()) map_it->second->_modelContainer.erase(model);
}

void Engine::Octree::getModels(const std::shared_ptr<PerspCamera> &cam, std::set<Model *> &set_model)
{
	if (!checkCamInCube(cam))
	{
		if (!checkCamInSphere(cam)) return;
		if (!checkInCamFrus(cam)) return;
	}

	set_model.insert(_modelContainer.begin(), _modelContainer.end());

	for (std::vector<Octree *>::iterator it = _children.begin(); it != _children.end(); it++)
		(*it)->getModels(cam, set_model);
}