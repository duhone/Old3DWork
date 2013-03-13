// StarTexture.h: interface for the StarTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARTEXTURE_H__9FEFCAD2_0479_49CE_94E9_B5E78DE5DE09__INCLUDED_)
#define AFX_STARTEXTURE_H__9FEFCAD2_0479_49CE_94E9_B5E78DE5DE09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <d3d9.h>
#include <d3dx9.h>

#define NUM_POINTS 150000
#define FILTER_SPEED 0.05f
#define HEAT_RANGE 0.5f

struct HeatPoint
{
	float heat;
	float velocity;
	float max_heat;
	bool increasing;
	void Generate()
	{
		heat = 0;
		max_heat = (float)rand()+1;
		max_heat /= RAND_MAX;
		max_heat *= HEAT_RANGE; 
		velocity = 0;
		velocity = (float)rand()+1;
		velocity /= RAND_MAX;
		velocity *= max_heat;
		increasing = true;
	};

};


class StarTexture  
{
public:
	void DoFilter();
	void CreateRectangleBuffer();
	void Reset();
	void RenderTexture();
	void DoHeat();
	void LoadShaders();
	void CreatPointBuffer();
	StarTexture();
	virtual ~StarTexture();
	IDirect3DTexture9* front_texture;
private:
	float time_to_filter;
	int height;
	int width;
	double heat_added;
	IDirect3DVertexBuffer9* point_vertex_buffer;
	IDirect3DVertexBuffer9* rect_vertex_buffer;
	IDirect3DTexture9* back_texture;
	IDirect3DVertexDeclaration9* point_vertex_decl;
	
	IDirect3DVertexShader9* vertex_shader; 
	IDirect3DPixelShader9* pixel_shader; 
	
	IDirect3DVertexShader9* filter_vertex_shader; 
	IDirect3DPixelShader9* filter_pixel_shader; 
	HeatPoint heat_points[NUM_POINTS];

};

#endif // !defined(AFX_STARTEXTURE_H__9FEFCAD2_0479_49CE_94E9_B5E78DE5DE09__INCLUDED_)
