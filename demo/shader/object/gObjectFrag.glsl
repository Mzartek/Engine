#version 330

uniform sampler2D colorTexture;

uniform material
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

in VertexData
{
	vec2 texCoord;
	vec3 normal;
} FragIn;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

void main(void)
{
    vec4 color = texture(colorTexture, vec2(FragIn.texCoord.x, 1.0 - FragIn.texCoord.y));

    if(color.a > 0.5)
    {
        outNormal = vec4(normalize(FragIn.normal), shininess);
        outMaterial =
            uvec4(0xFF000000 & uvec4(ivec4(color * 255) << 24)) |
            uvec4(0x00FF0000 & ivec4(ambient * 255) << 16) |
            uvec4(0x0000FF00 & ivec4(diffuse * 255) << 8) |
            uvec4(0x000000FF & ivec4(specular * 255));
		gl_FragDepth = gl_FragCoord.z;
    }
    else
		gl_FragDepth = 1.0;
}
