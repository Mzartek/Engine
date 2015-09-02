#ifndef TORCHLIGHT_HEADER
#define TORCHLIGHT_HEADER

#include <Engine/Graphics/Light/SpotLight.hpp>

using namespace Engine;

class TorchLight
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _spotLightProgram;
	std::shared_ptr<Graphics::SpotLight> _light;
public:
	TorchLight(void);
	~TorchLight(void);
	const std::shared_ptr<Graphics::SpotLight> &getLight(void) const;
};

#endif