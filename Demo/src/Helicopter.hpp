#ifndef HELICOPTER_HEADER
#define HELICOPTER_HEADER

#include <Engine/Graphics/StaticModel.hpp>

class Helicopter
{
private:
	std::shared_ptr<Engine::ShaderProgram> _objectProgram;
	std::shared_ptr<Engine::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Engine::StaticModel> _model;
public:
	Helicopter(void);
	~Helicopter(void);
	const std::shared_ptr<Engine::StaticModel> &getModel(void) const;
};

#endif
