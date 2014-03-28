uniform sampler2D colorTexture;

in vec4 color;
in vec2 texCoord;

varying out vec4 fragColor;

void main(void)
{
	fragColor = texture(colorTexture, texCoord) * color;
}