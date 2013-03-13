// oronaTexture.h: interface for the CoronaTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORONATEXTURE_H__E3943BB1_5125_49B9_9967_E0DBD6573F41__INCLUDED_)
#define AFX_ORONATEXTURE_H__E3943BB1_5125_49B9_9967_E0DBD6573F41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3d9.h>
#include <d3dx9.h>

class CoronaTexture  
{
public:
	CoronaTexture();
	virtual ~CoronaTexture();
private:
	LPDIRECT3DVOLUMETEXTURE9 corona_texture;
protected:
	void CreateDensity();
	float sample(float position,float step_size,float first,float second);

};

#endif // !defined(AFX_ORONATEXTURE_H__E3943BB1_5125_49B9_9967_E0DBD6573F41__INCLUDED_)
