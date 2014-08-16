#version 330

uniform sampler2D normalTexture;
uniform usampler2D materialTexture;
uniform sampler2D depthTexture;

uniform sampler2D colorTexture;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform uvec2 screen;

in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec4 outNormal;
layout(location = 1) out uvec4 outMaterial;

vec2 screenTexCoord = vec2(gl_FragCoord.x/screen.x, gl_FragCoord.y/screen.y);

void main(void)
{
    vec4 color = texture(colorTexture, vec2(texCoord.x, 1.0 - texCoord.y));

    if(color.a > 0.5)
    {
        outNormal = vec4(normalize(normal), matShininess);
        outMaterial =
            uvec4(0xFF000000 & uvec4(ivec4(color * 255) << 24)) |
            uvec4(0x00FF0000 & ivec4(matAmbient * 255) << 16) |
            uvec4(0x0000FF00 & ivec4(matDiffuse * 255) << 8) |
            uvec4(0x000000FF & ivec4(matSpecular * 255));
		gl_FragDepth = gl_FragCoord.z;
    }
    else
    {
        outNormal = texture(normalTexture, screenTexCoord);
        outMaterial = texture(materialTexture, screenTexCoord);
		gl_FragDepth = texture(depthTexture, screenTexCoord).z;
    }
}
