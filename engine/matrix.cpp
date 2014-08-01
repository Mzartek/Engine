#include <Engine/matrix.hpp>

void NormalizeVector(float *pvector)
{
	float normalizingConstant;
  
	normalizingConstant=1.0f/sqrtf(pvector[0]*pvector[0]+pvector[1]*pvector[1]+pvector[2]*pvector[2]);
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

void matrixMultiply(float *result, const float *matrix1, const float *matrix2)
{
	float tmp[16];
  
	tmp[ 0]=matrix1[ 0]*matrix2[ 0]+matrix1[ 4]*matrix2[ 1]+matrix1[ 8]*matrix2[ 2]+matrix1[12]*matrix2[ 3];
	tmp[ 4]=matrix1[ 0]*matrix2[ 4]+matrix1[ 4]*matrix2[ 5]+matrix1[ 8]*matrix2[ 6]+matrix1[12]*matrix2[ 7];
	tmp[ 8]=matrix1[ 0]*matrix2[ 8]+matrix1[ 4]*matrix2[ 9]+matrix1[ 8]*matrix2[10]+matrix1[12]*matrix2[11];
	tmp[12]=matrix1[ 0]*matrix2[12]+matrix1[ 4]*matrix2[13]+matrix1[ 8]*matrix2[14]+matrix1[12]*matrix2[15];

	tmp[ 1]=matrix1[ 1]*matrix2[ 0]+matrix1[ 5]*matrix2[ 1]+matrix1[ 9]*matrix2[ 2]+matrix1[13]*matrix2[ 3];
	tmp[ 5]=matrix1[ 1]*matrix2[ 4]+matrix1[ 5]*matrix2[ 5]+matrix1[ 9]*matrix2[ 6]+matrix1[13]*matrix2[ 7];
	tmp[ 9]=matrix1[ 1]*matrix2[ 8]+matrix1[ 5]*matrix2[ 9]+matrix1[ 9]*matrix2[10]+matrix1[13]*matrix2[11];
	tmp[13]=matrix1[ 1]*matrix2[12]+matrix1[ 5]*matrix2[13]+matrix1[ 9]*matrix2[14]+matrix1[13]*matrix2[15];

	tmp[ 2]=matrix1[ 2]*matrix2[ 0]+matrix1[ 6]*matrix2[ 1]+matrix1[10]*matrix2[ 2]+matrix1[14]*matrix2[ 3];
	tmp[ 6]=matrix1[ 2]*matrix2[ 4]+matrix1[ 6]*matrix2[ 5]+matrix1[10]*matrix2[ 6]+matrix1[14]*matrix2[ 7];
	tmp[10]=matrix1[ 2]*matrix2[ 8]+matrix1[ 6]*matrix2[ 9]+matrix1[10]*matrix2[10]+matrix1[14]*matrix2[11];
	tmp[14]=matrix1[ 2]*matrix2[12]+matrix1[ 6]*matrix2[13]+matrix1[10]*matrix2[14]+matrix1[14]*matrix2[15];

	tmp[ 3]=matrix1[ 3]*matrix2[ 0]+matrix1[ 7]*matrix2[ 1]+matrix1[11]*matrix2[ 2]+matrix1[15]*matrix2[ 3];
	tmp[ 7]=matrix1[ 3]*matrix2[ 4]+matrix1[ 7]*matrix2[ 5]+matrix1[11]*matrix2[ 6]+matrix1[15]*matrix2[ 7];
	tmp[11]=matrix1[ 3]*matrix2[ 8]+matrix1[ 7]*matrix2[ 9]+matrix1[11]*matrix2[10]+matrix1[15]*matrix2[11];
	tmp[15]=matrix1[ 3]*matrix2[12]+matrix1[ 7]*matrix2[13]+matrix1[11]*matrix2[14]+matrix1[15]*matrix2[15];

	memcpy(result, tmp, 16 * sizeof(float));
}

void matrixLoadIdentity(float *matrix)
{
	matrix[ 0]=1; matrix[ 4]=0; matrix[ 8]=0; matrix[12]=0; 
	matrix[ 1]=0; matrix[ 5]=1; matrix[ 9]=0; matrix[13]=0; 
	matrix[ 2]=0; matrix[ 6]=0; matrix[10]=1; matrix[14]=0; 
	matrix[ 3]=0; matrix[ 7]=0; matrix[11]=0; matrix[15]=1; 
}

void matrixLoadBias(float *matrix)
{
	matrix[ 0]=0.5; matrix[ 4]=0.0; matrix[ 8]=0.0; matrix[12]=0.5;
	matrix[ 1]=0.0; matrix[ 5]=0.5; matrix[ 9]=0.0; matrix[13]=0.5; 
	matrix[ 2]=0.0; matrix[ 6]=0.0; matrix[10]=0.5; matrix[14]=0.5; 
	matrix[ 3]=0.0; matrix[ 7]=0.0; matrix[11]=0.0; matrix[15]=1.0; 
}

void matrixNormalFromModel(float *result, const float *matrix)
{
	float tmp[16];
	float idet = 1/((matrix[ 0]*((matrix[ 5]*matrix[10])-(matrix[ 9]*matrix[ 6]))) -
			(matrix[ 4]*((matrix[ 1]*matrix[10])-(matrix[ 9]*matrix[ 2]))) +
			(matrix[ 8]*((matrix[ 1]*matrix[ 6])-(matrix[ 5]*matrix[ 2]))));

	tmp[0] = idet *  ((matrix[5] * matrix[10]) - (matrix[9] * matrix[6]));
	tmp[1] = idet * -((matrix[4] * matrix[10]) - (matrix[8] * matrix[6]));
	tmp[2] = idet *  ((matrix[4] * matrix[9]) - (matrix[8] * matrix[5]));
	tmp[3] = idet * -((matrix[1] * matrix[10]) - (matrix[9] * matrix[2]));
	tmp[4] = idet *  ((matrix[0] * matrix[10]) - (matrix[8] * matrix[2]));
	tmp[5] = idet * -((matrix[0] * matrix[9]) - (matrix[8] * matrix[1]));
	tmp[6] = idet *  ((matrix[1] * matrix[6]) - (matrix[5] * matrix[2]));
	tmp[7] = idet * -((matrix[0] * matrix[6]) - (matrix[4] * matrix[2]));
	tmp[8] = idet *  ((matrix[0] * matrix[5]) - (matrix[4] * matrix[1]));

	memcpy(result, tmp, 16 * sizeof(float));
}

void matrixInverse(float *result, const float *matrix)
{
	float inv[16], det;
	int i;

	inv[0] = matrix[5] * matrix[10] * matrix[15] -
		matrix[5] * matrix[11] * matrix[14] -
		matrix[9] * matrix[6] * matrix[15] +
		matrix[9] * matrix[7] * matrix[14] +
		matrix[13] * matrix[6] * matrix[11] -
		matrix[13] * matrix[7] * matrix[10];

	inv[4] = -matrix[4] * matrix[10] * matrix[15] +
		matrix[4] * matrix[11] * matrix[14] +
		matrix[8] * matrix[6] * matrix[15] -
		matrix[8] * matrix[7] * matrix[14] -
		matrix[12] * matrix[6] * matrix[11] +
		matrix[12] * matrix[7] * matrix[10];

	inv[8] = matrix[4] * matrix[9] * matrix[15] -
		matrix[4] * matrix[11] * matrix[13] -
		matrix[8] * matrix[5] * matrix[15] +
		matrix[8] * matrix[7] * matrix[13] +
		matrix[12] * matrix[5] * matrix[11] -
		matrix[12] * matrix[7] * matrix[9];

	inv[12] = -matrix[4] * matrix[9] * matrix[14] +
		matrix[4] * matrix[10] * matrix[13] +
		matrix[8] * matrix[5] * matrix[14] -
		matrix[8] * matrix[6] * matrix[13] -
		matrix[12] * matrix[5] * matrix[10] +
		matrix[12] * matrix[6] * matrix[9];

	inv[1] = -matrix[1] * matrix[10] * matrix[15] +
		matrix[1] * matrix[11] * matrix[14] +
		matrix[9] * matrix[2] * matrix[15] -
		matrix[9] * matrix[3] * matrix[14] -
		matrix[13] * matrix[2] * matrix[11] +
		matrix[13] * matrix[3] * matrix[10];

	inv[5] = matrix[0] * matrix[10] * matrix[15] -
		matrix[0] * matrix[11] * matrix[14] -
		matrix[8] * matrix[2] * matrix[15] +
		matrix[8] * matrix[3] * matrix[14] +
		matrix[12] * matrix[2] * matrix[11] -
		matrix[12] * matrix[3] * matrix[10];

	inv[9] = -matrix[0] * matrix[9] * matrix[15] +
		matrix[0] * matrix[11] * matrix[13] +
		matrix[8] * matrix[1] * matrix[15] -
		matrix[8] * matrix[3] * matrix[13] -
		matrix[12] * matrix[1] * matrix[11] +
		matrix[12] * matrix[3] * matrix[9];

	inv[13] = matrix[0] * matrix[9] * matrix[14] -
		matrix[0] * matrix[10] * matrix[13] -
		matrix[8] * matrix[1] * matrix[14] +
		matrix[8] * matrix[2] * matrix[13] +
		matrix[12] * matrix[1] * matrix[10] -
		matrix[12] * matrix[2] * matrix[9];

	inv[2] = matrix[1] * matrix[6] * matrix[15] -
		matrix[1] * matrix[7] * matrix[14] -
		matrix[5] * matrix[2] * matrix[15] +
		matrix[5] * matrix[3] * matrix[14] +
		matrix[13] * matrix[2] * matrix[7] -
		matrix[13] * matrix[3] * matrix[6];

	inv[6] = -matrix[0] * matrix[6] * matrix[15] +
		matrix[0] * matrix[7] * matrix[14] +
		matrix[4] * matrix[2] * matrix[15] -
		matrix[4] * matrix[3] * matrix[14] -
		matrix[12] * matrix[2] * matrix[7] +
		matrix[12] * matrix[3] * matrix[6];

	inv[10] = matrix[0] * matrix[5] * matrix[15] -
		matrix[0] * matrix[7] * matrix[13] -
		matrix[4] * matrix[1] * matrix[15] +
		matrix[4] * matrix[3] * matrix[13] +
		matrix[12] * matrix[1] * matrix[7] -
		matrix[12] * matrix[3] * matrix[5];

	inv[14] = -matrix[0] * matrix[5] * matrix[14] +
		matrix[0] * matrix[6] * matrix[13] +
		matrix[4] * matrix[1] * matrix[14] -
		matrix[4] * matrix[2] * matrix[13] -
		matrix[12] * matrix[1] * matrix[6] +
		matrix[12] * matrix[2] * matrix[5];

	inv[3] = -matrix[1] * matrix[6] * matrix[11] +
		matrix[1] * matrix[7] * matrix[10] +
		matrix[5] * matrix[2] * matrix[11] -
		matrix[5] * matrix[3] * matrix[10] -
		matrix[9] * matrix[2] * matrix[7] +
		matrix[9] * matrix[3] * matrix[6];

	inv[7] = matrix[0] * matrix[6] * matrix[11] -
		matrix[0] * matrix[7] * matrix[10] -
		matrix[4] * matrix[2] * matrix[11] +
		matrix[4] * matrix[3] * matrix[10] +
		matrix[8] * matrix[2] * matrix[7] -
		matrix[8] * matrix[3] * matrix[6];

	inv[11] = -matrix[0] * matrix[5] * matrix[11] +
		matrix[0] * matrix[7] * matrix[9] +
		matrix[4] * matrix[1] * matrix[11] -
		matrix[4] * matrix[3] * matrix[9] -
		matrix[8] * matrix[1] * matrix[7] +
		matrix[8] * matrix[3] * matrix[5];

	inv[15] = matrix[0] * matrix[5] * matrix[10] -
		matrix[0] * matrix[6] * matrix[9] -
		matrix[4] * matrix[1] * matrix[10] +
		matrix[4] * matrix[2] * matrix[9] +
		matrix[8] * matrix[1] * matrix[6] -
		matrix[8] * matrix[2] * matrix[5];

	det = matrix[0] * inv[0] + matrix[1] * inv[4] + matrix[2] * inv[8] + matrix[3] * inv[12];
	det = 1.0f / det;

	for (i = 0; i < 16; i++)
		result[i] = inv[i] * det;
}

void matrixOrtho(float *matrix, const float left, const float right, const float bottom, const float top, const float nearVal, const float farVal)
{
	float tx, ty, tz;
  
	tx = -((right+left)/(right-left));
	ty = -((top+bottom)/(top-bottom));
	tz = -((farVal+nearVal)/(farVal-nearVal));
  
	matrix[ 0]=2/(right-left);
	matrix[ 1]=0;
	matrix[ 2]=0;
	matrix[ 3]=0;

	matrix[ 4]=0;
	matrix[ 5]=2/(top-bottom);
	matrix[ 6]=0;
	matrix[ 7]=0;
  
	matrix[ 8]=0;
	matrix[ 9]=0;
	matrix[10]=-2/(farVal-nearVal);
	matrix[11]=0;

	matrix[12]=tx;
	matrix[13]=ty;
	matrix[14]=tz;
	matrix[15]=1;
}

void matrixPerspective(float *matrix, const float fovyInDegrees, const float aspectRatio, const float znear, const float zfar)
{
	float tmp, f;
  
	tmp = (float)M_PI * (fovyInDegrees/2) / 180;
	f = cosf(tmp)/sinf(tmp);
  
	matrix[ 0]=f/aspectRatio;
	matrix[ 1]=0;
	matrix[ 2]=0;
	matrix[ 3]=0;

	matrix[ 4]=0;
	matrix[ 5]=f;
	matrix[ 6]=0;
	matrix[ 7]=0;
  
	matrix[ 8]=0;
	matrix[ 9]=0;
	matrix[10]=(zfar+znear)/(znear-zfar);
	matrix[11]=-1;

	matrix[12]=0;
	matrix[13]=0;
	matrix[14]=(2*zfar*znear)/(znear-zfar);
	matrix[15]=0;
}

void matrixLookAt(float *matrix, const float *eyePosition3D, const float *center3D, const float *upVector3D)
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
   
	matrix2[ 0] = side[0];
	matrix2[ 4] = side[1];
	matrix2[ 8] = side[2];
	matrix2[12] = 0.0;
   
	matrix2[ 1] = up[0];
	matrix2[ 5] = up[1];
	matrix2[ 9] = up[2];
	matrix2[13] = 0.0;
   
	matrix2[ 2] = -forward[0];
	matrix2[ 6] = -forward[1];
	matrix2[10] = -forward[2];
	matrix2[14] = 0.0;
   
	matrix2[ 3] = matrix2[7] = matrix2[11] = 0.0;
	matrix2[15] = 1.0;
   
	matrixMultiply(resultMatrix, matrix, matrix2);
	matrixTranslate(resultMatrix, -eyePosition3D[0], -eyePosition3D[1], -eyePosition3D[2]);
   
	memcpy(matrix, resultMatrix, 16*sizeof(float));
}

void matrixTranslate(float *matrix, const float x, const float y, const float z)
{
	matrix[12]=matrix[ 0]*x+matrix[ 4]*y+matrix[ 8]*z+matrix[12];
	matrix[13]=matrix[ 1]*x+matrix[ 5]*y+matrix[ 9]*z+matrix[13];
	matrix[14]=matrix[ 2]*x+matrix[ 6]*y+matrix[10]*z+matrix[14];
	matrix[15]=matrix[ 3]*x+matrix[ 7]*y+matrix[11]*z+matrix[15];
}

void matrixRotate(float *matrix, const float angleInDegrees, const float x, const float y, const float z)
{
	float m[16], rotate[16];
	float OneMinusCosAngle, CosAngle, SinAngle;
	float A_OneMinusCosAngle, C_OneMinusCosAngle;
	float angleInRadians = angleInDegrees*((float)M_PI/180);
  
	CosAngle=cosf(angleInRadians);
	OneMinusCosAngle=1.0f-CosAngle;
	SinAngle=sinf(angleInRadians);
	A_OneMinusCosAngle=x*OneMinusCosAngle;
	C_OneMinusCosAngle=z*OneMinusCosAngle;
	
	m[ 0]=matrix[ 0];
	m[ 1]=matrix[ 1];
	m[ 2]=matrix[ 2];
	m[ 3]=matrix[ 3];
	m[ 4]=matrix[ 4];
	m[ 5]=matrix[ 5];
	m[ 6]=matrix[ 6];
	m[ 7]=matrix[ 7];
	m[ 8]=matrix[ 8];
	m[ 9]=matrix[ 9];
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

void matrixScale(float *matrix, const float x, const float y, const float z)
{
	matrix[ 0]*=x;
	matrix[ 4]*=y;
	matrix[ 8]*=z;
	
	matrix[ 1]*=x;
	matrix[ 5]*=y;
	matrix[ 9]*=z;

	matrix[ 2]*=x;
	matrix[ 6]*=y;
	matrix[10]*=z;

	matrix[ 3]*=x;
	matrix[ 7]*=y;
	matrix[11]*=z;
}
