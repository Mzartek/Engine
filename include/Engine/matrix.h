#ifndef MATRIX
#define MATRIX

#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

  void NormalizeVector(float *pvector);
  void ComputeNormalOfPlane(float *normal, const float *pvector1, const float *pvector2);
  void MultiplyMatrices4by4OpenGL_FLOAT(float *result, const float *matrix1, const float *matrix2);

  void matrixLoadIdentity(float *matrix);
  void matrixLoadBias(float *matrix);
  void matrixOrtho(float *matrix, float left, float right, float bottom, float top, float nearVal, float farVal);
  void matrixPerspective(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
  void matrixLookAt(float *matrix, float *eyePosition3D, float *center3D, float *upVector3D);
  void matrixTranslate(float *matrix, float x, float y, float z);
  void matrixRotate(float *matrix, float angleInRadians, float x, float y, float z);
  void matrixScale(float *matrix, float x, float y, float z);

#ifdef __cplusplus
}
#endif

#endif
