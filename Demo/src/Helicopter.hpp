#ifndef HELICOPTER_HEADER
#define HELICOPTER_HEADER

#include <Engine/Graphics/StaticModel.hpp>

class Helicopter
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::StaticModel *_model;
public:
	Helicopter(void);
	~Helicopter(void);
	Engine::StaticModel *getModel(void) const;
};

#endif
