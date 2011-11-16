#pragma once
#include  "math.h"
#include "cstringt.h"

#define PI			3.14159265358979323846
#define RAD_2_DEG	(180.0/PI)
#define DEG_2_RAD	(PI/180.0)

namespace QTMath {

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
		inline CHomoPoint&		setX(float x);
		inline CHomoPoint&		setY(float y);
		inline CHomoPoint&		setZ(float z);
		inline CHomoPoint&		setW(float w);
		inline float			getX() const;
		inline float			getY() const;
		inline float			getZ() const;
		inline float			getW() const;
		//CString toString();
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

	//============================================================================
	//CHomoPoint \
	//			CQuaternion
	class CQuaternion: public CHomoPoint  
	{
	public:
		CQuaternion(float x, float y, float z, float w);
		CQuaternion(const CVector3D& axis, float angleDEG);
		CQuaternion();
		virtual ~CQuaternion();
		//
		void loadIdentity();
		void loadFromAxisAngle(float x, float y, float z, float angleDEG);
		void loadFromAxisAngle(const CVector3D& axis, float angleDEG);
		CVector3D getRotationVector();
		float getRotationAngle() const;
		static CQuaternion fromR1toR2(CQuaternion r1, CQuaternion r2);

		operator float* const (); //casting
		//CQuaternion operator *(const CQuaternion& q);
		CQuaternion operator *(const CQuaternion& q) const;
		CQuaternion& operator *=(const CQuaternion& q);
		CVector3D	operator *(const CVector3D& aVector3D);
		CQuaternion	operator ~(); //conjugate
	protected:
		float	m_rotMatrix[16];
	};


	//============================================================================
	//CHomoPoint \
	//			CFactor3D
	class CFactor3D: public CHomoPoint
	{
	public:
		CFactor3D();
		CFactor3D(float xFactor, float yFactor, float zFactor);
		CFactor3D(const CFactor3D& factors);
		~CFactor3D();

	};

}