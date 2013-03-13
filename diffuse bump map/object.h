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
    float nx,ny,nz;  // The vertex color.
	float tu,tv;
	float tx,ty,tz;
	float sx,sy,sz;
	CUSTOMVERTEX(float a1,float a2,float a3,float a4,float a5,float a6,float a7,float a8)
	{
		x = a1;
		y = a2;
		z = a3;
		nx = a4;
		ny = a5;
		nz = a6;
		tu = a7;
		tv = a8;
	}
};


class object  
{
protected:
	void CalcTexCoords();
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
	LPDIRECT3DTEXTURE8 texture;
	LPD3DXBUFFER* adj;
	D3DXMATRIX matworld;
	D3DXVECTOR3 center_pos;
	float color[4];
	float radius_of_rotation;
public:
	void CreateSphere(FLOAT fRadius, WORD wNumRings, WORD wNumSections);
	void CalcTangentSpace();
	void LoadTexture(char *);
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
