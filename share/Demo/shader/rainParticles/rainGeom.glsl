#version 440

uniform sampler2D depthTexture;

layout (binding = 0) uniform matrixBuffer
{
     mat4 projectionMatrix;
     mat4 viewMatrix;
};

layout (binding = 1) uniform cameraBuffer
{
    vec3 camPosition;
    vec3 camTarget;
};

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VertexData
{
     vec4 particle;
} GeomIn[];

out VertexData
{
     vec2 texCoord;
} GeomOut;

void main(void)
{
     float xdim = 0.2;
     float ydim = 1.0;

     vec4 particle = GeomIn[0].particle;

	 mat4 finalMatrix = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		particle.x, particle.y, particle.z, 1.0
	 );

     finalMatrix = viewMatrix * finalMatrix;
     
     finalMatrix[0][0] = 1;
     finalMatrix[0][1] = 0;
     finalMatrix[0][2] = 0;
     
     finalMatrix[2][0] = 0;
     finalMatrix[2][1] = 0;
     finalMatrix[2][2] = 1;

     finalMatrix = projectionMatrix * finalMatrix;

     gl_Position = finalMatrix * vec4(-xdim, -ydim, 0, 1);
     GeomOut.texCoord = vec2(1, 1);
     EmitVertex();

     gl_Position = finalMatrix * vec4(+xdim, -ydim, 0, 1);
     GeomOut.texCoord = vec2(0, 1);
     EmitVertex();

     gl_Position = finalMatrix * vec4(-xdim, +ydim, 0, 1);
     GeomOut.texCoord = vec2(1, 0);
     EmitVertex();

     gl_Position = finalMatrix * vec4(+xdim, +ydim, 0, 1);
     GeomOut.texCoord = vec2(0, 0);
     EmitVertex();

     EndPrimitive();
}
