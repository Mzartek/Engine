#ifndef MATRIX
#define MATRIX

#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

  void NormalizeVector(float *pvector);
  void ComputeNormalOfPlane(float *normal, const float *pvector1, const float *pvector2);
  void matrixMultiply(float *result, const float *matrix1, const float *matrix2);
  void matrixLoadIdentity(float *matrix);
  void matrixLoadBias(float *matrix);
  void matrixNormalFromModel(float *result, const float *matrix);
  void matrixOrtho(float *matrix, const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal);
  void matrixPerspective(float *matrix, const float fovyInDegrees, const float aspectRatio, const float znear, const float zfar);
  void matrixLookAt(float *matrix, const float *eyePosition3D, const float *center3D, const float *upVector3D);
  void matrixTranslate(float *matrix, const float x, const float y, const float z);
  void matrixRotate(float *matrix, const float angleInDegrees, const float x, const float y, const float z);
  void matrixScale(float *matrix, const float x, const float y, const float z);

#ifdef __cplusplus
}
#endif

#endif
