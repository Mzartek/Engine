#version 330

uniform sampler2D colorTexture;
uniform usampler2D gBufferMaterialTexture;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec3 outPositionTexture;
layout(location = 1) out vec4 outNormalTexture;
layout(location = 2) out uvec4 outMaterialTexture;

void main(void)
{
	vec4 srcAmb, srcDiff, srcSpec;
	vec4 dstAmb, finAmb;
	uvec4 dstMat = texelFetch(gBufferMaterialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);

	outPositionTexture = position;
	outNormalTexture = vec4(normalize(normal), matShininess);

	srcAmb = texture(colorTexture, texCoord) * matAmbient;
	srcDiff = texture(colorTexture, texCoord) * matDiffuse;
	srcSpec = texture(colorTexture, texCoord) * matSpecular;

	dstAmb = vec4(0x000000FF & (ivec4(dstMat) >> 24)) / 255;
	finAmb = (srcAmb * srcAmb.a) + (dstAmb * (1 - srcAmb.a));

	outMaterialTexture =
		uvec4(0xFF000000 & uvec4(ivec4(finAmb * 255) << 24)) |
		uvec4(0x00FF0000 & ivec4(srcDiff * 255) << 16) |
		uvec4(0x0000FF00 & ivec4(srcSpec * 255) << 8) |
		uvec4(0, 0, 0, 0);

}
