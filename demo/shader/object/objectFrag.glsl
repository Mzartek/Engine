#version 330

uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

uniform sampler2D colorTexture;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec3 outMaterial;

void main(void)
{
    vec4 color = texture(colorTexture, texCoord);

    if(color.a > 0.5)
    {
        outNormal = vec4(normalize(normal), matShininess);
        outMaterial =
            uvec3(0xFF000000 & uvec3(ivec3(color.xyz * 255) << 24)) |
            uvec3(0x00FF0000 & ivec3(matAmbient.xyz * 255) << 16) |
            uvec3(0x0000FF00 & ivec3(matDiffuse.xyz * 255) << 8) |
            uvec3(0x000000FF & ivec3(matSpecular.xyz * 255));
		gl_FragDepth = gl_FragCoord.z;
    }
    else
    {
        outNormal = texelFetch(normalTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
        outMaterial = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
		gl_FragDepth = texelFetch(depthTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).z;
    }
}
