#include "HomoPoint.h"

#define m_x			m_coords[0]
#define m_y			m_coords[1]
#define m_z			m_coords[2]
#define m_w			m_coords[3]

namespace QTMath {

	CHomoPoint::CHomoPoint(void){
		setCoords(0.0f, 0.0f, 0.0f, 1.0f);
	}
	CHomoPoint::CHomoPoint(const CHomoPoint& aPoint){
		setCoords(aPoint.m_coords[0], aPoint.m_coords[1], aPoint.m_coords[2], aPoint.m_coords[3]);
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
	}; 
	inline CHomoPoint&	CHomoPoint::setCoords(float* xyzw){
		for(int i=0; i<4; i++){
			m_coords[i] = xyzw[i];
		}
		return *this;
	};
	inline CHomoPoint&		CHomoPoint::setX(float x) {m_coords[0] = x; return *this;};
	inline CHomoPoint&		CHomoPoint::setY(float y) {m_coords[1] = y; return *this;};
	inline CHomoPoint&		CHomoPoint::setZ(float z) {m_coords[2] = z; return *this;};
	inline CHomoPoint&		CHomoPoint::setW(float w) {m_coords[3] = w; return *this;};
	inline float			CHomoPoint::getX() const {return m_coords[0];};
	inline float			CHomoPoint::getY() const {return m_coords[1];};
	inline float			CHomoPoint::getZ() const {return m_coords[2];};
	inline float			CHomoPoint::getW() const {return m_coords[3];};
	//cast operator o float* const
	CHomoPoint::operator float* const	()	{return (float* const)m_coords; };

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
	//CString CHomoPoint::toString(){
	//	CString str;
	//	str.Format(_T("X=%4.2g, Y=%4.2g, Z=%4.2g, W=%4.2g\n"), m_coords[0], m_coords[1], m_coords[2], m_coords[3]);
	//	return str;
	//}

	//================================================

	CPoint3D::CPoint3D(): CHomoPoint(0.0f, 0.0f, 0.0f, 1.0f){
	}
	CPoint3D::CPoint3D(const CPoint3D& aPoint): CHomoPoint(aPoint){
		setCoords(aPoint.getX(), aPoint.getY(), aPoint.getZ(), aPoint.getW());
	}
	CPoint3D::CPoint3D(float x, float y, float z): CHomoPoint(x, y, z, 1.0f){
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
		float m_pi = 3.14159;
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
		return sqrt(m_coords[0]* m_coords[0] + m_coords[1]* m_coords[1] + m_coords[2]* m_coords[2] );
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

	//==========================================================
	CQuaternion::CQuaternion(float x, float y, float z, float w): CHomoPoint(x, y, z, w)
	{
	}
	CQuaternion::CQuaternion(const CVector3D& axis, float angleDEG){
		loadFromAxisAngle(axis, angleDEG);
	}

	CQuaternion::CQuaternion(){
		loadIdentity();
	}
	CQuaternion::~CQuaternion(){
	}
	//
	void CQuaternion::loadIdentity(){
		m_coords[0] = 0.0f;
		m_coords[1] = 0.0f;
		m_coords[2] = 0.0f;
		m_coords[3] = 1.0f;
	}

	void CQuaternion::loadFromAxisAngle(float x, float y, float z, float angleDEG){
		// First we want to convert the degrees to radians 
		// since the angle is assumed to be in radians
		float angle = float((angleDEG / 180.0f) * PI);

		// Here we calculate the sin( theta / 2) once for optimization
		float result = (float)sin( angle / 2.0f );
		
		// Calcualte the w value by cos( theta / 2 )
		m_coords[3] = (float)cos( angle / 2.0f );

		// Calculate the x, y and z of the quaternion
		m_coords[0] = float(x * result);
		m_coords[1] = float(y * result);
		m_coords[2] = float(z * result);
	}

	void CQuaternion::loadFromAxisAngle(const CVector3D& axis, float angleDEG){
		loadFromAxisAngle(axis.getX(), axis.getY(), axis.getZ(), angleDEG);
	}

	CQuaternion::operator float* const (){
		// First row
		m_rotMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z ); 
		m_rotMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
		m_rotMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
		m_rotMatrix[ 3] = 0.0f;  

		// Second row
		m_rotMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );  
		m_rotMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z ); 
		m_rotMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );  
		m_rotMatrix[ 7] = 0.0f;  

		// Third row
		m_rotMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
		m_rotMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
		m_rotMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );  
		m_rotMatrix[11] = 0.0f;  

		// Fourth row
		m_rotMatrix[12] = 0;  
		m_rotMatrix[13] = 0;  
		m_rotMatrix[14] = 0;  
		m_rotMatrix[15] = 1.0f;

		// Now pMatrix[] is a 4x4 homogeneous matrix that can be applied to an OpenGL Matrix
		return &m_rotMatrix[0];
	}

	//CQuaternion CQuaternion::operator *(const CQuaternion& q){
	//	CQuaternion r;
	//
	//	r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
	//	r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
	//	r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
	//	r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;
	//	
	//	return(r);
	//}
	CQuaternion CQuaternion::operator *(const CQuaternion& q) const{
		CQuaternion r;

		r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
		r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
		r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
		r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;
	
		return(r);
	}

	CQuaternion& CQuaternion::operator *=(const CQuaternion& q){
		float x, y, z, w;
		w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
		x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
		y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
		z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;
		m_x = x; m_y = y; m_z = z; m_w = w;

		return *this;
	}

	CVector3D	CQuaternion::operator *(const CVector3D& aVector3D){
		CVector3D vn = aVector3D;
		vn.normalize();
 
		CQuaternion vecQuat, resQuat;
		vecQuat.m_x = vn.getX();
		vecQuat.m_y = vn.getY();
		vecQuat.m_z = vn.getZ();
		vecQuat.m_w = 0.0f;
 
		resQuat = vecQuat * ~(*this);
		resQuat = *this * resQuat;
 
		return (CVector3D(resQuat.m_x, resQuat.m_y, resQuat.m_z));
	}
	CQuaternion	CQuaternion::operator ~(){
		//conjugate
		return CQuaternion(-m_x, -m_y, -m_z, m_w);
	}
	CVector3D CQuaternion::getRotationVector(){
		float scale = sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
		if(scale == 0.0f)
			return CVector3D(0.0, 0.0, 0.0);
		else
			return CVector3D(m_x / scale, m_y / scale, m_z = m_z / scale);
	}
	float CQuaternion::getRotationAngle() const{
		return (acos(m_w) * 2.0f)*RAD_2_DEG;
	}
	CQuaternion CQuaternion::fromR1toR2(CQuaternion r1, CQuaternion r2){
		CQuaternion q;
		q = ~r1 * r2;
		return q;
	}
	//========================================================
	CFactor3D::CFactor3D(): CHomoPoint(1.0f, 1.0f, 1.0f, 1.0f){
	}
	CFactor3D::CFactor3D(float xFactor, float yFactor, float zFactor):
		CHomoPoint(xFactor, yFactor, zFactor, 1.0f)
	{
	}
	CFactor3D::~CFactor3D(){
	}
	CFactor3D::CFactor3D(const CFactor3D& factors):
		CHomoPoint(factors.getX(), factors.getY(), factors.getZ(), 1.0f)
	{

	}

}