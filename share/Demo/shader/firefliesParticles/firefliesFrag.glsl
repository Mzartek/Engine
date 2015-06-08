#version 440

uniform sampler2D colorTexture;
uniform sampler2D depthTexture;

in VertexData
{
     vec2 texCoord;
     vec3 color;
     float life;
} FragIn;

layout(location = 0) out vec4 outColor;

void main(void)
{
     vec4 color = texture(colorTexture, FragIn.texCoord);
     color.xyz = mix(color.xyz, FragIn.color, FragIn.life/100);

     float depth = texelFetch(depthTexture, ivec2(gl_FragCoord.xy), 0).x;

     if (depth < gl_FragCoord.z)
	  discard;
	
     outColor = vec4(color.xyz, color.a * ((100 - FragIn.life) / 100));
}
