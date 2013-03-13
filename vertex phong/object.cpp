// object.cpp: implementation of the object class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

object::object()
{
	D3DXMatrixIdentity(&matworld);
	center_pos.x = 0;
	center_pos.y = 0;
	center_pos.z = 0;
	angle = 0;
	speed = ((rand() % 8) + 1) / 200.0f;
	color[0] = 1;
	color[1] = 1;
	color[2] = 1;
	color[3] = 1;
	ambient[0] = 0.3f;
	ambient[1] = 0.3f;
	ambient[2] = 0.3f;
	ambient[3] = 0.3f;
	radius_of_rotation = 3;

}

object::~object()
{
	
}

void object::render()
{
	//SetShader();
	d3ddevice->SetVertexShaderConstant( 0, &D3DXVECTOR4(0,0,0,0), 1 );
	d3ddevice->SetVertexShaderConstant( 1, &D3DXVECTOR4(1,1,1,1), 1 );

	D3DXMATRIX mat;
	D3DXMATRIX matworldview;
	D3DXMATRIX temp;
	D3DXVECTOR4 light_vec;

	D3DXMatrixIdentity(&matworld);
	D3DXMatrixTranslation(&temp,radius_of_rotation,0,0);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );
	D3DXMatrixRotationY(&temp,angle);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );
	D3DXMatrixTranslation(&temp,center_pos.x,center_pos.y,center_pos.z);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );
	
	D3DXMatrixMultiply( &matworldview, &matworld, &matView );
	
	D3DXMatrixMultiply( &mat, &matworldview, &matProj );
	D3DXMatrixTranspose( &mat, &mat );
	d3ddevice->SetVertexShaderConstant( 2, &mat, 4 );
	D3DXMatrixInverse(&temp,NULL,&matworld);
	light_vec.x = light_pos[0];
	light_vec.y = light_pos[1];
	light_vec.z = light_pos[2];
	light_vec.w = 1;
	
	D3DXVec4Transform(&light_vec,&light_vec,&temp);
	//D3DXVec3Normalize(&light_vec,&light_vec);
	//D3DXMatrixTranspose( &temp, &temp );
	//d3ddevice->SetVertexShaderConstant( 6, &temp, 4 );

// Declare and define the constant vertex color.
	d3ddevice->SetVertexShaderConstant( 10, &color, 1 );

	d3ddevice->SetVertexShaderConstant( 11, &light_vec, 1 );
	d3ddevice->SetVertexShaderConstant( 12, &ambient, 1 );

	d3ddevice->SetStreamSource( 0, vertex_buffer, sizeof(CUSTOMVERTEX) );
	d3ddevice->SetIndices(index_buffer,0);
	d3ddevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0,size, 0,size2);

	//mesh->DrawSubset(1);
	
}


void object::SetCenterPosition(float x, float y, float z)
{
	center_pos.x = x;
	center_pos.y = y;
	center_pos.z = z;

}

void object::IncAngle()
{
	angle += speed;
}

void object::SetColor(float r, float g, float b, float a)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void object::SetRotationRadius(float r)
{
	radius_of_rotation = r;
}

void object::GetPosition(float &x, float &y, float &z)
{
	D3DXMATRIX mat;
	D3DXMATRIX temp;
	D3DXVECTOR3 tempv(0,0,0);
	
	D3DXMatrixIdentity(&matworld);
	D3DXMatrixTranslation(&temp,radius_of_rotation,0,0);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );
	D3DXMatrixRotationY(&temp,angle);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );
	D3DXMatrixTranslation(&temp,center_pos.x,center_pos.y,center_pos.z);
	D3DXMatrixMultiply( &matworld, &matworld, &temp );

	D3DXVec3TransformCoord(&tempv,&tempv,&matworld);
	
	x = tempv.x;
	y = tempv.y;
	z = tempv.z;
}

void object::SetLightPos(float *arg)
{
	light_pos[0] = arg[0];
	light_pos[1] = arg[1];
	light_pos[2] = arg[2];

	//memcpy(light_pos,arg,12);
}
