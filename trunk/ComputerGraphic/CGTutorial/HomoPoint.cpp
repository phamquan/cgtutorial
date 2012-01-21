// HomoPoint.cpp: implementation of the CHomoPoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HomoPoint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define m_x			m_coords[0]
#define m_y			m_coords[1]
#define m_z			m_coords[2]
#define m_w			m_coords[3]


CHomoPoint::CHomoPoint(void){
	setCoords(0.0f, 0.0f, 0.0f, 1.0f);
}
CHomoPoint::CHomoPoint(const CHomoPoint& aPoint){
	setCoords(aPoint.m_coords[0],aPoint.m_coords[1],aPoint.m_coords[2],aPoint.m_coords[3]);
};
CHomoPoint::CHomoPoint(float x, float y, float z, float w){
	setCoords(x, y, z, w);
}
CHomoPoint::CHomoPoint(float* xyzw){
	setCoords(xyzw);
};
CHomoPoint::~CHomoPoint(void){
}
//-----------------------------------------------------------------------------
inline CHomoPoint&	CHomoPoint::setCoords(float x, float y, float z, float w){
	m_coords[0] = x;
	m_coords[1] = y;
	m_coords[2] = z;
	m_coords[3] = w;
	return *this;
}
inline CHomoPoint&	CHomoPoint::setCoords(float* xyzw){
	for(int i=0; i<4; i++){
		m_coords[i] = xyzw[i];
	}
	return *this;
}
inline float			CHomoPoint::getX() const {return m_coords[0];}
inline float			CHomoPoint::getY() const {return m_coords[1];}
inline float			CHomoPoint::getZ() const {return m_coords[2];}
inline float			CHomoPoint::getW() const {return m_coords[3];}
//cast operator o float* const
CHomoPoint::operator float* const	()	{return (float* const)m_coords; }

CHomoPoint& CHomoPoint::operator	=(const CHomoPoint& aPoint){
	m_coords[0] = aPoint.m_coords[0];
	m_coords[1] = aPoint.m_coords[1];
	m_coords[2] = aPoint.m_coords[2];
	m_coords[3] = aPoint.m_coords[3];
	return *this;
};

bool CHomoPoint::operator==(const CHomoPoint& right){
	bool ret =	(m_coords[0] == right.m_coords[0]) &&
				(m_coords[1] == right.m_coords[1]) &&
				(m_coords[2] == right.m_coords[2]) &&
				(m_coords[3] == right.m_coords[3]);
	return ret;
}
CString CHomoPoint::toString(){
	CString str;
	str.Format(_T("X=%4.2g, Y=%4.2g, Z=%4.2g, W=%4.2g\n"), m_coords[0], m_coords[1], m_coords[2], m_coords[3]);
	return str;
}

//================================================

CPoint3D::CPoint3D(): CHomoPoint(0.0f, 0.0f, 0.0f, 1.0f){
}
CPoint3D::CPoint3D(const CPoint3D& aPoint): CHomoPoint(aPoint){
}
CPoint3D::CPoint3D(float x, float y, float z): CHomoPoint(x, y, z, 1.0f){
}
CPoint3D::CPoint3D(float x, float y, float z, float w): CHomoPoint(x, y, z, w){
}
CPoint3D::CPoint3D(float* xyzw): CHomoPoint(xyzw){
};
CPoint3D::CPoint3D(CVector3D aVect3D){
	m_coords[0] = aVect3D.m_coords[0];
	m_coords[1] = aVect3D.m_coords[1];
	m_coords[2] = aVect3D.m_coords[2];
	m_coords[3] = 1.0f;
}
CPoint3D::~CPoint3D(void){
}
//--------------------------------------------------
//Cast operator
CPoint3D::operator CVector3D (){
	CVector3D aVect;
	aVect.setCoords(this->getX(), this->getY(), this->getZ(), 0.0f);
	return aVect;
}
bool CPoint3D::operator==(const CPoint3D& aPoint){
	return CHomoPoint::operator==(aPoint);
}
CPoint3D& CPoint3D::operator	=(const CPoint3D& aPoint){
	*((CHomoPoint*)this) = aPoint;
	return *this;
};
CPoint3D& CPoint3D::setFromMousePoint(int x, int y, int vpWidth, int vpHeight){
	if(x<0) x = 0;
	if(x>vpWidth) x = vpWidth;
	if(y<0) y = 0;
	if(y>vpHeight) y = vpHeight;

	y	= vpHeight - y;
	int centerX = vpWidth/2;
	int centerY = vpHeight/2;
	
	m_coords[0] = ((float)x - (float)centerX)/(float)centerX; m_coords[0] = (m_coords[0] >1.0f)? 1.0f : m_coords[0];
	m_coords[1] = ((float)y - (float)centerY)/(float)centerY; m_coords[1] = (m_coords[1] >1.0f)? 1.0f : m_coords[1];
	
	//float d2 = (float)(m_coords[0]*m_coords[0] + m_coords[1]*m_coords[1]);
	//d2 = (d2<1.0)?d2:1.0f;
	//m_coords[2] = sqrt(1- d2);
	//m_coords[3] = 1.0f;
	//normalize();


	float d = (float)sqrt(m_coords[0]*m_coords[0] + m_coords[1]*m_coords[1]);
	float m_pi = 3.14159f;
	m_coords[2] = (float)cos((m_pi/2)* ((d<1.0f)?d:1.0f));
	float a = 1.0f/(float)sqrt(m_coords[0]*m_coords[0] + m_coords[1]*m_coords[1]+  m_coords[2]*m_coords[2]);
	m_coords[0] = m_coords[0]*a;
	m_coords[1] = m_coords[1]*a;
	m_coords[2] = m_coords[2]*a;
	m_coords[3] = 1.0f;		
	return *this;
}
CPoint3D CPoint3D::operator +(const CVector3D& aVect3D){
	CPoint3D result;
	result.m_coords[0] = m_coords[0] + aVect3D.m_coords[0];
	result.m_coords[1] = m_coords[1] + aVect3D.m_coords[1];
	result.m_coords[2] = m_coords[2] + aVect3D.m_coords[2];
	result.m_coords[3] = 1.0f;
	return result;
}
CPoint3D CPoint3D::operator +=(const CVector3D& aVect3D){
	m_coords[0] = m_coords[0] + aVect3D.m_coords[0];
	m_coords[1] = m_coords[1] + aVect3D.m_coords[1];
	m_coords[2] = m_coords[2] + aVect3D.m_coords[2];
	m_coords[3] = 1.0f;
	return *this;
}
CVector3D CPoint3D::operator -(const CPoint3D& aPoint3D) const{
	//P2 - P1 = vector from P1 -> P2
	CVector3D result;
	result.m_coords[0] = this->m_coords[0] - aPoint3D.m_coords[0];
	result.m_coords[1] = this->m_coords[1] - aPoint3D.m_coords[1];
	result.m_coords[2] = this->m_coords[2] - aPoint3D.m_coords[2];
	result.m_coords[3] = 0.0f;
	return result;
}
CPoint3D MultMatrixPoint(float m[16], CPoint3D point) {
	CPoint3D result;
	result.setX(m[0]*point.getX() + m[4]*point.getY() + m[8]*point.getZ() + m[12]*point.getW());
	result.setY(m[1]*point.getX() + m[5]*point.getY() + m[9]*point.getZ() + m[13]*point.getW());
	result.setZ(m[2]*point.getX() + m[6]*point.getY() + m[10]*point.getZ() + m[14]*point.getW());
	result.setW(m[3]*point.getX() + m[7]*point.getY() + m[11]*point.getZ() + m[15]*point.getW());
	/*if(result.getW() != 0) {
		result.setX(result.getX()/result.getW());
		result.setY(result.getY()/result.getW());
		result.setZ(result.getZ()/result.getW());
		result.setW(1);
	}*/
	return result;
}

void MultMatrixMatrix(float in1[16], float in2[16], float out[16]) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) {
			float sum = 0;
			for(int k=0; k<4; k++) {
				sum += in1[k*4+i]*in2[j*4+k];
			}
			out[j*4+i] = sum;
		}
}
//===================================================================
CVector3D::CVector3D(): CHomoPoint(0.0f, 0.0f, 0.0f, 0.0f)
{
}
CVector3D::CVector3D(const CVector3D& aVector)
{
	m_coords[0] = aVector.m_coords[0];
	m_coords[1] = aVector.m_coords[1];
	m_coords[2] = aVector.m_coords[2];
	m_coords[3] = 0.0f;
}
CVector3D::CVector3D(float x, float y, float z): CHomoPoint(x, y, z, 0.0f)
{
}
CVector3D::CVector3D(float* xyzw): CHomoPoint(xyzw){
	m_coords[3] = 0.0f;
};
CVector3D::~CVector3D(void){
}
//----------------------------------------------
//cast operator
CVector3D::operator CPoint3D (){
	CPoint3D aPoint;
	aPoint.setCoords(this->getX(), this->getY(), this->getZ(), 1.0f);
	return aPoint;
}
CVector3D& CVector3D::operator	=(const CVector3D& aVect){
	CHomoPoint::operator=(aVect);
	return *this;
};
inline float			CVector3D::getNorm() const{ 
	return (float)sqrt(m_coords[0]* m_coords[0] + m_coords[1]* m_coords[1] + m_coords[2]* m_coords[2] );
};
CVector3D		CVector3D::getNormVector(){ 
	CVector3D result = *this;
	result.normalize();
	return result;
};
inline CVector3D&			CVector3D::normalize(){
	float norm = getNorm();
	m_coords[0] /= norm;
	m_coords[1] /= norm; 
	m_coords[2] /= norm; 
	return *this;
};
CVector3D CVector3D::operator	+(const CVector3D& aVect) {
	CVector3D result;
	result.m_coords[0] = m_coords[0] + aVect.m_coords[0]; 
	result.m_coords[1] = m_coords[1] + aVect.m_coords[1]; 
	result.m_coords[2] = m_coords[2] + aVect.m_coords[2]; 
	return result; 
};
CVector3D CVector3D::operator	+=(const CVector3D& aVect) {
	m_coords[0] = m_coords[0] + aVect.m_coords[0]; 
	m_coords[1] = m_coords[1] + aVect.m_coords[1]; 
	m_coords[2] = m_coords[2] + aVect.m_coords[2]; 
	return *this; 
};
CVector3D CVector3D::operator	-(const CVector3D& aVect) {
	CVector3D result;
	result.m_coords[0] = m_coords[0] - aVect.m_coords[0]; 
	result.m_coords[1] = m_coords[1] - aVect.m_coords[1]; 
	result.m_coords[2] = m_coords[2] - aVect.m_coords[2]; 
	return result; 
};
CVector3D& CVector3D::operator	-=(const CVector3D& aVect) {
	m_coords[0] = m_coords[0] - aVect.m_coords[0]; 
	m_coords[1] = m_coords[1] - aVect.m_coords[1]; 
	m_coords[2] = m_coords[2] - aVect.m_coords[2]; 
	return *this; 
};

CVector3D CVector3D::operator	*(float factor) {
	CVector3D result;
	result.m_coords[0] = m_coords[0] * factor; 
	result.m_coords[1] = m_coords[1] * factor; 
	result.m_coords[2] = m_coords[2] * factor; 
	return result; 
};
CVector3D operator*(float factor, CVector3D aVector){
	CVector3D result;
	result.m_coords[0] = aVector.m_coords[0] * factor; 
	result.m_coords[1] = aVector.m_coords[1] * factor; 
	result.m_coords[2] = aVector.m_coords[2] * factor; 
	return result; 
}

CVector3D CVector3D::operator	*=(float factor) {
	m_coords[0] *= factor; 
	m_coords[1] *= factor;
	m_coords[2] *= factor; 
	return *this; 
};

CVector3D CVector3D::crossProduct(const CVector3D& aVect){
	CVector3D result;
	result.m_coords[0]	=	this->m_coords[1]*aVect.m_coords[2] - this->m_coords[2] * aVect.m_coords[1];
	result.m_coords[1]	=	this->m_coords[2]*aVect.m_coords[0] - this->m_coords[0] * aVect.m_coords[2];
	result.m_coords[2]	=	this->m_coords[0]*aVect.m_coords[1] - this->m_coords[1] * aVect.m_coords[0];
	result.m_coords[3]	=	0.0; //is vector
	return result;
}
float CVector3D::dotProduct(const CVector3D& aVect){
	return (m_coords[0]*aVect.m_coords[0] + m_coords[1]*aVect.m_coords[1]  + m_coords[2]*aVect.m_coords[2] );
}

bool CVector3D::operator==(const CVector3D& aVect3D){
	bool ret =	
			(m_coords[0] == aVect3D.m_coords[0]) &&
			(m_coords[1] == aVect3D.m_coords[1]) &&
			(m_coords[2] == aVect3D.m_coords[2]);
	return ret;
}
CVector3D CVector3D::fromP1toP2(CPoint3D p1, CPoint3D p2){
	return (p2 - p1);
}
CVector3D& CVector3D::operator - (){
	m_coords[0] = - m_coords[0];
	m_coords[1] = - m_coords[1];
	m_coords[2] = - m_coords[2];
	return *this;
}

bool InvertMatrix(float src[16], float inverse[16])
{
    float t;
    int i, j, k, swap;
    float tmp[4][4];
    
    for(i = 0; i < 16; i++)
		inverse[i] = 0;
	inverse[0] = inverse[5] = inverse[10] = inverse[15] = 1;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            tmp[i][j] = src[i*4+j];
        }
    }
    
    for (i = 0; i < 4; i++) {
        /* look for largest element in column. */
        swap = i;
        for (j = i + 1; j < 4; j++) {
            if (fabs(tmp[j][i]) > fabs(tmp[i][i])) {
                swap = j;
            }
        }
        
        if (swap != i) {
            /* swap rows. */
            for (k = 0; k < 4; k++) {
                t = tmp[i][k];
                tmp[i][k] = tmp[swap][k];
                tmp[swap][k] = t;
                
                t = inverse[i*4+k];
                inverse[i*4+k] = inverse[swap*4+k];
                inverse[swap*4+k] = t;
            }
        }
        
        if (tmp[i][i] == 0) {
        /* no non-zero pivot.  the matrix is singular, which
           shouldn't happen.  This means the user gave us a bad
            matrix. */
            return false;
        }
        
        t = tmp[i][i];
        for (k = 0; k < 4; k++) {
            tmp[i][k] /= t;
            inverse[i*4+k] /= t;
        }
        for (j = 0; j < 4; j++) {
            if (j != i) {
                t = tmp[j][i];
                for (k = 0; k < 4; k++) {
                    tmp[j][k] -= tmp[i][k]*t;
                    inverse[j*4+k] -= inverse[i*4+k]*t;
                }
            }
        }
    }
    return true;
}
