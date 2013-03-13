// object_sphere.cpp: implementation of the object_sphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object_sphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

object_sphere::object_sphere()
{
/*	if(D3DXCreateSphere(d3ddevice,1,20,20,&mesh,NULL) != D3D_OK)
		MessageBox(NULL,"cant create sphere","error",MB_OK);;
	mesh->CloneMeshFVF(D3DXMESH_VB_MANAGED ,D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX3 | D3DFVF_TEXCOORDSIZE2(0)
						| D3DFVF_TEXCOORDSIZE3(1) | D3DFVF_TEXCOORDSIZE3(2),d3ddevice,&mesh);
	mesh->GetVertexBuffer(&vertex_buffer);
	//D3DVERTEXBUFFER_DESC Desc;
	mesh->GetIndexBuffer(&index_buffer);
	size = mesh->GetNumVertices();
	size2 = mesh->GetNumFaces();
	CalcTexCoords();
	*/
	CreateSphere(1,20,20);
	CalcTangentSpace();

/*vertex_buffer->GetDesc(&Desc);
	size = Desc.Size;
	size /= sizeof(CUSTOMVERTEX);*/
}

object_sphere::~object_sphere()
{
	//mesh->Release();
}

void object_sphere::SetShader()
{
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_DOTPRODUCT3);
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	d3ddevice->SetRenderState( D3DRS_WRAP0, D3DWRAP_U | D3DWRAP_V);
	d3ddevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	
	d3ddevice->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_MODULATE);
	d3ddevice->SetTextureStageState( 1, D3DTSS_COLORARG1, D3DTA_SPECULAR );
	d3ddevice->SetTextureStageState( 1, D3DTSS_COLORARG2, D3DTA_CURRENT );


	d3ddevice->SetVertexShader(phong_shader);
}
