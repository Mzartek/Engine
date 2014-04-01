#version 330 core

varying out float fragmentDepth;
 
void main()
{
  fragmentDepth = gl_FragCoord.z;
}
