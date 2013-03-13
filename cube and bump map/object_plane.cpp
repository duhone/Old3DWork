// object_plane.cpp: implementation of the object_plane class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object_plane.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

object_plane::object_plane()
{
	d3ddevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEXTEX), 0, 0, D3DPOOL_MANAGED, &vertex_buffer);
	d3ddevice->CreateIndexBuffer(6 * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &index_buffer);
	size = 4;
	size2 = 2;

	CUSTOMVERTEXTEX* pVertices;
	WORD* pIndices;
	
	vertex_buffer->Lock(0, 0, (BYTE**)&pVertices, 0);
	index_buffer->Lock(0, 0, (BYTE**)&pIndices, 0);

	pVertices[0].x = -50;
	pVertices[0].y = 0;
	pVertices[0].z = -50;

	pVertices[1].x = 50;
	pVertices[1].y = 0;
	pVertices[1].z = -50;

	pVertices[2].x = -50;
	pVertices[2].y = 0;
	pVertices[2].z = 50;

	pVertices[3].x = 50;
	pVertices[3].y = 0;
	pVertices[3].z = 50;

	pIndices[0] = 0;
	pIndices[1] = 2;
	pIndices[2] = 1;
	pIndices[3] = 1;
	pIndices[4] = 2;
	pIndices[5] = 3;

	vertex_buffer->Unlock();
	index_buffer->Unlock();

	vertex_size = sizeof(CUSTOMVERTEXTEX);



}

object_plane::~object_plane()
{

}

void object_plane::SetShader()
{
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	d3ddevice->SetRenderState( D3DRS_WRAP0, D3DWRAP_U | D3DWRAP_V);
	d3ddevice->SetTextureStageState(0, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(0, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );
	
/*	d3ddevice->SetTextureStageState(1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
	d3ddevice->SetTextureStageState(1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
	d3ddevice->SetTextureStageState(1, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(1, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );

	d3ddevice->SetTextureStageState(2, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(2, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );
*/
/*	if(shader_number == 0)
	{
		d3ddevice->SetVertexShader(phong_shader);
		d3ddevice->SetPixelShader(spec_pixel);
	}
	else
	{
		d3ddevice->SetVertexShader(cube_shader);
		d3ddevice->SetPixelShader(cube_pixel);

	}
*/
//		d3ddevice->SetVertexShader(tex_shader);
//		d3ddevice->SetPixelShader(tex_pixel);
//	d3ddevice->SetVertexShader(basic_shader);
//	d3ddevice->SetPixelShader(basic_pixel);
	if(d3ddevice->SetVertexShader(basic_shader) != D3D_OK)
		MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);
	if(d3ddevice->SetPixelShader(basic_pixel) != D3D_OK)
		MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);

}



