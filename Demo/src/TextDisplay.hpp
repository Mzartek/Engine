#ifndef TEXTDISPLAY_HEADER
#define TEXTDISPLAY_HEADER

#include <Engine/Graphics/TextArray.hpp>

using namespace Engine;

class TextDisplay
{
private:
	std::shared_ptr<Graphics::ShaderProgram> _textProgram;
	std::shared_ptr<Graphics::TextArray> _text;

public:
	TextDisplay(void);
	~TextDisplay(void);
	const std::shared_ptr<Graphics::TextArray> &getText(void) const;
};

#endif