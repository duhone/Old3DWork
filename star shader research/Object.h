// HPT3DObjectInternal.h: interface for the HPT3DObjectInternal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HPT3DOBJECTINTERNAL_H__A305D4D5_E232_425E_A570_32168CB9AAAC__INCLUDED_)
#define AFX_HPT3DOBJECTINTERNAL_H__A305D4D5_E232_425E_A570_32168CB9AAAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"
#include <d3dx9.h>
#include"startexture.h"


class Object
{
public:
	int GetUV();
	void SetUV(int arg);
	void AnimateTemperatureMap();
	Object();
	virtual ~Object();
	virtual void Render();
	virtual void RenderHeat();
	virtual void SetPositionAbsalute(int x,int y,int z);
	virtual void SetPositionRelative(int x,int y,int z);
	virtual void Release();
	virtual void Scale(float scale_factor);
	virtual void Position(float x,float y,float z);
	virtual void Rotate(float y,float z);
	virtual void SetTemperature(int arg);
	virtual void SetBrightness(float r,float g,float b);
	
private:
	D3DXMATRIX world;
	D3DXMATRIX rot_worldz;
	D3DXMATRIX rot_worldy;
	D3DXMATRIX full;
	int temperature;
	float r_bright,g_bright,b_bright;
	StarTexture *star_texture;
	int uv;

};

#endif // !defined(AFX_HPT3DOBJECTINTERNAL_H__A305D4D5_E232_425E_A570_32168CB9AAAC__INCLUDED_)
