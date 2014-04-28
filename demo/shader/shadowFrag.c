#version 330

//Final Out
out float fragmentDepth;
 
void main()
{
  fragmentDepth = gl_FragCoord.z;
}
