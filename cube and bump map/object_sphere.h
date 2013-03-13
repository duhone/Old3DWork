// object_sphere.h: interface for the object_sphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_SPHERE_H__1D6A6B43_9679_4396_A9CF_098BA431CDBE__INCLUDED_)
#define AFX_OBJECT_SPHERE_H__1D6A6B43_9679_4396_A9CF_098BA431CDBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "object.h"

class object_sphere : public object  
{
public:
	object_sphere();
	virtual ~object_sphere();

protected:
	virtual void SetShader();
};

#endif // !defined(AFX_OBJECT_SPHERE_H__1D6A6B43_9679_4396_A9CF_098BA431CDBE__INCLUDED_)
