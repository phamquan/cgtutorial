// GeometricObject.h: interface for the CGeometricObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEOMETRICOBJECT_H__6C4FA14E_F450_4700_AC0D_D8701852EC9D__INCLUDED_)
#define AFX_GEOMETRICOBJECT_H__6C4FA14E_F450_4700_AC0D_D8701852EC9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
#include "HomoPoint.h"
#include "GL/gl.h"
#include "GL/glu.h"

class CGeometricObject  
{
public:
	CGeometricObject() {
		m_Scale.setCoords(1,1,1);
		m_Color.setCoords(0,0,0,1);
		for(int i = 0; i<16; i++)
			m_RotateMatrix[i] = 0;
		m_RotateMatrix[0] = m_RotateMatrix[5] = m_RotateMatrix[10] = m_RotateMatrix[15] = 1;
	}
	virtual ~CGeometricObject();
	virtual void Draw();
	virtual void setBegin(CPoint3D begin);
	virtual void setEnd(CPoint3D end);
	CPoint3D* getBegin();
	CPoint3D* getEnd();
	virtual CPoint3D* getCenter() = 0;
protected:
	inline float abs(float a) {return a>=0?a:-a;}
	virtual void Draw_Object() = 0;
	CPoint3D m_Begin;
	CPoint3D m_End;
	CPoint3D m_Middle;
	CPoint3D m_Center;

	CVector3D m_Scale;
	CVector3D m_Color;
};

#endif // !defined(AFX_GEOMETRICOBJECT_H__6C4FA14E_F450_4700_AC0D_D8701852EC9D__INCLUDED_)
