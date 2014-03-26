uniform sampler2D colorTexture;

in vec4 color;
in vec2 texCoord;

void main(void)
{
	gl_FragColor = texture(colorTexture, texCoord) * color;
}