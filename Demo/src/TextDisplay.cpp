#include "TextDisplay.hpp"

TextDisplay::TextDisplay(void)
{
	_textProgram = std::shared_ptr<Graphics::ShaderProgram>(new Graphics::ShaderProgram(
		"../share/Demo/shader/text/textVert.glsl",
		NULL,
		NULL,
		NULL,
		"../share/Demo/shader/text/textFrag.glsl"));

	_text = std::shared_ptr<Graphics::TextArray>(new Graphics::TextArray(_textProgram));

	_text->setFont("../share/Demo/resources/font/SIXTY.TTF", 200, 255, 255, 255);
}

TextDisplay::~TextDisplay(void)
{
}

const std::shared_ptr<Graphics::TextArray> &TextDisplay::getText(void) const
{
	return _text;
}