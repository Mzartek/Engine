#ifndef ARMYSOLDIER_HEADER
#define ARMYSOLDIER_HEADER

#include <Engine/Graphics/Model/Skeletal/SkeletalModel.hpp>

using namespace Engine;

class AnimModel
{
	std::shared_ptr<Graphics::ShaderProgram> _objectProgram;
	std::shared_ptr<Graphics::ShaderProgram> _depthMapProgram;
	std::shared_ptr<Graphics::SkeletalModel> _model;

public:
	AnimModel(void);
	~AnimModel(void);
	const std::shared_ptr<Graphics::SkeletalModel> &getModel(void) const;
};

#endif
