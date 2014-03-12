#include <Engine/Object.hpp>

engine::Object::Object(void)
{
  _idObject = 0;
  _idElementObject = 0;
  _idTextureObject = 0;
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

void engine::Object::setIdObject(GLuint const &id)
{
  _idObject = id;
}

void engine::Object::setIdElementObject(GLuint const &id, GLuint const &num)
{
  _idElementObject = id;
  _numElement = num;
}

void engine::Object::setIdTextureObject(GLuint const &id)
{
  _idTextureObject = id;
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

void engine::Object::display(void) const
{ 
  glBindBuffer(GL_ARRAY_BUFFER, _idObject);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idElementObject);
  glBindTexture(GL_TEXTURE_2D, _idTextureObject);
  
  glEnableVertexAttribArray(0); // GL_VERTEX_ARRAY
  glEnableVertexAttribArray(8); // GL_TEXTURE_COORD_ARRAY
  glEnableVertexAttribArray(2); // GL_NORMAL_ARRAY

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), BUFFER_OFFSET(6*sizeof(GLfloat)));
  glDrawElements(GL_QUADS, _numElement, GL_UNSIGNED_INT, 0);
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(8);
  glDisableVertexAttribArray(2);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

#undef BUFFER_OFFSET
