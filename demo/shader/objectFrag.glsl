#version 330

uniform sampler2D positionTexture;
uniform sampler2D normalTexture;
uniform usampler2D materialTexture;

uniform sampler2D colorTexture;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec4 outNormal;
layout(location = 2) out uvec3 outMaterial;

void main(void)
{
    vec4 albedo = texture(colorTexture, texCoord);

    if(albedo.a == 1.0 && matAmbient.a == 1.0 && matDiffuse.a == 1.0 && matSpecular.a == 1.0)
    {
        outPosition = position;
        outNormal = vec4(normalize(normal), matShininess);
        outMaterial =
            uvec3(0xFF000000 & uvec3(ivec3(albedo.xyz * 255) << 24)) |
            uvec3(0x00FF0000 & ivec3(matAmbient.xyz * 255) << 16) |
            uvec3(0x0000FF00 & ivec3(matDiffuse.xyz * 255) << 8) |
            uvec3(0x000000FF & ivec3(matSpecular.xyz * 255));
    }
    else
    {
        outPosition = texelFetch(positionTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
        outNormal = texelFetch(normalTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0);
        outMaterial = texelFetch(materialTexture, ivec2(gl_FragCoord.x, gl_FragCoord.y), 0).xyz;
    }
}
