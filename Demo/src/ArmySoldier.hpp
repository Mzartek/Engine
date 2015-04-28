#ifndef ARMYSOLDIER_HEADER
#define ARMYSOLDIER_HEADER

#include <Engine/Engine.hpp>

class ArmySoldier
{
private:
	Engine::ShaderProgram *_objectProgram;
	Engine::ShaderProgram *_depthMapProgram;
	Engine::Model *_model;
public:
	ArmySoldier(void);
	~ArmySoldier(void);
	Engine::Model *getModel(void) const;
};

#endif