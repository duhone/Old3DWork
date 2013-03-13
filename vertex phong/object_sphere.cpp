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
	if(D3DXCreateSphere(d3ddevice,1,10,10,&mesh,NULL) != D3D_OK)
		MessageBox(NULL,"cant create sphere","error",MB_OK);;
	mesh->CloneMeshFVF(D3DXMESH_VB_MANAGED ,D3DFVF_XYZ | D3DFVF_NORMAL,d3ddevice,&mesh);
	mesh->GetVertexBuffer(&vertex_buffer);
	//D3DVERTEXBUFFER_DESC Desc;
	mesh->GetIndexBuffer(&index_buffer);
	size = mesh->GetNumVertices();
	size2 = mesh->GetNumFaces();
/*vertex_buffer->GetDesc(&Desc);
	size = Desc.Size;
	size /= sizeof(CUSTOMVERTEX);*/
}

object_sphere::~object_sphere()
{
	mesh->Release();
}

void object_sphere::SetShader()
{
	d3ddevice->SetVertexShader(phong_shader);
}
