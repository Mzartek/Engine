#version 440

#define SKELETAL_MODEL_MAX_BONES 200

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	mat4 normalMatrix;
};

layout (binding = 4) uniform bonesBuffer
{
	mat4 bones[SKELETAL_MODEL_MAX_BONES];
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in ivec4 index0;
layout(location = 5) in ivec4 index1;
layout(location = 6) in vec4 weight0;
layout(location = 7) in vec4 weight1;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main()
{
    mat4 boneTransform = 
		bones[index0[0]] * weight0[0] + 
		bones[index0[1]] * weight0[1] + 
		bones[index0[2]] * weight0[2] + 
		bones[index0[3]] * weight0[3] + 
		bones[index1[0]] * weight1[0] + 
		bones[index1[1]] * weight1[1] + 
		bones[index1[2]] * weight1[2] +
		bones[index1[3]] * weight1[3];
	
	gl_Position = MVP * boneTransform * vec4(vertex, 1.0);
	VertOut.texCoord = texCoord;
}
