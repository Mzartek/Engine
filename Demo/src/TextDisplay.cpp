#include "TextDisplay.hpp"

TextDisplay::TextDisplay(void)
{
	_textProgram = std::shared_ptr<Engine::ShaderProgram>(new Engine::ShaderProgram(
		"../share/Demo/shader/text/textVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/text/textFrag.glsl"));

	_text = std::shared_ptr<Engine::TextArray>(new Engine::TextArray(_textProgram));

	_text->setFont("../share/Demo/resources/font/SIXTY.TTF", 100, 255, 255, 0);
}

TextDisplay::~TextDisplay(void)
{
}

const std::shared_ptr<Engine::TextArray> &TextDisplay::getText(void) const
{
	return _text;
}