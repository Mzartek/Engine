#ifndef MATRIX
#define MATRIX

#ifdef WIN32
#ifdef ENGINE_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
#else
#define DLLAPI
#endif

#include <math.h>
#include <string.h>

extern DLLAPI void NormalizeVector(float *pvector);
extern DLLAPI void ComputeNormalOfPlane(float *normal, const float *pvector1, const float *pvector2);
extern DLLAPI void matrixMultiply(float *result, const float *matrix1, const float *matrix2);
extern DLLAPI void matrixLoadIdentity(float *matrix);
extern DLLAPI void matrixLoadBias(float *matrix);
extern DLLAPI void matrixNormalFromModel(float *result, const float *matrix);
extern DLLAPI void matrixOrtho(float *matrix, const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal);
extern DLLAPI void matrixPerspective(float *matrix, const float fovyInDegrees, const float aspectRatio, const float znear, const float zfar);
extern DLLAPI void matrixLookAt(float *matrix, const float *eyePosition3D, const float *center3D, const float *upVector3D);
extern DLLAPI void matrixTranslate(float *matrix, const float x, const float y, const float z);
extern DLLAPI void matrixRotate(float *matrix, const float angleInDegrees, const float x, const float y, const float z);
extern DLLAPI void matrixScale(float *matrix, const float x, const float y, const float z);

#endif
