// HPT3DObjectInternal.cpp: implementation of the HPT3DObjectInternal class.
//
//////////////////////////////////////////////////////////////////////

#include "Object.h"
#include "GraphicsEngine.h"

extern GraphicsEngine *gengine;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Object::Object()
{
	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&rot_worldy);
	D3DXMatrixIdentity(&rot_worldz);
	star_texture = new StarTexture();
	star_texture->Reset();
	uv = false;
}

Object::~Object()
{
	delete star_texture;
}





void Object::RenderHeat()
{
	gengine->GetD3DDevice()->SetRenderState( D3DRS_ZENABLE, TRUE );
	gengine->GetD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);


	//form transformation matrix
	D3DXMatrixMultiply(&full,&rot_worldy,&rot_worldz);
	D3DXMatrixMultiply(&full,&full,&world);
	D3DXMATRIX temp;
	D3DXMatrixMultiply(&temp,&full,&(gengine->GetMatView()));
	D3DXMatrixMultiply(&temp,&temp,&(gengine->GetMatProj()));
	D3DXMatrixTranspose( &temp, &temp );
	gengine->GetD3DDevice()->SetVertexShaderConstantF(0,temp,4);


	gengine->ChangeGraphicsState(2);

	

	gengine->GetD3DDevice()->SetTexture(0,star_texture->front_texture);
	gengine->GetD3DDevice()->SetIndices(gengine->GetIndexBuffer());
	gengine->GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,gengine->GetSphereVSize(),0,gengine->GetSphereSize());

}

void Object::Render()
{

	gengine->GetD3DDevice()->SetRenderState( D3DRS_ZENABLE, TRUE );
	gengine->GetD3DDevice()->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

	//create transformation matrix
	D3DXMatrixMultiply(&full,&rot_worldy,&rot_worldz);
	D3DXMatrixMultiply(&full,&full,&world);
	D3DXMATRIX temp;
	D3DXMatrixMultiply(&temp,&full,&(gengine->GetMatView()));
	D3DXMatrixMultiply(&temp,&temp,&(gengine->GetMatProj()));
	D3DXMatrixTranspose( &temp, &temp );


	gengine->ChangeGraphicsState(3);


	gengine->GetD3DDevice()->SetVertexShaderConstantF(0,temp,4);
	gengine->GetD3DDevice()->SetPixelShaderConstantF(6,D3DXVECTOR4((float)temperature,(float)temperature,(float)temperature,(float)temperature),1);
	gengine->GetD3DDevice()->SetPixelShaderConstantF(18,D3DXVECTOR4(r_bright,g_bright,b_bright,1.0f),1);
	gengine->GetD3DDevice()->SetPixelShaderConstantB(0,&uv,1);

	//projection for view vector to object space
	D3DXMatrixMultiply(&temp,&full,&(gengine->GetMatView()));
	D3DXMatrixInverse(&temp,NULL, &temp);
	D3DXMatrixTranspose( &temp, &temp );
	gengine->GetD3DDevice()->SetVertexShaderConstantF(4,temp,4);

	gengine->GetD3DDevice()->SetTexture(0,star_texture->front_texture);
	gengine->GetD3DDevice()->SetIndices(gengine->GetIndexBuffer());
	gengine->GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,gengine->GetSphereVSize(),0,gengine->GetSphereSize());

}

void Object::SetPositionAbsalute(int x,int y,int z)
{

}

void Object::SetPositionRelative(int x,int y,int z)
{

}

void Object::Release()
{
	delete this;
}

void Object::Scale(float scale_factor)
{
	world(0,0) = scale_factor;
	world(1,1) = scale_factor;
	world(2,2) = scale_factor;

}

void Object::Position(float x,float y,float z)
{
	world(3,0) = x;
	world(3,1) = y;
	world(3,2) = z;
}

void Object::Rotate(float y,float z)
{
	D3DXMatrixRotationY(&rot_worldy,y);
	D3DXMatrixRotationY(&rot_worldz,z);

}

void Object::SetTemperature(int arg)
{
	temperature = arg;
}

void Object::SetBrightness(float r,float g,float b)
{
	r_bright = r;
	g_bright = g;
	b_bright = b;

}

void Object::AnimateTemperatureMap()
{
	star_texture->RenderTexture();
}

void Object::SetUV(int arg)
{
	uv = arg;
}

int Object::GetUV()
{
	return uv;
}
