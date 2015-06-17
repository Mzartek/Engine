#ifndef SCREENDISPLAY_HEADER
#define SCREENDISPLAY_HEADER

#include <Engine/Graphics/GraphicsRenderer.hpp>
#include <Engine/Graphics/GBuffer.hpp>

using namespace Engine;

class ScreenDisplay
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _backgroundProgram;
	std::shared_ptr<Graphics::GBuffer> _gBuffer;

public:
	ScreenDisplay(void);
	~ScreenDisplay(void);
	const std::shared_ptr<Graphics::GBuffer> &getGBuffer(void) const;
};

#endif