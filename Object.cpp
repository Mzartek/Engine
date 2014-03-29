#include <Engine/Object.hpp>

engine::Object::Object(void)
{
  unsigned i;
  _idObject = 0;
  _idElementObject = 0;
  _idTextureObject = 0;
  for(i=0 ; i<4 ; i++)
    {
      _matAmbient[i]=1.0;
      _matDiffuse[i]=1.0;
      _matSpecular[i]=1.0;
    }
  _matShininess[0]=1.0;
  _program = NULL;
}

engine::Object::~Object(void)
{
  if(glIsBuffer(_idObject))
    glDeleteBuffers(1, &_idObject);
  if(glIsBuffer(_idElementObject))
    glDeleteBuffers(1, &_idElementObject);
  if(glIsTexture(_idTextureObject))
    glDeleteTextures(1, &_idTextureObject);
}

void engine::Object::setShaderProgram(ShaderProgram *program)
{
  _program = program;
  _matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  _matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  _matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  _matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  
  _vertexAttribLocation = glGetAttribLocation(_program->getId(), "vertexArray");
  _textureAttribLocation = glGetAttribLocation(_program->getId(), "textureArray");
  _normalAttribLocation = glGetAttribLocation(_program->getId(), "normalArray");
}

void engine::Object::setIdObject(const GLuint &id)
{
  _idObject = id;
}

void engine::Object::setIdElementObject(const GLuint &id, const GLuint &num)
{
  _idElementObject = id;
  _numElement = num;
}

void engine::Object::setIdTextureObject(const GLuint &id)
{
  _idTextureObject = id;
}

void engine::Object::setAmbient(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matAmbient[0] = x;
  _matAmbient[1] = y;
  _matAmbient[2] = z;
  _matAmbient[3] = w;
}

void engine::Object::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matDiffuse[0] = x;
  _matDiffuse[1] = y;
  _matDiffuse[2] = z;
  _matDiffuse[3] = w;
}

void engine::Object::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _matSpecular[0] = x;
  _matSpecular[1] = y;
  _matSpecular[2] = z;
  _matSpecular[3] = w;
}

void engine::Object::setShininess(const GLfloat &x)
{
  _matShininess[0] = x;
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void engine::Object::display(void) const
{
  _program->use();
  glUniform4fv(_matAmbientLocation,  1, _matAmbient);
  glUniform4fv(_matDiffuseLocation,  1, _matDiffuse);
  glUniform4fv(_matSpecularLocation,  1, _matSpecular);
  glUniform1fv(_matShininessLocation, 1, _matShininess);
  
  glBindBuffer(GL_ARRAY_BUFFER, _idObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idElementObject);
  glBindTexture(GL_TEXTURE_2D, _idTextureObject);
  
  glEnableVertexAttribArray(_vertexAttribLocation); // GL_VERTEX_ARRAY
  glEnableVertexAttribArray(_textureAttribLocation); // GL_TEXTURE_COORD_ARRAY
  glEnableVertexAttribArray(_normalAttribLocation); // GL_NORMAL_ARRAY

  glVertexAttribPointer(_vertexAttribLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(_textureAttribLocation, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat)));
  glVertexAttribPointer(_normalAttribLocation, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(5*sizeof(GLfloat)));
  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
  glDisableVertexAttribArray(_vertexAttribLocation);
  glDisableVertexAttribArray(_textureAttribLocation);
  glDisableVertexAttribArray(_normalAttribLocation);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

#undef BUFFER_OFFSET
