#include <Engine/ShaderProgram.hpp>

engine::ShaderProgram::ShaderProgram(void)
{
  _id = glCreateProgram();
  if(_id == 0)
    {
      std::cerr << "Error while creating program" << std::endl;
      exit(1);
    }
}

engine::ShaderProgram::~ShaderProgram(void)
{
  glDeleteProgram(_id);
}

GLuint engine::ShaderProgram::getId(void)
{
  return _id;
}

void engine::ShaderProgram::reset(void)
{
  glDeleteProgram(_id);
  _id = glCreateProgram();
  if(_id == 0)
    {
      std::cerr << "Error while creating program" << std::endl;
      exit(1);
    }
}

void engine::ShaderProgram::attachShader(ShaderObject *shader)
{
  glAttachShader(_id, shader->getId());
}

void engine::ShaderProgram::detachShader(ShaderObject *shader)
{
  glDetachShader(_id, shader->getId());
}

int engine::ShaderProgram::link(void)
{
  char *log;
  GLsizei logsize;
  GLint status;
  
  glLinkProgram(_id);
  
  glGetProgramiv(_id, GL_LINK_STATUS, &status);
  if(status != GL_TRUE)
    {
      glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &logsize);
        
      log = new char[logsize + 1];
      assert(log != NULL);

      log[logsize] = '\0';
        
      glGetProgramInfoLog(_id, logsize, &logsize, log);
      std::cerr << "Error while linking program: " << _id << std::endl << log << std::endl;
        
      delete log;
      return 0;
    }

  return 1;
}

void engine::ShaderProgram::use(void)
{
  glUseProgram(_id);
}
