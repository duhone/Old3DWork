// object.h: interface for the object class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_H__0ECD5B75_28B2_4A5B_BD5D_CDA33CDF4C8B__INCLUDED_)
#define AFX_OBJECT_H__0ECD5B75_28B2_4A5B_BD5D_CDA33CDF4C8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
extern	LPDIRECT3DDEVICE8    d3ddevice; // Our rendering device
extern DWORD basic_shader;
extern DWORD phong_shader;
extern D3DXMATRIX matView;
extern D3DXMATRIX matProj;

struct CUSTOMVERTEX
{
    FLOAT x, y, z; // The transformed position for the vertex.
    float nx,ny,nz;        // The vertex color.
};


class object  
{
protected:
	int size2;
	float ambient[4];
	float light_pos[3];
	float speed;
	float angle;
	virtual void SetShader() = 0;
	int size;
	LPD3DXMESH mesh;
	LPDIRECT3DVERTEXBUFFER8 vertex_buffer;
	IDirect3DIndexBuffer8* index_buffer;
	LPD3DXBUFFER* adj;
	D3DXMATRIX matworld;
	D3DXVECTOR3 center_pos;
	float color[4];
	float radius_of_rotation;
public:
	void SetLightPos(float *arg);
	void GetPosition(float &x,float &y,float &z);
	void SetRotationRadius(float r);
	void SetColor(float r,float g,float b,float a);
	void IncAngle();
	void SetCenterPosition(float x,float y,float z);
	void render();
	object();
	virtual ~object();

};

#endif // !defined(AFX_OBJECT_H__0ECD5B75_28B2_4A5B_BD5D_CDA33CDF4C8B__INCLUDED_)
