#ifndef ARMYSOLDIER_HEADER
#define ARMYSOLDIER_HEADER

#include <Engine/Graphics/SkeletalModel.hpp>

class AnimModel
{
private:
	std::shared_ptr<Engine::ShaderProgram> _objectProgram;
	std::shared_ptr<Engine::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Engine::SkeletalModel> _model;

public:
	AnimModel(void);
	~AnimModel(void);
	const std::shared_ptr<Engine::SkeletalModel> &getModel(void) const;
};

#endif