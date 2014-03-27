#include <Engine/matrix.h>

void matrixPerspectiveBis(float *matrix, float left, float right, float bottom, float top, float znear, float zfar)
{
  float temp, temp2, temp3, temp4;
  temp = 2.0 * znear;
  temp2 = right - left;
  temp3 = top - bottom;
  temp4 = zfar - znear;
  matrix[0] = temp / temp2;
  matrix[1] = 0.0;
  matrix[2] = 0.0;
  matrix[3] = 0.0;
  matrix[4] = 0.0;
  matrix[5] = temp / temp3;
  matrix[6] = 0.0;
  matrix[7] = 0.0;
  matrix[8] = (right + left) / temp2;
  matrix[9] = (top + bottom) / temp3;
  matrix[10] = (-zfar - znear) / temp4;
  matrix[11] = -1.0;
  matrix[12] = 0.0;
  matrix[13] = 0.0;
  matrix[14] = (-temp * zfar) / temp4;
  matrix[15] = 0.0;
}

void NormalizeVector(float *pvector)
{
  float normalizingConstant;
  normalizingConstant=1.0/sqrtf(pvector[0]*pvector[0]+pvector[1]*pvector[1]+pvector[2]*pvector[2]);
  pvector[0]*=normalizingConstant;
  pvector[1]*=normalizingConstant;
  pvector[2]*=normalizingConstant;
}

void ComputeNormalOfPlane(float *normal, const float *pvector1, const float *pvector2)
{
  normal[0]=(pvector1[1]*pvector2[2])-(pvector1[2]*pvector2[1]);
  normal[1]=(pvector1[2]*pvector2[0])-(pvector1[0]*pvector2[2]);
  normal[2]=(pvector1[0]*pvector2[1])-(pvector1[1]*pvector2[0]);
}

void MultiplyMatrices4by4OpenGL_FLOAT(float *result, float *matrix1, float *matrix2)
{
  result[ 0]=matrix1[ 0]*matrix2[ 0]+matrix1[ 4]*matrix2[ 1]+matrix1[ 8]*matrix2[ 2]+matrix1[12]*matrix2[ 3];
  result[ 4]=matrix1[ 0]*matrix2[ 4]+matrix1[ 4]*matrix2[ 5]+matrix1[ 8]*matrix2[ 6]+matrix1[12]*matrix2[ 7];
  result[ 8]=matrix1[ 0]*matrix2[ 8]+matrix1[ 4]*matrix2[ 9]+matrix1[ 8]*matrix2[10]+matrix1[12]*matrix2[11];
  result[12]=matrix1[ 0]*matrix2[12]+matrix1[ 4]*matrix2[13]+matrix1[ 8]*matrix2[14]+matrix1[12]*matrix2[15];

  result[ 1]=matrix1[ 1]*matrix2[ 0]+matrix1[ 5]*matrix2[ 1]+matrix1[ 9]*matrix2[ 2]+matrix1[13]*matrix2[ 3];
  result[ 5]=matrix1[ 1]*matrix2[ 4]+matrix1[ 5]*matrix2[ 5]+matrix1[ 9]*matrix2[ 6]+matrix1[13]*matrix2[ 7];
  result[ 9]=matrix1[ 1]*matrix2[ 8]+matrix1[ 5]*matrix2[ 9]+matrix1[ 9]*matrix2[10]+matrix1[13]*matrix2[11];
  result[13]=matrix1[ 1]*matrix2[12]+matrix1[ 5]*matrix2[13]+matrix1[ 9]*matrix2[14]+matrix1[13]*matrix2[15];

  result[ 2]=matrix1[ 2]*matrix2[ 0]+matrix1[ 6]*matrix2[ 1]+matrix1[10]*matrix2[ 2]+matrix1[14]*matrix2[ 3];
  result[ 6]=matrix1[ 2]*matrix2[ 4]+matrix1[ 6]*matrix2[ 5]+matrix1[10]*matrix2[ 6]+matrix1[14]*matrix2[ 7];
  result[10]=matrix1[ 2]*matrix2[ 8]+matrix1[ 6]*matrix2[ 9]+matrix1[10]*matrix2[10]+matrix1[14]*matrix2[11];
  result[14]=matrix1[ 2]*matrix2[12]+matrix1[ 6]*matrix2[13]+matrix1[10]*matrix2[14]+matrix1[14]*matrix2[15];

  result[ 3]=matrix1[ 3]*matrix2[ 0]+matrix1[ 7]*matrix2[ 1]+matrix1[11]*matrix2[ 2]+matrix1[15]*matrix2[ 3];
  result[ 7]=matrix1[ 3]*matrix2[ 4]+matrix1[ 7]*matrix2[ 5]+matrix1[11]*matrix2[ 6]+matrix1[15]*matrix2[ 7];
  result[11]=matrix1[ 3]*matrix2[ 8]+matrix1[ 7]*matrix2[ 9]+matrix1[11]*matrix2[10]+matrix1[15]*matrix2[11];
  result[15]=matrix1[ 3]*matrix2[12]+matrix1[ 7]*matrix2[13]+matrix1[11]*matrix2[14]+matrix1[15]*matrix2[15];
}

//---------------------

void matrixLoadIdentity(float *matrix)
{
  unsigned i;
  for(i=0 ; i<16 ; i++)
    {
      if(i==0 || i==5 || i==10 || i==15)
	matrix[i]=1;
      else
	matrix[i]=0;
    }
}

void matrixPerspective(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar)
{
  float ymax, xmax;
  ymax = znear * tanf(fovyInDegrees * M_PI / 360.0);
  xmax = ymax * aspectRatio;
  matrixPerspectiveBis(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void matrixLookAt(float *matrix, float *eyePosition3D, float *center3D, float *upVector3D)
{
   float forward[3], side[3], up[3];
   float matrix2[16], resultMatrix[16];
   
   forward[0] = center3D[0] - eyePosition3D[0];
   forward[1] = center3D[1] - eyePosition3D[1];
   forward[2] = center3D[2] - eyePosition3D[2];
   NormalizeVector(forward);
   
   ComputeNormalOfPlane(side, forward, upVector3D);
   NormalizeVector(side);
   
   ComputeNormalOfPlane(up, side, forward);
   
   matrix2[0] = side[0];
   matrix2[4] = side[1];
   matrix2[8] = side[2];
   matrix2[12] = 0.0;
   
   matrix2[1] = up[0];
   matrix2[5] = up[1];
   matrix2[9] = up[2];
   matrix2[13] = 0.0;
   
   matrix2[2] = -forward[0];
   matrix2[6] = -forward[1];
   matrix2[10] = -forward[2];
   matrix2[14] = 0.0;
   
   matrix2[3] = matrix2[7] = matrix2[11] = 0.0;
   matrix2[15] = 1.0;
   
   MultiplyMatrices4by4OpenGL_FLOAT(resultMatrix, matrix, matrix2);
   matrixTranslate(resultMatrix, -eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);
   
   memcpy(matrix, resultMatrix, 16*sizeof(float));
}

void matrixTranslate(float *matrix, float x, float y, float z)
{
  matrix[12]=matrix[0]*x+matrix[4]*y+matrix[8]*z+matrix[12];
  matrix[13]=matrix[1]*x+matrix[5]*y+matrix[9]*z+matrix[13];
  matrix[14]=matrix[2]*x+matrix[6]*y+matrix[10]*z+matrix[14];
  matrix[15]=matrix[3]*x+matrix[7]*y+matrix[11]*z+matrix[15];
}

void matrixRotate(float *matrix, float angleInRadians, float x, float y, float z)
{
  float m[16], rotate[16];
  float OneMinusCosAngle, CosAngle, SinAngle;
  float A_OneMinusCosAngle, C_OneMinusCosAngle;
  CosAngle=cosf(angleInRadians);
  OneMinusCosAngle=1.0-CosAngle;
  SinAngle=sinf(angleInRadians);
  A_OneMinusCosAngle=x*OneMinusCosAngle;
  C_OneMinusCosAngle=z*OneMinusCosAngle;
	
  m[0]=matrix[0];
  m[1]=matrix[1];
  m[2]=matrix[2];
  m[3]=matrix[3];
  m[4]=matrix[4];
  m[5]=matrix[5];
  m[6]=matrix[6];
  m[7]=matrix[7];
  m[8]=matrix[8];
  m[9]=matrix[9];
  m[10]=matrix[10];
  m[11]=matrix[11];
  m[12]=matrix[12];
  m[13]=matrix[13];
  m[14]=matrix[14];
  m[15]=matrix[15];

  rotate[ 0]=x*A_OneMinusCosAngle+CosAngle;
  rotate[ 1]=y*A_OneMinusCosAngle+z*SinAngle;
  rotate[ 2]=z*A_OneMinusCosAngle-y*SinAngle;
  rotate[ 3]=0.0;

  rotate[ 4]=y*A_OneMinusCosAngle-z*SinAngle;
  rotate[ 5]=y*y*OneMinusCosAngle+CosAngle;
  rotate[ 6]=y*C_OneMinusCosAngle+x*SinAngle;
  rotate[ 7]=0.0;

  rotate[ 8]=x*C_OneMinusCosAngle+y*SinAngle;
  rotate[ 9]=y*C_OneMinusCosAngle-x*SinAngle;
  rotate[10]=z*C_OneMinusCosAngle+CosAngle;
  rotate[11]=0.0;

  matrix[ 0]=m[0]*rotate[0]+m[4]*rotate[1]+m[ 8]*rotate[ 2];

  matrix[ 4]=m[0]*rotate[4]+m[4]*rotate[5]+m[ 8]*rotate[ 6];

  matrix[ 8]=m[0]*rotate[8]+m[4]*rotate[9]+m[ 8]*rotate[10];

  matrix[ 1]=m[1]*rotate[0]+m[5]*rotate[1]+m[ 9]*rotate[ 2];

  matrix[ 5]=m[1]*rotate[4]+m[5]*rotate[5]+m[ 9]*rotate[ 6];

  matrix[ 9]=m[1]*rotate[8]+m[5]*rotate[9]+m[ 9]*rotate[10];

  matrix[ 2]=m[2]*rotate[0]+m[6]*rotate[1]+m[10]*rotate[ 2];

  matrix[ 6]=m[2]*rotate[4]+m[6]*rotate[5]+m[10]*rotate[ 6];

  matrix[10]=m[2]*rotate[8]+m[6]*rotate[9]+m[10]*rotate[10];

  matrix[ 3]=m[3]*rotate[0]+m[7]*rotate[1]+m[11]*rotate[ 2];

  matrix[ 7]=m[3]*rotate[4]+m[7]*rotate[5]+m[11]*rotate[ 6];

  matrix[11]=m[3]*rotate[8]+m[7]*rotate[9]+m[11]*rotate[10];
}

void matrixScale(float *matrix, float x, float y, float z)
{
  matrix[0]*=x;
  matrix[4]*=y;
  matrix[8]*=z;
	
  matrix[1]*=x;
  matrix[5]*=y;
  matrix[9]*=z;

  matrix[2]*=x;
  matrix[6]*=y;
  matrix[10]*=z;

  matrix[3]*=x;
  matrix[7]*=y;
  matrix[11]*=z;
}
