// HomoPoint.h: interface for the CHomoPoint class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include  "math.h"
#include "string.h"

#define PI			3.14159265358979323846
#define RAD_2_DEG	(180.0/PI)
#define DEG_2_RAD	(PI/180.0)

class CHomoPoint
{
public:
	CHomoPoint(void);
	CHomoPoint(const CHomoPoint& aPoint);
	CHomoPoint(float x, float y, float z, float w=1.0);
	CHomoPoint(float* xyzw);
	~CHomoPoint(void);
	//-----------------------------------------------------------------------------
	inline CHomoPoint&		setCoords(float x, float y, float z, float w=1.0);
	inline CHomoPoint&		setCoords(float* xyzw);
	inline CHomoPoint&		setX(float x) {m_coords[0] = x; return *this;}
	inline CHomoPoint&		setY(float y) {m_coords[1] = y; return *this;}
	inline CHomoPoint&		setZ(float z) {m_coords[2] = z; return *this;}
	inline CHomoPoint&		setW(float w) {m_coords[3] = w; return *this;}
	inline float			getX() const;
	inline float			getY() const;
	inline float			getZ() const;
	inline float			getW() const;
	CString toString();
	//cast operator o float* const
	operator float* const	();
	virtual CHomoPoint& operator	=(const CHomoPoint& aPoint);
	virtual bool operator==(const CHomoPoint& right);
protected:
	float m_coords[4];
};

//============================================================================
//CHomoPoint \
//			CPoint3D
class CPoint3D: public CHomoPoint{
	friend class CVector3D;
public:
	CPoint3D();
	CPoint3D(const CPoint3D& aPoint);
	CPoint3D(float x, float y, float z);
	CPoint3D(float* xyzw);
	CPoint3D(CVector3D aVect3D);
	~CPoint3D(void);
	//--------------------------------------------------
	//Cast operator
	operator CVector3D ();
	virtual bool operator==(const CPoint3D& aPoint);
	virtual CPoint3D& operator	=(const CPoint3D& aPoint);
	CPoint3D& setFromMousePoint(int x, int y, int vpWidth, int vpHeight);
	CPoint3D operator +(const CVector3D& aVect3D);
	CPoint3D operator +=(const CVector3D& aVect3D);
	CVector3D operator -(const CPoint3D& aPoint3D) const;
private:
protected:
};

CPoint3D MultMatrixPoint(float m[], CPoint3D point);
//============================================================================
//CHomoPoint \
//			CVector3D
class CVector3D: public CHomoPoint{
	friend class CPoint3D;
public:
	CVector3D();
	CVector3D(const CVector3D& aVector);
	CVector3D(float x, float y, float z);
	CVector3D(float* xyzw);
	~CVector3D(void);

	//----------------------------------------------
	//cast operator
	operator CPoint3D ();
	virtual CVector3D& operator	=(const CVector3D& aVect);
	virtual bool operator==(const CVector3D& aVect3D);

	inline float			getNorm() const;
	CVector3D				getNormVector();
	inline CVector3D&			normalize();
	CVector3D operator	+(const CVector3D& aVect) ;
	CVector3D operator	+=(const CVector3D& aVect) ;
	CVector3D operator	-(const CVector3D& aVect);
	CVector3D& operator	-=(const CVector3D& aVect) ;
	
	CVector3D operator	*(float factor) ;
	friend CVector3D operator*(float factor, CVector3D aVector);
	CVector3D operator	*=(float factor) ;
	
	CVector3D crossProduct(const CVector3D& aVect);
	float dotProduct(const CVector3D& aVect);
	
	static CVector3D fromP1toP2(CPoint3D p1, CPoint3D p2);
	CVector3D& operator - ();
	
private:
protected:
};

bool InvertMatrix(float src[16], float inverse[16]);