#include "include/Engine/ShaderLoader.hpp"

engine::ShaderLoader::ShaderLoader(void)
{
  _id = 0;
}

engine::ShaderLoader::~ShaderLoader(void)
{
}

GLuint engine::ShaderLoader::getId(void)
{
  return _id;
}

int engine::ShaderLoader::loadShader(const char* filename, GLenum type)
{
  char *content, *log;
  GLsizei logsize;
  GLint status;
  
  _id = glCreateShader(type);
  if(_id == 0)
    {
      std::cerr << "Error while creating shader" << std::endl;
      exit(1);
    }
  
  content = readText(filename);

  glShaderSource(_id, 1, (const char**)&content, NULL);
  glCompileShader(_id);
  glGetShaderiv(_id, GL_COMPILE_STATUS, &status);
  if(status != GL_TRUE)
    {
      glGetShaderiv(_id, GL_INFO_LOG_LENGTH, &logsize);
        
      log = new char[logsize + 1];
      if(log == NULL)
        {
	  std::cerr << "Error in the allocation for a shader log"  << std::endl;
	  exit(1);
        }

      log[logsize] = '\0';
        
      glGetShaderInfoLog(_id, logsize, &logsize, log);
      std::cerr << "Error while compiling shader: " << filename << std::endl << log << std::endl;
        
      glDeleteShader(_id);
      delete log;
      return 0;
    }
  
  delete content;
  return 1;
}

void engine::ShaderLoader::deleteShader(GLuint id)
{
  if(glIsShader(id))
    glDeleteShader(id);
}
