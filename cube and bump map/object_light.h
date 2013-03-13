// object_light.h: interface for the object_light class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_LIGHT_H__D8ABBB8E_9578_44FF_847B_0EF1E22F14A6__INCLUDED_)
#define AFX_OBJECT_LIGHT_H__D8ABBB8E_9578_44FF_847B_0EF1E22F14A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "object_sphere.h"
struct CUSTOMVERTEXSIMPLE
{
    FLOAT x, y, z; // The transformed position for the vertex.
  	CUSTOMVERTEXSIMPLE(float a1,float a2,float a3)
	{
		x = a1;
		y = a2;
		z = a3;
	}
};

class object_light : public object  
{
public:
	object_light();
	virtual ~object_light();

protected:
	virtual void SetShader();
};

#endif // !defined(AFX_OBJECT_LIGHT_H__D8ABBB8E_9578_44FF_847B_0EF1E22F14A6__INCLUDED_)
