#ifndef TEXTDISPLAY_HEADER
#define TEXTDISPLAY_HEADER

#include <Engine/Graphics/TextArray.hpp>

class TextDisplay
{
private:
	Engine::ShaderProgram *_textProgram;
	Engine::TextArray *_text;
public:
	TextDisplay(void);
	~TextDisplay(void);
	Engine::TextArray *getText(void) const;
};

#endif