#include "Helicopter.hpp"

Helicopter::Helicopter()
	: _isMount(true)
{
	_objectProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/object/objectVert.glsl",
		NULL,
		NULL,
		"../share/Demo/shader/object/objectGeom.glsl",
		"../share/Demo/shader/object/objectFrag.glsl"));

	_depthMapProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/depthMap/depthMapVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/depthMap/depthMapFrag.glsl"));

	_corpsModel = std::shared_ptr<Graphics::StaticModel>(new Graphics::StaticModel(_objectProgram, _depthMapProgram));
	_rotorModel = std::shared_ptr<Graphics::StaticModel>(new Graphics::StaticModel(_objectProgram, _depthMapProgram));

	_corpsModel->loadFromFile("../share/Demo/resources/models/heli/corps.mobj");
	_corpsModel->sortMesh();

	_rotorModel->loadFromFile("../share/Demo/resources/models/heli/grotor.mobj");
	_rotorModel->sortMesh();
}

Helicopter::~Helicopter(void)
{
}

const std::shared_ptr<Graphics::StaticModel> &Helicopter::getCorpsModel(void) const
{
	return _corpsModel;
}

const std::shared_ptr<Graphics::StaticModel> &Helicopter::getRotorModel(void) const
{
	return _rotorModel;
}

void Helicopter::setMount(bool isMount)
{
	_isMount = isMount;
}

void Helicopter::setPosition(const glm::vec3 &position)
{
	_corpsModel->setPosition(position);

	if (_isMount)
		_rotorModel->setPosition(position + _rotorOffset);
}

void Helicopter::setScale(const glm::vec3 &scale)
{
	_corpsModel->setScale(scale);

	if (_isMount)
		_rotorModel->setScale(scale);
}

void Helicopter::setRotation(const glm::vec3 &rotation)
{
	_corpsModel->setRotation(rotation);

	if (_isMount)
		_rotorModel->setRotation(rotation);
}

void Helicopter::setRotation(const glm::vec3 &axis, GLfloat angle)
{
	_corpsModel->setRotation(axis, angle);

	if (_isMount)
		_rotorModel->setRotation(axis, angle);
}

void Helicopter::addPosition(const glm::vec3 &position)
{
	_corpsModel->addPosition(position);

	if (_isMount)
		_rotorModel->addPosition(position + _rotorOffset);
}

void Helicopter::addScale(const glm::vec3 &scale)
{
	_corpsModel->addScale(scale);

	if (_isMount)
		_rotorModel->addScale(scale);
}

void Helicopter::addRotation(const glm::vec3 &rotation)
{
	_corpsModel->addRotation(rotation);

	if (_isMount)
		_rotorModel->addRotation(rotation);
}

void Helicopter::addRotation(const glm::vec3 &axis, GLfloat angle)
{
	_corpsModel->addRotation(axis, angle);

	if (_isMount)
		_rotorModel->addRotation(axis, angle);
}
