#version 440

layout (binding = 0) uniform matrixBuffer
{
     mat4 MVP;
     mat4 projectionMatrix;
     mat4 viewMatrix;
     mat4 modelMatrix;
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
     vec4 particle = GeomIn[0].particle;
     float xdim = 0.2;
     float ydim = 1.0;

     mat4 finalMatrix = modelMatrix;
     
     finalMatrix[3][0] = particle.x;
     finalMatrix[3][1] = particle.y;
     finalMatrix[3][2] = particle.z;

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
