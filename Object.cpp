#include <Engine/Object.hpp>

engine::Object::Object(void)
{
  unsigned i;
  _idVAO = 0;
  _idVBO[0] = 0;
  _idVBO[1] = 0;
  _idTexture = 0;
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
  if(glIsVertexArray(_idVAO))
    glDeleteVertexArrays(1, &_idVAO);
  if(glIsBuffer(_idVBO[0]))
    glDeleteBuffers(1, &_idVBO[0]);
  if(glIsBuffer(_idVBO[1]))
    glDeleteBuffers(1, &_idVBO[1]);
  if(glIsTexture(_idTexture))
    glDeleteTextures(1, &_idTexture);
}

void engine::Object::setTexture(const GLuint &id)
{
  _idTexture = id;
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

void engine::Object::load(const GLuint &sizeVertexArray, const GLfloat *vertexArray,
			  const GLuint &sizeIndexArray, const GLuint *indexArray,
			  ShaderProgram *program)
{
  _numElement = sizeIndexArray/sizeof(GLuint);
  
  _program = program;
  _textureLocation = glGetUniformLocation(_program->getId(), "colorTexture");
  _matAmbientLocation = glGetUniformLocation(_program->getId(), "matAmbient");
  _matDiffuseLocation = glGetUniformLocation(_program->getId(), "matDiffuse");
  _matSpecularLocation = glGetUniformLocation(_program->getId(), "matSpecular");
  _matShininessLocation = glGetUniformLocation(_program->getId(), "matShininess");
  

  // Vertex Array et Vertex Buffer Object
  glGenVertexArrays(1, &_idVAO);
  glBindVertexArray(_idVAO);
  
  glGenBuffers(1, &_idVBO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, _idVBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeVertexArray, vertexArray, GL_STATIC_DRAW);
  
  glGenBuffers(1, &_idVBO[1]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _idVBO[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndexArray, indexArray, GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(0));
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(3*sizeof(GLfloat)));
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), BUFFER_OFFSET(5*sizeof(GLfloat)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

#undef BUFFER_OFFSET

void engine::Object::display(void) const
{
  _program->use();
  
  glBindVertexArray(_idVAO);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _idTexture);
  glUniform1i(_textureLocation, 0);
  
  glUniform4fv(_matAmbientLocation,  1, _matAmbient);
  glUniform4fv(_matDiffuseLocation,  1, _matDiffuse);
  glUniform4fv(_matSpecularLocation,  1, _matSpecular);
  glUniform1fv(_matShininessLocation, 1, _matShininess);

  glDrawElements(GL_TRIANGLES, _numElement, GL_UNSIGNED_INT, 0);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glBindVertexArray(0);
  
  glUseProgram(0);
}
