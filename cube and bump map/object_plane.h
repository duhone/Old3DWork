// object_plane.h: interface for the object_plane class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_PLANE_H__5B1F8553_719E_4124_B957_4863A430EC8C__INCLUDED_)
#define AFX_OBJECT_PLANE_H__5B1F8553_719E_4124_B957_4863A430EC8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "object.h"

struct CUSTOMVERTEXTEX
{
    FLOAT x, y, z; // The transformed position for the vertex.
 	CUSTOMVERTEXTEX(float a1,float a2,float a3,float a4,float a5,float a6,float a7,float a8)
	{
		x = a1;
		y = a2;
		z = a3;
	}
};

class object_plane : public object  
{
public:
	object_plane();
	virtual ~object_plane();

protected:
	virtual void SetShader();

};

#endif // !defined(AFX_OBJECT_PLANE_H__5B1F8553_719E_4124_B957_4863A430EC8C__INCLUDED_)
