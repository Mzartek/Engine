uniform sampler2D colorTexture;

in vec4 color;
in vec4 texCoord;

void main(void)
{
	gl_FragColor = texture2D(colorTexture, texCoord) * color;
}