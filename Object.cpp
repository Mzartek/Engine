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

void engine::Object::setAmbiant(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _mat_ambiant[0] = x;
  _mat_ambiant[1] = y;
  _mat_ambiant[2] = z;
  _mat_ambiant[3] = w;
}

void engine::Object::setDiffuse(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _mat_diffuse[0] = x;
  _mat_diffuse[1] = y;
  _mat_diffuse[2] = z;
  _mat_diffuse[3] = w;
}

void engine::Object::setSpecular(const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
  _mat_specular[0] = x;
  _mat_specular[1] = y;
  _mat_specular[2] = z;
  _mat_specular[3] = w;
}

void engine::Object::setShininess(const GLfloat &x)
{
  _mat_shininess[0] = x;
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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(8, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(5*sizeof(GLfloat)));
  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(8);
  glDisableVertexAttribArray(2);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

#undef BUFFER_OFFSET
