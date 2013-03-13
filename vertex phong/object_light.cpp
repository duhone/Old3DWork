// object_light.cpp: implementation of the object_light class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object_light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

object_light::object_light()
{
	if(D3DXCreateSphere(d3ddevice,1.0f,10,10,&mesh,NULL) != D3D_OK)
		MessageBox(NULL,"cant create sphere","error",MB_OK);;
	mesh->CloneMeshFVF(D3DXMESH_VB_MANAGED ,D3DFVF_XYZ | D3DFVF_NORMAL,d3ddevice,&mesh);
	mesh->GetVertexBuffer(&vertex_buffer);
	mesh->GetIndexBuffer(&index_buffer);
	size = mesh->GetNumVertices();
	size2 = mesh->GetNumFaces();
	/*D3DVERTEXBUFFER_DESC Desc;
	size = Desc.Size;
	size /= sizeof(CUSTOMVERTEX);
*/
}

object_light::~object_light()
{
	mesh->Release();

}

void object_light::SetShader()
{
	d3ddevice->SetVertexShader(basic_shader);

}
