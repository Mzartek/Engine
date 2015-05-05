#ifndef TEXTDISPLAY_HEADER
#define TEXTDISPLAY_HEADER

#include <Engine/Graphics/TextArray.hpp>

class TextDisplay
{
private:
	std::shared_ptr<Engine::ShaderProgram> _textProgram;
	std::shared_ptr<Engine::TextArray> _text;
public:
	TextDisplay(void);
	~TextDisplay(void);
	const std::shared_ptr<Engine::TextArray> &getText(void) const;
};

#endif