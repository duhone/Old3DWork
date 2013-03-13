// object.cpp: implementation of the object class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "object.h"

#define SMALL_FLOAT 1e-12

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
	texture = NULL;
	power_texture = NULL;
}

object::~object()
{
	
}

void object::render()
{
	SetShader();
	d3ddevice->SetVertexShaderConstant( 0, &D3DXVECTOR4(0,0,0,0), 1 );
	d3ddevice->SetVertexShaderConstant( 1, &D3DXVECTOR4(1,1,1,1), 1 );
	d3ddevice->SetVertexShaderConstant( 80, &D3DXVECTOR4(0.5f,0.5f,0.5f,0.5f), 1 );

	D3DXMATRIX mat;
	D3DXMATRIX matworldview;
	D3DXMATRIX temp;
	D3DXVECTOR4 light_vec;
	//D3DXVECTOR4 eye_vec;

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
	
	eye_pos.x = 0;
	eye_pos.y = 0;
	eye_pos.z = -15;
	eye_pos.w = 1;

	D3DXVec4Transform(&light_vec,&light_vec,&temp);
	D3DXVec4Transform(&eye_pos,&eye_pos,&temp);
	//D3DXVec3Normalize(&light_vec,&light_vec);
	//D3DXMatrixTranspose( &temp, &temp );
	//d3ddevice->SetVertexShaderConstant( 6, &temp, 4 );

// Declare and define the constant vertex color.
	D3DXVECTOR4 diff_color;
	diff_color = color;
	diff_color *= diffuse_amount;
	diff_color.w = 1;
	d3ddevice->SetVertexShaderConstant( 10, &color, 1 );
	d3ddevice->SetPixelShaderConstant( 2, &diff_color, 1 );
	D3DXVECTOR4 spec_color;
	spec_color = color;
	spec_color += D3DXVECTOR4(1,1,1,1);
	spec_color *= 0.5;
	spec_color *= specular_amount;
	spec_color.w = 1;
	d3ddevice->SetPixelShaderConstant( 4, &spec_color, 1 );

	d3ddevice->SetVertexShaderConstant( 11, &light_vec, 1 );
	d3ddevice->SetVertexShaderConstant( 13, &eye_pos, 1 );
	d3ddevice->SetVertexShaderConstant( 12, &ambient, 1 );
	
	D3DXVECTOR4 amb_color;
	amb_color = diff_color+spec_color;
	amb_color *= 0.1f;
	//amb_color.x *= color[0];
	//amb_color.y *= color[1];
	//amb_color.z *= color[2];
	amb_color.w = 1;

	d3ddevice->SetPixelShaderConstant( 3, &amb_color, 1 );

	//d3ddevice->SetPixelShaderConstant( 5, &D3DXVECTOR4(0,0,0,0), 1 );

//set texture
	if(texture != NULL)
		d3ddevice->SetTexture(0,texture);
	if(power_texture != NULL)
		d3ddevice->SetTexture(1,power_texture);

	
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

void object::LoadTexture(char *arg)
{
	D3DXCreateTextureFromFile(d3ddevice,arg,&texture);
}

void object::CalcTexCoords()
{
	CUSTOMVERTEX *data;
	vertex_buffer->Lock(0,0,(BYTE**)&data,0);
	float temp;
	for(int count = 0;count < size;count++)
	{
		temp = data[(count)].x;
		if(data[count].z < 0)
		{
			temp = 3-temp;
		}
		else temp += 1;
		temp /= 2.0;
		temp = 1-temp;
		data[count].tu = temp;			
		data[(count)].tv = 1-((data[(count)].y+1)/2);			
	}
	vertex_buffer->Unlock();
}

void object::CreateSphere(FLOAT fRadius, WORD wNumRings, WORD wNumSections)
{
    FLOAT x, y, z, v, rsintheta; // Temporary variables
    WORD  i, j, n, m;            // counters
    D3DXVECTOR3 vPoint;

//	SAFE_RELEASE(m_pSphereVertexBuffer);
//	SAFE_RELEASE(m_pSphereIndexBuffer);

    //Generate space for the required triangles and vertices.
    WORD       wNumTriangles = (wNumRings + 1) * wNumSections * 2;
    DWORD      dwNumIndices   = wNumTriangles*3;
    DWORD      dwNumVertices  = (wNumRings + 1) * wNumSections + 2;

//	m_dwNumVertices = dwNumVertices;
//	m_dwNumIndices = wNumTriangles * 3;
//	m_dwNumFaces = wNumTriangles;	

	d3ddevice->CreateVertexBuffer(dwNumVertices * sizeof(CUSTOMVERTEX), 0, 0, D3DPOOL_MANAGED, &vertex_buffer);
	d3ddevice->CreateIndexBuffer(3 * wNumTriangles * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &index_buffer);
	size = dwNumVertices;
	size2 = wNumTriangles;

	CUSTOMVERTEX* pVertices;
	WORD* pIndices;
	
	vertex_buffer->Lock(0, 0, (BYTE**)&pVertices, 0);
	index_buffer->Lock(0, 0, (BYTE**)&pIndices, 0);

    // Generate vertices at the top and bottom points.
    D3DXVECTOR3 vTopPoint  = D3DXVECTOR3( 0.0f, +fRadius, 0.0f);
    D3DXVECTOR3 vBotPoint  = D3DXVECTOR3( 0.0f, -fRadius, 0.0f);
    D3DXVECTOR3 vNormal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

    pVertices[0]               = CUSTOMVERTEX(vTopPoint.x, vTopPoint.y, vTopPoint.z,vNormal.x, vNormal.y, vNormal.z,0.0f, 0.0f );
    pVertices[dwNumVertices-1] = CUSTOMVERTEX(vBotPoint.x, vBotPoint.y, vBotPoint.z,-vNormal.x, -vNormal.y, -vNormal.z,0.0f, 0.0f );

    // Generate vertex points for rings
    FLOAT dtheta = (float)(D3DX_PI / (wNumRings + 2));     //Angle between each ring
    FLOAT dphi   = (float)(2*D3DX_PI / (wNumSections)); //Angle between each section
    FLOAT theta  = dtheta;
    n = 1; //vertex being generated, begins at 1 to skip top point

    for( i = 0; i < (wNumRings+1); i++ )
    {
        y = fRadius * (float)cos(theta); // y is the same for each ring
        v = theta / D3DX_PI;     // v is the same for each ring
        rsintheta = fRadius * (float)sin(theta);
        FLOAT phi = 0.0f;

        for( j = 0; j < wNumSections; j++ )
        {
            x = rsintheta * (float)sin(phi);
            z = rsintheta * (float)cos(phi);
        
            FLOAT u = 1.0f - (FLOAT)(phi / (2 * D3DX_PI) );
            vPoint        = D3DXVECTOR3( x, y, z );
            vNormal       = D3DXVECTOR3( x/fRadius, y/fRadius, z/fRadius );
			D3DXVec3Normalize(&vNormal, &vNormal);
			pVertices[n] = CUSTOMVERTEX( vPoint.x, vPoint.y, vPoint.z, vNormal.x, vNormal.y, vNormal.z, u, v );

            phi += dphi;
            ++n;
        }
        theta += dtheta;
    }

    // Generate triangles for top and bottom caps.
    for( i = 0; i < wNumSections; i++ )
    {
        pIndices[3*i+0] = 0;
        pIndices[3*i+1] = i + 1;
        pIndices[3*i+2] = 1 + ((i + 1) % wNumSections);

        pIndices[3*(wNumTriangles - wNumSections + i)+0] = (WORD)( dwNumVertices - 1 );
        pIndices[3*(wNumTriangles - wNumSections + i)+1] = (WORD)( dwNumVertices - 2 - i );
        pIndices[3*(wNumTriangles - wNumSections + i)+2] = (WORD)( dwNumVertices - 2 - 
                ((1 + i) % wNumSections) );
    }

    // Generate triangles for the rings
   m = 1;            // first vertex in current ring,begins at 1 to skip top point
    n = wNumSections; // triangle being generated, skip the top cap 
        
    for( i = 0; i < wNumRings; i++ )
    {
        for( j = 0; j < (wNumSections); j++ )
        {
            pIndices[3*n+0] = m + j;
            pIndices[3*n+1] = m + wNumSections + j;
            pIndices[3*n+2] = m + wNumSections + ((j + 1) % wNumSections);
            
            pIndices[3*(n+1)+0] = pIndices[3*n+0];
            pIndices[3*(n+1)+1] = pIndices[3*n+2];
            pIndices[3*(n+1)+2] = m + ((j + 1) % wNumSections);
            
            n += 2;
        }
      
        m += wNumSections;
    }

	vertex_buffer->Unlock();
	index_buffer->Unlock();

}

void object::CalcTangentSpace()
{
	CUSTOMVERTEX *data;
	unsigned short *index_data;
	vertex_buffer->Lock(0,0,(BYTE**)&data,0);
	index_buffer->Lock(0,0,(BYTE**)&index_data,0);
	int count;
//clear s and t
	for(count = 0;count < size;count++)
	{
		data[count].sx = 0;
		data[count].sy = 0;
		data[count].sz = 0;
		data[count].tx = 0;
		data[count].ty = 0;
		data[count].tz = 0;

	}

	for(count = 0;count < size2*3;count += 3)
	{
		int TriIndex[3];
		D3DXVECTOR3 du, dv;
		D3DXVECTOR3 edge01;
		D3DXVECTOR3 edge02;
		D3DXVECTOR3 cp;
		
		TriIndex[0] = index_data[count];
		TriIndex[1] = index_data[count+1];
		TriIndex[2] = index_data[count+2];

		CUSTOMVERTEX& v0 = data[TriIndex[0]];
		CUSTOMVERTEX &v1 = data[TriIndex[1]];
		CUSTOMVERTEX &v2 = data[TriIndex[2]];
		
		// x, s, t
		edge01 = D3DXVECTOR3( v1.x - v0.x, v1.tu - v0.tu, v1.tv - v0.tv );
		edge02 = D3DXVECTOR3( v2.x - v0.x, v2.tu - v0.tu, v2.tv - v0.tv );

		D3DXVec3Cross(&cp, &edge01, &edge02);
		if ( fabs(cp.x) > SMALL_FLOAT )
		{
			v0.sx += -cp.y / cp.x;
			v0.tx += -cp.z / cp.x;

			v1.sx += -cp.y / cp.x;
			v1.tx += -cp.z / cp.x;
			
			v2.sx += -cp.y / cp.x;
			v2.tx += -cp.z / cp.x;
		}

		edge01 = D3DXVECTOR3( v1.y - v0.y, v1.tu - v0.tu, v1.tv - v0.tv );
		edge02 = D3DXVECTOR3( v2.y - v0.y, v2.tu - v0.tu, v2.tv - v0.tv );

		D3DXVec3Cross(&cp, &edge01, &edge02);
		
		if ( fabs(cp.x) > SMALL_FLOAT )
		{
			v0.sy += -cp.y / cp.x;
			v0.ty += -cp.z / cp.x;

			v1.sy += -cp.y / cp.x;
			v1.ty += -cp.z / cp.x;
			
			v2.sy += -cp.y / cp.x;
			v2.ty += -cp.z / cp.x;
		}

		// z, s, t
		edge01 = D3DXVECTOR3( v1.z - v0.z, v1.tu - v0.tu, v1.tv - v0.tv );
		edge02 = D3DXVECTOR3( v2.z - v0.z, v2.tu - v0.tu, v2.tv - v0.tv );

		D3DXVec3Cross(&cp, &edge01, &edge02);
		
		if ( fabs(cp.x) > SMALL_FLOAT )
		{
			v0.sz += -cp.y / cp.x;
			v0.tz += -cp.z / cp.x;

			v1.sz += -cp.y / cp.x;
			v1.tz += -cp.z / cp.x;
			
			v2.sz += -cp.y / cp.x;
			v2.tz += -cp.z / cp.x;
		}
 
	};
	

	vertex_buffer->Unlock();
	index_buffer->Unlock();
}

void object::SetMaterial(float diff, float spec)
{
	diffuse_amount = diff;
	specular_amount = spec;
}

void object::SetSpecPower(float p)
{
	D3DLOCKED_RECT tex_info;
	unsigned char* data;
	d3ddevice->CreateTexture(2048,1,1,0,D3DFMT_A8R8G8B8, D3DPOOL_MANAGED ,&power_texture);
	power_texture->LockRect(0,&tex_info,NULL,0 );
	data = (unsigned char*)tex_info.pBits;
	float temp;
	unsigned char tempi;
	for(int count = 0;count < 2048;count++)
	{
		temp = (float)count;
		temp /= 2047.0f;
		temp = (float)pow(temp,p);
		temp *= 255.0f;
		tempi = (unsigned char)temp;
		data[count*4] = tempi;
		data[count*4+1] = tempi;
		data[count*4+2] = tempi;
		data[count*4+3] = 1;
	}
	power_texture->UnlockRect(0);

}
