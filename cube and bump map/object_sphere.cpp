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

	CreateSphere(1,20,20);
	CalcTangentSpace();
	D3DXCreateCubeTexture(d3ddevice,128,1,D3DUSAGE_RENDERTARGET,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT ,&cube_texture);
	vertex_size = sizeof(CUSTOMVERTEX);

}

object_sphere::~object_sphere()
{
}

void object_sphere::SetShader()
{
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_WRAP );
	d3ddevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_WRAP );
	d3ddevice->SetRenderState( D3DRS_WRAP0, D3DWRAP_U | D3DWRAP_V);
	d3ddevice->SetTextureStageState(0, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(0, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );
	
	d3ddevice->SetTextureStageState(1, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP );
	d3ddevice->SetTextureStageState(1, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP );
	d3ddevice->SetTextureStageState(1, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(1, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );

	d3ddevice->SetTextureStageState(2, D3DTSS_MAGFILTER , D3DTEXF_LINEAR  );
	d3ddevice->SetTextureStageState(2, D3DTSS_MINFILTER , D3DTEXF_LINEAR  );


	if(shader_number == 0)
	{
		if(d3ddevice->SetVertexShader(phong_shader) != D3D_OK)
			MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);
		if(d3ddevice->SetPixelShader(spec_pixel) != D3D_OK)
			MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);

//		d3ddevice->SetVertexShader(phong_shader);
//		d3ddevice->SetPixelShader(spec_pixel);
	}
	else
	{
		if(d3ddevice->SetVertexShader(cube_shader) != D3D_OK)
			MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);
		if(d3ddevice->SetPixelShader(cube_pixel) != D3D_OK)
			MessageBox(NULL,"Failed to set vertex shader","error",MB_OK);

//		d3ddevice->SetVertexShader(cube_shader);
//		d3ddevice->SetPixelShader(cube_pixel);

	}

}
