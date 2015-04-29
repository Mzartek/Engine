#version 440

#define SKELETAL_MODEL_MAX_BONES 200

layout (binding = 0) uniform matrixBuffer
{
	mat4 MVP;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;
	mat4 normalMatrix;
	mat4 bones[SKELETAL_MODEL_MAX_BONES];
};

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 tangent;
layout(location = 4) in ivec4 index;
layout(location = 5) in vec4 weights;

out VertexData
{
	vec2 texCoord;
} VertOut;

void main()
{
    mat4 BoneTransform = bones[index[0]] * weights[0];
    BoneTransform += bones[index[1]] * weights[1];
    BoneTransform += bones[index[2]] * weights[2];
    BoneTransform += bones[index[3]] * weights[3];
	
	gl_Position = MVP * BoneTransform * vec4(vertex, 1.0);
	VertOut.texCoord = texCoord;
}
