// math3d.cpp
// Math3D Library, version 0.95

/* Copyright (c) 2007-2009, Richard S. Wright Jr.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list 
of conditions and the following disclaimer.

Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other 
materials provided with the distribution.

Neither the name of Richard S. Wright Jr. nor the names of other contributors may be used 
to endorse or promote products derived from this software without specific prior 
written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED 
TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Implementation file for the Math3d library. The C-Runtime has math.h, these routines 
// are meant to suppliment math.h by adding geometry/math routines
// useful for graphics, simulation, and physics applications (3D stuff).
// This library is meant to be useful on Win32, Mac OS X, various Linux/Unix distros,
// and mobile platforms. Although designed with OpenGL in mind, there are no OpenGL 
// dependencies. Other than standard math routines, the only other outside routine
// used is memcpy (for faster copying of vector arrays).
// Most of the library is inlined. Some functions however are here as I judged them
// too big to be inlined all over the place... nothing prevents anyone from changing
// this if it better fits their project requirements.
// Richard S. Wright Jr.

// Most functions are in-lined... and are defined here
#include <math3d.h>


////////////////////////////////////////////////////////////
// LoadIdentity
// For 3x3 and 4x4 float and double matricies.
// 3x3 float
void m3dLoadIdentity33(M3DMatrix33f m)
	{
	// Don't be fooled, this is still column major
	static M3DMatrix33f	identity = { 1.0f, 0.0f, 0.0f ,
									 0.0f, 1.0f, 0.0f,
									 0.0f, 0.0f, 1.0f };

	memcpy(m, identity, sizeof(M3DMatrix33f));
	}

// 3x3 double
void m3dLoadIdentity33(M3DMatrix33d m)
	{
	// Don't be fooled, this is still column major
	static M3DMatrix33d	identity = { 1.0, 0.0, 0.0 ,
									 0.0, 1.0, 0.0,
									 0.0, 0.0, 1.0 };

	memcpy(m, identity, sizeof(M3DMatrix33d));
	}

// 4x4 float
void m3dLoadIdentity44(M3DMatrix44f m)
	{
	// Don't be fooled, this is still column major
	static M3DMatrix44f	identity = { 1.0f, 0.0f, 0.0f, 0.0f,
									 0.0f, 1.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 1.0f, 0.0f,
									 0.0f, 0.0f, 0.0f, 1.0f };

	memcpy(m, identity, sizeof(M3DMatrix44f));
	}

// 4x4 double
void m3dLoadIdentity44(M3DMatrix44d m)
	{
	static M3DMatrix44d	identity = { 1.0, 0.0, 0.0, 0.0,
									 0.0, 1.0, 0.0, 0.0,
									 0.0, 0.0, 1.0, 0.0,
									 0.0, 0.0, 0.0, 1.0 };

	memcpy(m, identity, sizeof(M3DMatrix44d));
	}


////////////////////////////////////////////////////////////////////////
// Return the square of the distance between two points
// Should these be inlined...?
float m3dGetDistanceSquared3(const M3DVector3f u, const M3DVector3f v)
	{
	float x = u[0] - v[0];
	x = x*x;
	
	float y = u[1] - v[1];
	y = y*y;

	float z = u[2] - v[2];
	z = z*z;

	return (x + y + z);
    }

// Ditto above, but for doubles
double m3dGetDistanceSquared3(const M3DVector3d u, const M3DVector3d v)
	{
	double x = u[0] - v[0];
	x = x*x;
	
	double y = u[1] - v[1];
	y = y*y;

	double z = u[2] - v[2];
	z = z*z;

	return (x + y + z);
	}

#define A(row,col)  a[(col<<2)+row]
#define B(row,col)  b[(col<<2)+row]
#define P(row,col)  product[(col<<2)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 4x4 matricies
void m3dMatrixMultiply44(M3DMatrix44f product, const M3DMatrix44f a, const M3DMatrix44f b )
{
	for (int i = 0; i < 4; i++) {
		float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	}
}

// Ditto above, but for doubles
void m3dMatrixMultiply(M3DMatrix44d product, const M3DMatrix44d a, const M3DMatrix44d b )
{
	for (int i = 0; i < 4; i++) {
		double ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
		P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
		P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
		P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
		P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
	}
}
#undef A
#undef B
#undef P


#define A33(row,col)  a[(col*3)+row]
#define B33(row,col)  b[(col*3)+row]
#define P33(row,col)  product[(col*3)+row]

///////////////////////////////////////////////////////////////////////////////
// Multiply two 3x3 matricies
void m3dMatrixMultiply33(M3DMatrix33f product, const M3DMatrix33f a, const M3DMatrix33f b )
{
	for (int i = 0; i < 3; i++) {
		float ai0=A33(i,0), ai1=A33(i,1),  ai2=A33(i,2);
		P33(i,0) = ai0 * B33(0,0) + ai1 * B33(1,0) + ai2 * B33(2,0);
		P33(i,1) = ai0 * B33(0,1) + ai1 * B33(1,1) + ai2 * B33(2,1);
		P33(i,2) = ai0 * B33(0,2) + ai1 * B33(1,2) + ai2 * B33(2,2);
	}
}

// Ditto above, but for doubles
void m3dMatrixMultiply44(M3DMatrix33d product, const M3DMatrix33d a, const M3DMatrix33d b )
{
	for (int i = 0; i < 3; i++) {
		double ai0=A33(i,0),  ai1=A33(i,1),  ai2=A33(i,2);
		P33(i,0) = ai0 * B33(0,0) + ai1 * B33(1,0) + ai2 * B33(2,0);
		P33(i,1) = ai0 * B33(0,1) + ai1 * B33(1,1) + ai2 * B33(2,1);
		P33(i,2) = ai0 * B33(0,2) + ai1 * B33(1,2) + ai2 * B33(2,2);
	}
}

#undef A33
#undef B33
#undef P33

	

////////////////////////////////////////////////////////////////////////////////////////////
// Create a projection matrix
// Similiar to the old gluPerspective... fov is in radians btw...
void m3dMakePerspectiveMatrix(M3DMatrix44f mProjection, float fFov, float fAspect, float zMin, float zMax)
	{
	m3dLoadIdentity44(mProjection); // Fastest way to get most valid values already in place

    float yMax = zMin * tanf(fFov * 0.5f);
    float yMin = -yMax;
	float xMin = yMin * fAspect;
    float xMax = -xMin; 
    
	mProjection[0] = (2.0f * zMin) / (xMax - xMin);
	mProjection[5] = (2.0f * zMin) / (yMax - yMin);
	mProjection[8] = (xMax + xMin) / (xMax - xMin);
	mProjection[9] = (yMax + yMin) / (yMax - yMin);
	mProjection[10] = -((zMax + zMin) / (zMax - zMin));
	mProjection[11] = -1.0f;
	mProjection[14] = -((2.0f * (zMax*zMin))/(zMax - zMin));
	mProjection[15] = 0.0f;
	}

///////////////////////////////////////////////////////////////////////////////
// Make a orthographic projection matrix
void m3dMakeOrthographicMatrix(M3DMatrix44f mProjection, float xMin, float xMax, float yMin, float yMax, float zMin, float zMax)
	{
	m3dLoadIdentity44(mProjection);
	
	mProjection[0] = 2.0f / (xMax - xMin);
	mProjection[5] = 2.0f / (yMax - yMin);
	mProjection[10] = -2.0f / (zMax - zMin);
	mProjection[12] = -((xMax + xMin)/(xMax - xMin));
	mProjection[13] = -((yMax + yMin)/(yMax - yMin));
	mProjection[14] = -((zMax + zMin)/(zMax - zMin));
	mProjection[15] = 1.0f;
	}
	


#define M33(row,col)  m[col*3+row]
///////////////////////////////////////////////////////////////////////////////
// Creates a 3x3 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix33(M3DMatrix33f m, float angle, float x, float y, float z)
	{
	
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	mag = float(sqrt( x*x + y*y + z*z ));

	// Identity matrix
	if (mag == 0.0f) {
		m3dLoadIdentity33(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M33(0,0) = (one_c * xx) + c;
	M33(0,1) = (one_c * xy) - zs;
	M33(0,2) = (one_c * zx) + ys;

	M33(1,0) = (one_c * xy) + zs;
	M33(1,1) = (one_c * yy) + c;
	M33(1,2) = (one_c * yz) - xs;

	M33(2,0) = (one_c * zx) - ys;
	M33(2,1) = (one_c * yz) + xs;
	M33(2,2) = (one_c * zz) + c;
	}

#undef M33

///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44f m, float angle, float x, float y, float z)
	{
	float mag, s, c;
	float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = float(sin(angle));
	c = float(cos(angle));

	mag = float(sqrt( x*x + y*y + z*z ));

	// Identity matrix
	if (mag == 0.0f) {
		m3dLoadIdentity44(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

    #define M(row,col)  m[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;
	M(0,3) = 0.0f;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;
	M(1,3) = 0.0f;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;
	M(2,3) = 0.0f;

	M(3,0) = 0.0f;
	M(3,1) = 0.0f;
	M(3,2) = 0.0f;
	M(3,3) = 1.0f;

    #undef M
	}



///////////////////////////////////////////////////////////////////////////////
// Ditto above, but for doubles
void m3dRotationMatrix33(M3DMatrix33d m, double angle, double x, double y, double z)
	{
	double mag, s, c;
	double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	mag = sqrt( x*x + y*y + z*z );

	// Identity matrix
	if (mag == 0.0) {
		m3dLoadIdentity33(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

    #define M(row,col)  m[col*3+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0 - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;

    #undef M
	}


///////////////////////////////////////////////////////////////////////////////
// Creates a 4x4 rotation matrix, takes radians NOT degrees
void m3dRotationMatrix44(M3DMatrix44d m, double angle, double x, double y, double z)
	{
	double mag, s, c;
	double xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = sin(angle);
	c = cos(angle);

	mag = sqrt( x*x + y*y + z*z );

	// Identity matrix
	if (mag == 0.0) {
		m3dLoadIdentity44(m);
		return;
	}

	// Rotation matrix is normalized
	x /= mag;
	y /= mag;
	z /= mag;

    #define M(row,col)  m[col*4+row]

	xx = x * x;
	yy = y * y;
	zz = z * z;
	xy = x * y;
	yz = y * z;
	zx = z * x;
	xs = x * s;
	ys = y * s;
	zs = z * s;
	one_c = 1.0f - c;

	M(0,0) = (one_c * xx) + c;
	M(0,1) = (one_c * xy) - zs;
	M(0,2) = (one_c * zx) + ys;
	M(0,3) = 0.0;

	M(1,0) = (one_c * xy) + zs;
	M(1,1) = (one_c * yy) + c;
	M(1,2) = (one_c * yz) - xs;
	M(1,3) = 0.0;

	M(2,0) = (one_c * zx) - ys;
	M(2,1) = (one_c * yz) + xs;
	M(2,2) = (one_c * zz) + c;
	M(2,3) = 0.0;

	M(3,0) = 0.0;
	M(3,1) = 0.0;
	M(3,2) = 0.0;
	M(3,3) = 1.0;

    #undef M
  }

////////////////////////////////////////////////////////////////////////////
/// This function is not exported by library, just for this modules use only
// 3x3 determinant
static float DetIJ(const M3DMatrix44f m, const int i, const int j)
    {
    int x, y, ii, jj;
    float ret, mat[3][3];

    x = 0;
    for (ii = 0; ii < 4; ii++)
        {
        if (ii == i) continue;
        y = 0;
        for (jj = 0; jj < 4; jj++)
            {
            if (jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            y++;
            }
        x++;
        }

    ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);

    return ret;
    }


////////////////////////////////////////////////////////////////////////////
/// This function is not exported by library, just for this modules use only
// 3x3 determinant
static double DetIJ(const M3DMatrix44d m, const int i, const int j)
    {
    int x, y, ii, jj;
    double ret, mat[3][3];

    x = 0;
    for (ii = 0; ii < 4; ii++)
        {
        if (ii == i) continue;
        y = 0;
        for (jj = 0; jj < 4; jj++)
            {
            if (jj == j) continue;
            mat[x][y] = m[(ii*4)+jj];
            y++;
            }
        x++;
        }

    ret =  mat[0][0]*(mat[1][1]*mat[2][2]-mat[2][1]*mat[1][2]);
    ret -= mat[0][1]*(mat[1][0]*mat[2][2]-mat[2][0]*mat[1][2]);
    ret += mat[0][2]*(mat[1][0]*mat[2][1]-mat[2][0]*mat[1][1]);

    return ret;
    }

////////////////////////////////////////////////////////////////////////////
///
// Invert matrix
void m3dInvertMatrix44(M3DMatrix44f mInverse, const M3DMatrix44f m)
    {
    int i, j;
    float det, detij;

    // calculate 4x4 determinant
    det = 0.0f;
    for (i = 0; i < 4; i++)
        {
        det += (i & 0x1) ? (-m[i] * DetIJ(m, 0, i)) : (m[i] * DetIJ(m, 0,i));
        }
    det = 1.0f / det;

    // calculate inverse
    for (i = 0; i < 4; i++)
        {
        for (j = 0; j < 4; j++)
            {
            detij = DetIJ(m, j, i);
            mInverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det); 
            }
        }
    }

////////////////////////////////////////////////////////////////////////////
///
// Invert matrix
void m3dInvertMatrix44(M3DMatrix44d mInverse, const M3DMatrix44d m)
    {
    int i, j;
    double det, detij;

    // calculate 4x4 determinant
    det = 0.0;
    for (i = 0; i < 4; i++)
        {
        det += (i & 0x1) ? (-m[i] * DetIJ(m, 0, i)) : (m[i] * DetIJ(m, 0,i));
        }
    det = 1.0 / det;

    // calculate inverse
    for (i = 0; i < 4; i++)
        {
        for (j = 0; j < 4; j++)
            {
            detij = DetIJ(m, j, i);
            mInverse[(i*4)+j] = ((i+j) & 0x1) ? (-detij * det) : (detij *det); 
            }
        }
    }


///////////////////////////////////////////////////////////////////////////////////////
// Get Window coordinates, discard Z...
void m3dProjectXY(M3DVector2f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn)
	{
    M3DVector4f vBack, vForth;

	memcpy(vBack, vPointIn, sizeof(float)*3);
	vBack[3] = 1.0f;
    
    m3dTransformVector4(vForth, vBack, mModelView);
    m3dTransformVector4(vBack, vForth, mProjection);
    
    if(!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
        float div = 1.0f / vBack[3];
        vBack[0] *= div;
        vBack[1] *= div;
        //vBack[2] *= div; 
        }

    vPointOut[0] = float(iViewPort[0])+(1.0f+float(vBack[0]))*float(iViewPort[2])/2.0f;
    vPointOut[1] = float(iViewPort[1])+(1.0f+float(vBack[1]))*float(iViewPort[3])/2.0f;

	// This was put in for Grand Tour... I think it's right. 
	// .... please report any bugs
	if(iViewPort[0] != 0)     // Cast to float is expensive... avoid if posssible
		vPointOut[0] -= float(iViewPort[0]);
	
	if(iViewPort[1] != 0) 
		vPointOut[1] -= float(iViewPort[1]);
	}
    
///////////////////////////////////////////////////////////////////////////////////////
// Get window coordinates, we also want Z....
void m3dProjectXYZ(M3DVector3f vPointOut, const M3DMatrix44f mModelView, const M3DMatrix44f mProjection, const int iViewPort[4], const M3DVector3f vPointIn)
	{
    M3DVector4f vBack, vForth;

	memcpy(vBack, vPointIn, sizeof(float)*3);
	vBack[3] = 1.0f;
    
    m3dTransformVector4(vForth, vBack, mModelView);
    m3dTransformVector4(vBack, vForth, mProjection);
    
    if(!m3dCloseEnough(vBack[3], 0.0f, 0.000001f)) {
        float div = 1.0f / vBack[3];
        vBack[0] *= div;
        vBack[1] *= div;
        vBack[2] *= div; 
        }

    vPointOut[0] = float(iViewPort[0])+(1.0f+float(vBack[0]))*float(iViewPort[2])/2.0f;
    vPointOut[1] = float(iViewPort[1])+(1.0f+float(vBack[1]))*float(iViewPort[3])/2.0f;

	if(iViewPort[0] != 0)     // Cast to float is expensive... avoid if posssible
		vPointOut[0] -= float(iViewPort[0]);
	
	if(iViewPort[1] != 0) 
		vPointOut[1] -= float(iViewPort[1]);

 	vPointOut[2] = vBack[2];
	}



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Misc. Utilities
///////////////////////////////////////////////////////////////////////////////
// Calculates the normal of a triangle specified by the three points
// p1, p2, and p3. Each pointer points to an array of three floats. The
// triangle is assumed to be wound counter clockwise. 
void m3dFindNormal(M3DVector3f result, const M3DVector3f point1, const M3DVector3f point2, 
							const M3DVector3f point3)
	{
	M3DVector3f v1,v2;		// Temporary vectors

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
	v1[0] = point1[0] - point2[0];
	v1[1] = point1[1] - point2[1];
	v1[2] = point1[2] - point2[2];

	v2[0] = point2[0] - point3[0];
	v2[1] = point2[1] - point3[1];
	v2[2] = point2[2] - point3[2];

	// Take the cross product of the two vectors to get
	// the normal vector.
	m3dCrossProduct3(result, v1, v2);
	}



// Ditto above, but for doubles
void m3dFindNormal(M3DVector3d result, const M3DVector3d point1, const M3DVector3d point2, 
							const M3DVector3d point3)
	{
	M3DVector3d v1,v2;		// Temporary vectors

	// Calculate two vectors from the three points. Assumes counter clockwise
	// winding!
	v1[0] = point1[0] - point2[0];
	v1[1] = point1[1] - point2[1];
	v1[2] = point1[2] - point2[2];

	v2[0] = point2[0] - point3[0];
	v2[1] = point2[1] - point3[1];
	v2[2] = point2[2] - point3[2];

	// Take the cross product of the two vectors to get
	// the normal vector.
	m3dCrossProduct3(result, v1, v2);
	}



/////////////////////////////////////////////////////////////////////////////////////////
// Calculate the plane equation of the plane that the three specified points lay in. The
// points are given in clockwise winding order, with normal pointing out of clockwise face
// planeEq contains the A,B,C, and D of the plane equation coefficients
void m3dGetPlaneEquation(M3DVector4f planeEq, const M3DVector3f p1, const M3DVector3f p2, const M3DVector3f p3)
{
    // Get two vectors... do the cross product
    M3DVector3f v1, v2;

    // V1 = p3 - p1
    v1[0] = p3[0] - p1[0];
    v1[1] = p3[1] - p1[1];
    v1[2] = p3[2] - p1[2];

    // V2 = P2 - p1
    v2[0] = p2[0] - p1[0];
    v2[1] = p2[1] - p1[1];
    v2[2] = p2[2] - p1[2];

    // Unit normal to plane - Not sure which is the best way here
    m3dCrossProduct3(planeEq, v1, v2);
    m3dNormalizeVector3(planeEq);

    // Back substitute to get D
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


// Ditto above, but for doubles
void m3dGetPlaneEquation(M3DVector4d planeEq, const M3DVector3d p1, const M3DVector3d p2, const M3DVector3d p3)
{
    // Get two vectors... do the cross product
    M3DVector3d v1, v2;

    // V1 = p3 - p1
    v1[0] = p3[0] - p1[0];
    v1[1] = p3[1] - p1[1];
    v1[2] = p3[2] - p1[2];

    // V2 = P2 - p1
    v2[0] = p2[0] - p1[0];
    v2[1] = p2[1] - p1[1];
    v2[2] = p2[2] - p1[2];

    // Unit normal to plane - Not sure which is the best way here
    m3dCrossProduct3(planeEq, v1, v2);
    m3dNormalizeVector3(planeEq);
    // Back substitute to get D
    planeEq[3] = -(planeEq[0] * p3[0] + planeEq[1] * p3[1] + planeEq[2] * p3[2]);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom(M3DVector3f vOut, const M3DVector3f vP0, const M3DVector3f vP1, const M3DVector3f vP2, const M3DVector3f vP3, float t)
    {
    float t2 = t * t;
    float t3 = t2 * t;

    // X    
    vOut[0] = 0.5f * ( ( 2.0f * vP1[0]) +
                       (-vP0[0] + vP2[0]) * t +
                       (2.0f * vP0[0] - 5.0f *vP1[0] + 4.0f * vP2[0] - vP3[0]) * t2 +
                       (-vP0[0] + 3.0f*vP1[0] - 3.0f *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5f * ( ( 2.0f * vP1[1]) +
                       (-vP0[1] + vP2[1]) * t +
                       (2.0f * vP0[1] - 5.0f *vP1[1] + 4.0f * vP2[1] - vP3[1]) * t2 +
                       (-vP0[1] + 3.0f*vP1[1] - 3.0f *vP2[1] + vP3[1]) * t3);

    // Z
    vOut[2] = 0.5f * ( ( 2.0f * vP1[2]) +
                       (-vP0[2] + vP2[2]) * t +
                       (2.0f * vP0[2] - 5.0f *vP1[2] + 4.0f * vP2[2] - vP3[2]) * t2 +
                       (-vP0[2] + 3.0f*vP1[2] - 3.0f *vP2[2] + vP3[2]) * t3);
    }


//////////////////////////////////////////////////////////////////////////////////////////////////
// This function does a three dimensional Catmull-Rom curve interpolation. Pass four points, and a
// floating point number between 0.0 and 1.0. The curve is interpolated between the middle two points.
// Coded by RSW
void m3dCatmullRom(M3DVector3d vOut, const M3DVector3d vP0, const M3DVector3d vP1, const M3DVector3d vP2, const M3DVector3d vP3, double t)
    {
    double t2 = t * t;
    double t3 = t2 * t;

    // X    
    vOut[0] = 0.5 * ( ( 2.0 * vP1[0]) +
                       (-vP0[0] + vP2[0]) * t +
                       (2.0 * vP0[0] - 5.0 *vP1[0] + 4.0 * vP2[0] - vP3[0]) * t2 +
                       (-vP0[0] + 3.0*vP1[0] - 3.0 *vP2[0] + vP3[0]) * t3);
    // Y
    vOut[1] = 0.5 * ( ( 2.0 * vP1[1]) +
                       (-vP0[1] + vP2[1]) * t +
                       (2.0 * vP0[1] - 5.0 *vP1[1] + 4.0 * vP2[1] - vP3[1]) * t2 +
                       (-vP0[1] + 3*vP1[1] - 3.0 *vP2[1] + vP3[1]) * t3);

    // Z
    vOut[2] = 0.5 * ( ( 2.0 * vP1[2]) +
                       (-vP0[2] + vP2[2]) * t +
                       (2.0 * vP0[2] - 5.0 *vP1[2] + 4.0 * vP2[2] - vP3[2]) * t2 +
                       (-vP0[2] + 3.0*vP1[2] - 3.0 *vP2[2] + vP3[2]) * t3);
    }


///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// sphereCenter with radius sphereRadius
// Return value is < 0 if the ray does not intersect
// Return value is 0.0 if ray is tangent
// Positive value is distance to the intersection point
// Algorithm from "3D Math Primer for Graphics and Game Development"
double m3dRaySphereTest(const M3DVector3d point, const M3DVector3d ray, const M3DVector3d sphereCenter, double sphereRadius)
	{
	//m3dNormalizeVector(ray);	// Make sure ray is unit length

	M3DVector3d rayToCenter;	// Ray to center of sphere
	rayToCenter[0] =  sphereCenter[0] - point[0];	
	rayToCenter[1] =  sphereCenter[1] - point[1];
	rayToCenter[2] =  sphereCenter[2] - point[2];
	
	// Project rayToCenter on ray to test
	double a = m3dDotProduct3(rayToCenter, ray);
	
	// Distance to center of sphere
	double distance2 = m3dDotProduct3(rayToCenter, rayToCenter);	// Or length

	
	double dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);
	
	if(dRet > 0.0)			// Return distance to intersection
		dRet = a - sqrt(dRet);
	
	return dRet;
	}

///////////////////////////////////////////////////////////////////////////////
// Determine if the ray (starting at point) intersects the sphere centered at
// ditto above, but uses floating point math
float m3dRaySphereTest(const M3DVector3f point, const M3DVector3f ray, const M3DVector3f sphereCenter, float sphereRadius)
	{
	//m3dNormalizeVectorf(ray);	// Make sure ray is unit length

	M3DVector3f rayToCenter;	// Ray to center of sphere
	rayToCenter[0] =  sphereCenter[0] - point[0];	
	rayToCenter[1] =  sphereCenter[1] - point[1];
	rayToCenter[2] =  sphereCenter[2] - point[2];
	
	// Project rayToCenter on ray to test
	float a = m3dDotProduct3(rayToCenter, ray);
	
	// Distance to center of sphere
	float distance2 = m3dDotProduct3(rayToCenter, rayToCenter);	// Or length
	
	float dRet = (sphereRadius * sphereRadius) - distance2 + (a*a);
	
	if(dRet > 0.0)			// Return distance to intersection
		dRet = a - sqrtf(dRet);
	
	return dRet;
	}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Calculate the tangent basis for a triangle on the surface of a model
// This vector is needed for most normal mapping shaders 
void m3dCalculateTangentBasis(M3DVector3f vTangent, const M3DVector3f vTriangle[3], const M3DVector2f vTexCoords[3], const M3DVector3f N)
{
    M3DVector3f dv2v1, dv3v1;
    float dc2c1t, dc2c1b, dc3c1t, dc3c1b;
    float M;
    
    m3dSubtractVectors3(dv2v1, vTriangle[1], vTriangle[0]);
    m3dSubtractVectors3(dv3v1, vTriangle[2], vTriangle[0]);
    
    dc2c1t = vTexCoords[1][0] - vTexCoords[0][0];
    dc2c1b = vTexCoords[1][1] - vTexCoords[0][1];
    dc3c1t = vTexCoords[2][0] - vTexCoords[0][0];
    dc3c1b = vTexCoords[2][1] - vTexCoords[0][1];
    
    M = (dc2c1t * dc3c1b) - (dc3c1t * dc2c1b);
    M = 1.0f / M;
    
    m3dScaleVector3(dv2v1, dc3c1b);
    m3dScaleVector3(dv3v1, dc2c1b);
    
    m3dSubtractVectors3(vTangent, dv2v1, dv3v1);
    m3dScaleVector3(vTangent, M);  // This potentially changes the direction of the vector
    m3dNormalizeVector3(vTangent);

    M3DVector3f B;
    m3dCrossProduct3(B, N, vTangent);
    m3dCrossProduct3(vTangent, B, N);
    m3dNormalizeVector3(vTangent);
    }
	
	
////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
double m3dSmoothStep(const double edge1, const double edge2, const double x)
    {
    double t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1.0)
        t = 1.0;
        
    if(t < 0.0)
        t = 0.0f;
        
    return t * t * ( 3.0 - 2.0 * t);
    }

////////////////////////////////////////////////////////////////////////////
// Smoothly step between 0 and 1 between edge1 and edge 2
float m3dSmoothStep(const float edge1, const float edge2, const float x)
    {
    float t;
    t = (x - edge1) / (edge2 - edge1);
    if(t > 1.0f)
        t = 1.0f;
        
    if(t < 0.0)
        t = 0.0f;
        
    return t * t * ( 3.0f - 2.0f * t);
    }
	
	

///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationf(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44f proj, const M3DVector4f planeEq, const M3DVector3f vLightPos)
	{
	// These just make the code below easier to read. They will be 
	// removed by the optimizer.	
	float a = planeEq[0];
	float b = planeEq[1];
	float c = planeEq[2];
	float d = planeEq[3];

	float dx = -vLightPos[0];
	float dy = -vLightPos[1];
	float dz = -vLightPos[2];

	// Now build the projection matrix
	proj[0] = b * dy + c * dz;
	proj[1] = -a * dy;
	proj[2] = -a * dz;
	proj[3] = 0.0;

	proj[4] = -b * dx;
	proj[5] = a * dx + c * dz;
	proj[6] = -b * dz;
	proj[7] = 0.0;

	proj[8] = -c * dx;
	proj[9] = -c * dy;
	proj[10] = a * dx + b * dy;
	proj[11] = 0.0;

	proj[12] = -d * dx;
	proj[13] = -d * dy;
	proj[14] = -d * dz;
	proj[15] = a * dx + b * dy + c * dz;
	// Shadow matrix ready
	}
	
	
///////////////////////////////////////////////////////////////////////////
// Creae a projection to "squish" an object into the plane.
// Use m3dGetPlaneEquationd(planeEq, point1, point2, point3);
// to get a plane equation.
void m3dMakePlanarShadowMatrix(M3DMatrix44d proj, const M3DVector4d planeEq, const M3DVector3f vLightPos)
	{
	// These just make the code below easier to read. They will be 
	// removed by the optimizer.	
	double a = planeEq[0];
	double b = planeEq[1];
	double c = planeEq[2];
	double d = planeEq[3];

	double dx = -vLightPos[0];
	double dy = -vLightPos[1];
	double dz = -vLightPos[2];

	// Now build the projection matrix
	proj[0] = b * dy + c * dz;
	proj[1] = -a * dy;
	proj[2] = -a * dz;
	proj[3] = 0.0;

	proj[4] = -b * dx;
	proj[5] = a * dx + c * dz;
	proj[6] = -b * dz;
	proj[7] = 0.0;

	proj[8] = -c * dx;
	proj[9] = -c * dy;
	proj[10] = a * dx + b * dy;
	proj[11] = 0.0;

	proj[12] = -d * dx;
	proj[13] = -d * dy;
	proj[14] = -d * dz;
	proj[15] = a * dx + b * dy + c * dz;
	// Shadow matrix ready
	}


/////////////////////////////////////////////////////////////////////////////
// I want to know the point on a ray, closest to another given point in space.
// As a bonus, return the distance squared of the two points.
// In: vRayOrigin is the origin of the ray.
// In: vUnitRayDir is the unit vector of the ray
// In: vPointInSpace is the point in space
// Out: vPointOnRay is the poing on the ray closest to vPointInSpace
// Return: The square of the distance to the ray
double m3dClosestPointOnRay(M3DVector3d vPointOnRay, const M3DVector3d vRayOrigin, const M3DVector3d vUnitRayDir, 
											const M3DVector3d vPointInSpace)
	{
	M3DVector3d v;
	m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);
	
	double t = m3dDotProduct3(vUnitRayDir, v);
	
	// This is the point on the ray
	vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
	vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
	vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);
	
	return m3dGetDistanceSquared3(vPointOnRay, vPointInSpace);
	}

// ditto above... but with floats
float m3dClosestPointOnRay(M3DVector3f vPointOnRay, const M3DVector3f vRayOrigin, const M3DVector3f vUnitRayDir, 
							 const M3DVector3f vPointInSpace)
	{
	M3DVector3f v;
	m3dSubtractVectors3(v, vPointInSpace, vRayOrigin);
	
	float t = m3dDotProduct3(vUnitRayDir, v);
	
	// This is the point on the ray
	vPointOnRay[0] = vRayOrigin[0] + (t * vUnitRayDir[0]);
	vPointOnRay[1] = vRayOrigin[1] + (t * vUnitRayDir[1]);
	vPointOnRay[2] = vRayOrigin[2] + (t * vUnitRayDir[2]);
	
	return m3dGetDistanceSquared3(vPointOnRay, vPointInSpace);
	}
