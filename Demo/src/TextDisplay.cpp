#include "TextDisplay.hpp"

TextDisplay::TextDisplay(void)
{
	_textProgram = new_ptr(Engine::ShaderProgram(
		"../share/Demo/shader/text/textVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/text/textFrag.glsl"));

	_text = new_ptr(Engine::TextArray(_textProgram));

	_text->setFont("../share/Demo/resources/font/SIXTY.TTF", 100, 255, 255, 0);
}

TextDisplay::~TextDisplay(void)
{
	release_ptr(_textProgram);
	release_ptr(_text);
}

Engine::TextArray *TextDisplay::getText(void) const
{
	return _text;
}