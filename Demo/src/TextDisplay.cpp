#include "TextDisplay.hpp"

TextDisplay::TextDisplay(void)
{
	_textProgram = new_ref(Engine::ShaderProgram(
		"../share/Demo/shader/text/textVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/text/textFrag.glsl"));

	_text = new_ref(Engine::TextArray(_textProgram));

	_text->setFont("../share/Demo/resources/font/SIXTY.TTF", 100, 255, 255, 0);
}

TextDisplay::~TextDisplay(void)
{
	release_ref(_textProgram);
	release_ref(_text);
}

Engine::TextArray *TextDisplay::getText(void) const
{
	return _text;
}