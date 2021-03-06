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
#include"TextureStruct.h"
#include "StarTexture.h"

#define PI 3.141592653589

struct SpriteVertex
{
	float x,y,z;
	float tu,tv;
	float tx,ty,tz;
	float bx,by,bz;
	SpriteVertex() {};
	SpriteVertex(float xa,float ya,float za,float u,float v,float txa,float tya,float tza,float bxa,float bya,float bza)
	{
		x = xa;
		y = ya;
		z = za;
		tu = u;
		tv = v;
		tx = txa;
		ty = tya;
		tz = tza;
		bx = bxa;
		by = bya;
		bz = bza;
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
	void CreateSphereVertexBufferLow();
	void RenderSprite(D3DXMATRIX& world,int texture,D3DXVECTOR4& color);
	void RenderSphere(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR4& color,float np);
	void RenderSpherePoints(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR4& color,float np);
	void RenderSpherePoints2(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR4& color,float np);
	void RenderSphere2(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR4& color,float np);
	//void RenderSphereL(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR4& color,float np);
	//void RenderSphereP(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR3& light,float sky_pos,int night,float diffuse,float specular);
	//void RenderSphereE(D3DXMATRIX& world,int texture,int texture2,D3DXVECTOR3& light,float sky_pos,int night,float diffuse,float specular);
	//void RenderRing(D3DXMATRIX& world,int texture,D3DXVECTOR3& light);
	void CreateSpriteVertexBuffer();
	//void CreateRingVertexBuffer();
	GraphicsEngine(int quality);
	virtual ~GraphicsEngine();
	virtual int LoadHGF(TCHAR *name);
	virtual void Release();
	virtual HPT3DObject* Create3DObject();
	//virtual HPT3DObjectP* Create3DObjectP();
	virtual void BeginFrame();
	virtual void EndFrame();
//	virtual HPTGraphicsEngine& operator<<(HPTFont1* arg) = 0;
	virtual GraphicsEngine& operator<<(char *arg);
	virtual GraphicsEngine& operator<<(int arg);
	virtual GraphicsEngine& operator<<(unsigned int arg);
	virtual GraphicsEngine& operator<<(double arg);
	IDirect3DDevice9* GetD3DDevice() {return d3d_device;};
	virtual GraphicsEngine& Position(int x,int y);
	int GetQuality() {return render_quality;};
	bool GetTexture32bpp() {return texture32bpp;};
	virtual void SetTime(float time) {time_passed = time;};
	float time_passed;
	virtual void ResetStarTextureForFull();

private:
	bool texture32bpp;
	int render_quality;
	void ChangeGraphicsState(int arg);
	int graphics_state;
	int ring_cuts;
	int sphere_cuts;
	IDirect3D9 *d3d;
	IDirect3DDevice9* d3d_device;
	SpriteVertex sprite_vertexs[4];
	IDirect3DVertexBuffer9* sprite_vertex_buffer;
	IDirect3DVertexDeclaration9* sprite_vertex_decl;
	IDirect3DVertexShader9* sprite_vertex_shader; 
	IDirect3DVertexShader9* planet_vertex_shader; 
	IDirect3DVertexShader9* star_vertex_shader; 
	IDirect3DPixelShader9* star_pixel_shader; 
	IDirect3DVertexShader9* star_vertex_shader_points; 
	IDirect3DPixelShader9* star_pixel_shader_points; 
	IDirect3DVertexShader9* star_vertex_shader_high; 
	IDirect3DPixelShader9* star_pixel_shader_high; 
	IDirect3DVertexShader9* planet_vertex_shader_med; 
	IDirect3DPixelShader9* planet_pixel_shader_med; 
	IDirect3DVertexShader9* planet_vertex_shader_high; 
	IDirect3DPixelShader9* planet_pixel_shader_high; 
	IDirect3DVertexShader9* planet_vertex_shader_earth; 
	IDirect3DPixelShader9* planet_pixel_shader_earth; 
	IDirect3DVertexShader9* planck_vertex_shader; 
	IDirect3DPixelShader9* planck_pixel_shader; 

	IDirect3DVertexBuffer9* sphere_vertex_buffer;
	IDirect3DIndexBuffer9* sphere_index_buffer;
	IDirect3DVertexBuffer9* sphere_vertex_buffer_low;
	IDirect3DIndexBuffer9* sphere_index_buffer_low;
	IDirect3DVertexBuffer9* ring_vertex_buffer;
	int ring_size;
	int sphere_size;
	int sphere_v_size;
	int sphere_size_low;
	int sphere_v_size_low;
	D3DXMATRIX matview;
	D3DXMATRIX matproj;
	int num_entrys;
	HPTTextureStruct *entrys;
	HFONT font;
	ID3DXFont *d3dfont;
	int text_positionx,text_positiony;
	StarTexture *star_texture;
	
};

#endif // !defined(AFX_HPTGRAPHICSENGINEINTERNAL_H__C210BF6B_5A78_4E48_9CDA_46FE9A8F2737__INCLUDED_)
