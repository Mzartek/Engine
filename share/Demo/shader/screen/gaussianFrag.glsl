#version 440

uniform sampler2D inputTexture;

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

vec4 gaussianFilter(void)
{
	vec3 outColor = texture(inputTexture, FragIn.texCoord).xyz;
	
	if (FragIn.texCoord.x > 0.0 && FragIn.texCoord.x < 1.0 &&
			FragIn.texCoord.y > 0.0 && FragIn.texCoord.y < 1.0)
	{
		float num = 0.0;
		for (int i = -2; i < 2; i++)
		{
			for (int j = -2; j < 2; j++)
			{
				outColor += texelFetch(inputTexture, ivec2(gl_FragCoord.x + i, gl_FragCoord.y + j), 0).xyz;
				num += 1.0;
			}
		}
		
		outColor /= num;
	}	
	
	return vec4(outColor, 1.0);
}

void main(void)
{
	fragColor = gaussianFilter();
}
