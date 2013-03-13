// HPTGraphicsEngineInternal.h: interface for the HPTGraphicsEngineInternal class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HPTGRAPHICSENGINEINTERNAL_H__C210BF6B_5A78_4E48_9CDA_46FE9A8F2737__INCLUDED_)
#define AFX_HPTGRAPHICSENGINEINTERNAL_H__C210BF6B_5A78_4E48_9CDA_46FE9A8F2737__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphics.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "StarTexture.h"
#include"Object.h"

#define PI 3.141592653589

struct StarVertex
{
	float x,y,z;
	float tu,tv;
	StarVertex() {};
	StarVertex(float xa,float ya,float za,float u,float v)
	{
		x = xa;
		y = ya;
		z = za;
		tu = u;
		tv = v;
	};
};

struct PointVertex
{
	float theta,delta;
	float temperature;
	PointVertex() {};
	PointVertex(float ta,float da)
	{
		theta = ta;
		delta = da;
		temperature = 0;
	};
};

class GraphicsEngine
{
public:
	void LoadShaders();
	void CreateSphereVertexBuffer();
	GraphicsEngine();
	virtual ~GraphicsEngine();
	virtual void Release();
	virtual Object* CreateObject();
	virtual void BeginFrame();
	virtual void EndFrame();
	virtual GraphicsEngine& operator<<(char *arg);
	virtual GraphicsEngine& operator<<(int arg);
	virtual GraphicsEngine& operator<<(unsigned int arg);
	virtual GraphicsEngine& operator<<(double arg);
	IDirect3DDevice9* GetD3DDevice() {return d3d_device;};
	virtual GraphicsEngine& Position(int x,int y);
	virtual void SetTime(float time) {time_passed = time;};
	float time_passed;
	void ChangeGraphicsState(int arg);
	D3DXMATRIX GetMatView() {return matview;};
	D3DXMATRIX GetMatProj() {return matproj;};
	IDirect3DVertexBuffer9* GetVertextBuffer() {return sphere_vertex_buffer;};
	IDirect3DIndexBuffer9* GetIndexBuffer() {return sphere_index_buffer;};
	int GetSphereSize() {return sphere_size;};
	int GetSphereVSize() {return sphere_v_size;};
	
private:
	int sphere_cuts;
	IDirect3D9 *d3d;
	IDirect3DDevice9* d3d_device;

	IDirect3DVertexDeclaration9* star_vertex_decl;

	IDirect3DVertexShader9* star_vertex_shader_heat; 
	IDirect3DPixelShader9* star_pixel_shader_heat; 
	IDirect3DVertexShader9* planck_vertex_shader; 
	IDirect3DPixelShader9* planck_pixel_shader; 

	IDirect3DVertexBuffer9* sphere_vertex_buffer;
	IDirect3DIndexBuffer9* sphere_index_buffer;

	int sphere_size;
	int sphere_v_size;
	D3DXMATRIX matview;
	D3DXMATRIX matproj;
	ID3DXFont *d3dfont;
	int text_positionx,text_positiony;
	
};

#endif // !defined(AFX_HPTGRAPHICSENGINEINTERNAL_H__C210BF6B_5A78_4E48_9CDA_46FE9A8F2737__INCLUDED_)
