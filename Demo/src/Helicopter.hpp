#ifndef HELICOPTER_HEADER
#define HELICOPTER_HEADER

#include <Engine/Engine.hpp>

class Helicopter
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::Model *_model;
public:
	Helicopter(void);
	~Helicopter(void);
	Engine::Model *getModel(void) const;
};

#endif
