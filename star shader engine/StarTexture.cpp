// StarTexture.cpp: implementation of the StarTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "StarTexture.h"
#include<vector>
#include "HPTGraphicsEngineInternal.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern HPTGraphicsEngineInternal *gengine;

StarTexture::StarTexture()
{
	width = 2048;
	height = 1024;
	for(int count = 0;count < NUM_POINTS;count++)
	{
		heat_points[count].Generate();
	}
	CreatPointBuffer();
	CreateRectangleBuffer();
	gengine->GetD3DDevice()->CreateTexture(width,height,1,D3DUSAGE_RENDERTARGET/*D3DUSAGE_AUTOGENMIPMAP*/,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT ,&back_texture,NULL);
	//D3DXFilterTexture(back_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);
	gengine->GetD3DDevice()->CreateTexture(width,height,1,D3DUSAGE_RENDERTARGET/*D3DUSAGE_AUTOGENMIPMAP*/,D3DFMT_A16B16G16R16F,D3DPOOL_DEFAULT ,&front_texture,NULL);
	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 8, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	gengine->GetD3DDevice()->CreateVertexDeclaration(decl,&point_vertex_decl);
	LoadShaders();

}

StarTexture::~StarTexture()
{

}

void StarTexture::CreatPointBuffer()
{
	vector<PointVertex> buffer;

/*	for(float theta = 0;theta <= PI;theta += PI/SPHERE_CUTS)
	{
		buffer.push_back(SpriteVertex(0,cos(theta-PI),sin(theta),0.5f,(cos(theta)+1)/2));

	}
*/

	float delta,theta;
	for(int count = 0;count < NUM_POINTS;count++)
	{
		delta = rand();
		delta /= RAND_MAX;
		delta -= 0.5f;
		delta *= 2;
		theta = rand();
		theta /= RAND_MAX;
		theta -= 0.5f;
		theta *= 2;
		theta = asin(theta);
		theta /= PI;
		theta *= 2;
		buffer.push_back(PointVertex(delta,theta));
	}

	PointVertex* tempv;

	gengine->GetD3DDevice()->CreateVertexBuffer(buffer.size() * sizeof(PointVertex),D3DUSAGE_WRITEONLY,0,D3DPOOL_DEFAULT,&point_vertex_buffer,NULL);
	point_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	memcpy(tempv,&(buffer[0]),buffer.size()*sizeof(PointVertex));
	point_vertex_buffer->Unlock();

}

void StarTexture::RenderTexture()
{
	DoHeat();

	IDirect3DTexture9* temp_texture;
	temp_texture = front_texture;
	front_texture = back_texture;
	back_texture = temp_texture;

	IDirect3DDevice9* d3d_device = gengine->GetD3DDevice();
	IDirect3DSurface9 *render_target;
	d3d_device->GetRenderTarget(0,&render_target);
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	d3d_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE  );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	d3d_device->SetVertexShader(vertex_shader);
	d3d_device->SetPixelShader(NULL);
	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
/*	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);*/

	D3DXMATRIX temp;
	D3DXMatrixPerspectiveFovLH( &temp, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );

	D3DXMatrixOrthoLH(&temp,1,1,0,1);

	D3DXMatrixTranspose( &temp, &temp );

	d3d_device->SetVertexShaderConstantF(0,temp,4);
	
	
	d3d_device->SetVertexDeclaration(point_vertex_decl);
	d3d_device->SetStreamSource(0,point_vertex_buffer,0,sizeof(PointVertex));
	d3d_device->SetVertexShaderConstantF(4,D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(5,D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),1);
	d3d_device->SetPixelShaderConstantF(0,D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f),1);


	
	
	
	IDirect3DSurface9 *surface;
	front_texture->GetSurfaceLevel(0,&surface);
	d3d_device->SetRenderTarget(0,surface);
	surface->Release();

	d3d_device->Clear(0,NULL,D3DCLEAR_TARGET,0,1.0f,0);
	d3d_device->BeginScene();

	d3d_device->SetTexture(0,back_texture);
	d3d_device->DrawPrimitive(D3DPT_POINTLIST,0,NUM_POINTS);
	
	d3d_device->EndScene();
	
	d3d_device->SetRenderTarget(0,render_target);
	render_target->Release();
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	//IDirect3DSurface9 *surface;
	front_texture->GetSurfaceLevel(0,&surface);
	
	//D3DXSaveSurfaceToFile("out texture.bmp",D3DXIFF_BMP,surface,NULL,NULL);
	surface->Release();

}

void StarTexture::LoadShaders()
{
	LPD3DXBUFFER tempvbufer;
	LPD3DXBUFFER emsg;
	if(D3DXAssembleShaderFromFile("points vertex shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	gengine->GetD3DDevice()->CreateVertexShader((const unsigned long*)tempvbufer->GetBufferPointer(),&vertex_shader);

	if(D3DXAssembleShaderFromFile("points pixel shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	gengine->GetD3DDevice()->CreatePixelShader((const unsigned long*)tempvbufer->GetBufferPointer(),&pixel_shader);

	if(D3DXAssembleShaderFromFile("cool pixel shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	gengine->GetD3DDevice()->CreatePixelShader((const unsigned long*)tempvbufer->GetBufferPointer(),&cool_pixel_shader);
	
	if(D3DXAssembleShaderFromFile("filter vertex shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	gengine->GetD3DDevice()->CreateVertexShader((const unsigned long*)tempvbufer->GetBufferPointer(),&filter_vertex_shader);

	if(D3DXAssembleShaderFromFile("filter pixel shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	gengine->GetD3DDevice()->CreatePixelShader((const unsigned long*)tempvbufer->GetBufferPointer(),&filter_pixel_shader);

}

void StarTexture::DoHeat()
{
	PointVertex* tempv;

	point_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	float time = gengine->time_passed;

	for(int count = 0;count < NUM_POINTS;count++)
	{
		if(heat_points[count].increasing)
		{
			heat_points[count].heat += heat_points[count].velocity*time;
			if(heat_points[count].heat >= heat_points[count].max_heat)
				heat_points[count].increasing = false;
			
			//heat_points[count].heat += heat_points[count].velocity*time;
		}
		else
		{
			heat_points[count].heat -= heat_points[count].velocity*time;
						
			if(heat_points[count].heat <= 0)
			{
				heat_points[count].Generate();
				float delta,theta;
				delta = rand();
				delta /= RAND_MAX;
				delta -= 0.5f;
				delta *= 2;
				theta = rand();
				theta /= RAND_MAX;
				theta -= 0.5f;
				theta *= 2;
				theta = asin(theta);
				theta /= PI;
				theta *= 2;
				tempv[count].delta = theta;
				tempv[count].theta = delta;
				tempv[count].temperature = 0;
			}
			//else heat_points[count].heat -= heat_points[count].velocity*time;

		}
		tempv[count].temperature = heat_points[count].heat*time*20;
		heat_added += heat_points[count].heat*time;
	}	


	point_vertex_buffer->Unlock();

}

void StarTexture::DoHeatFull()
{
	IDirect3DTexture9* temp_texture;
	
	PointVertex* tempv;

	point_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	float time = gengine->time_passed;

	for(int count = 0;count < (NUM_POINTS/2);count++)
	{
		if(heat_points[count*2].increasing)
		{
			heat_points[count*2].heat += heat_points[count*2].velocity*time;
			if(heat_points[count*2].heat >= heat_points[count*2].max_heat)
			{
				heat_points[count*2].increasing = false;
				heat_points[count*2].heat = heat_points[count*2].max_heat;
			}
			
			//heat_points[count].heat += heat_points[count].velocity*time;
		}
		else
		{
			heat_points[count*2].heat -= heat_points[count*2].velocity*time;
						
			if(heat_points[count*2].heat <= 0)
			{
				heat_points[count*2].Generate();
				float delta,theta;
				delta = rand();
				delta /= RAND_MAX;
				delta -= 0.5f;
				delta *= 2;
				theta = rand();
				theta /= RAND_MAX;
				theta -= 0.5f;
				theta *= 2;
				theta = asin(theta);
				theta /= PI;
				theta *= 2;
				tempv[count*2].delta = theta;
				tempv[count*2].theta = delta;
				tempv[count*2].temperature = 0;
				heat_points[count*2+1].Generate();
				//float delta,theta;
				delta = rand();
				delta /= RAND_MAX;
				delta -= 0.5f;
				delta *= 2;
				theta = rand();
				theta /= RAND_MAX;
				theta -= 0.5f;
				theta *= 2;
				theta = asin(theta);
				theta /= PI;
				theta *= 2;
				tempv[count*2+1].delta = theta;
				tempv[count*2+1].theta = delta;
				tempv[count*2+1].temperature = 0;
			}
			//else heat_points[count].heat -= heat_points[count].velocity*time;

		}
		tempv[count*2].temperature = heat_points[count*2].heat*time;
		tempv[count*2+1].temperature = -heat_points[count*2].heat*time;
		//heat_added += tempv[count].temperature;
	}	


	point_vertex_buffer->Unlock();

}

void StarTexture::RenderTexture2()
{

	IDirect3DDevice9* d3d_device = gengine->GetD3DDevice();
	d3d_device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
	/*if(heat_added > (width*height/256.0))*/ //DoCool();
	DoHeatFull();

	IDirect3DTexture9* temp_texture;
		IDirect3DSurface9 *render_target;
	//d3d_device->SetSamplerState(0,D3DSAMP_MAXANISOTROPY,8);
	d3d_device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);

	d3d_device->GetRenderTarget(0,&render_target);
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	d3d_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE  );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	d3d_device->SetVertexShader(vertex_shader);
	d3d_device->SetPixelShader(pixel_shader);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
/*	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);*/

	D3DXMATRIX temp;
	D3DXMatrixPerspectiveFovLH( &temp, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );

	D3DXMatrixOrthoLH(&temp,1,1,0,1);

	D3DXMatrixTranspose( &temp, &temp );

	d3d_device->SetVertexShaderConstantF(0,temp,4);
	
	
	d3d_device->SetVertexDeclaration(point_vertex_decl);
	d3d_device->SetStreamSource(0,point_vertex_buffer,0,sizeof(PointVertex));
	d3d_device->SetVertexShaderConstantF(4,D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(5,D3DXVECTOR4(0.5f,1.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(6,D3DXVECTOR4(1.0/width,1.0/height,1.0/(width*2),1.0/(height*2)),1);
	d3d_device->SetPixelShaderConstantF(0,D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f),1);
	d3d_device->SetPixelShaderConstantF(1,D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),1);


	
	
	
	IDirect3DSurface9 *surface;
	front_texture->GetSurfaceLevel(0,&surface);
	d3d_device->SetRenderTarget(0,surface);
	surface->Release();

	//d3d_device->Clear(0,NULL,D3DCLEAR_TARGET,0.5f,1.0f,0);
	d3d_device->BeginScene();

	d3d_device->SetTexture(0,back_texture);
	d3d_device->DrawPrimitive(D3DPT_POINTLIST,0,NUM_POINTS);
	
	d3d_device->EndScene();
	
	temp_texture = front_texture;
	front_texture = back_texture;
	back_texture = temp_texture;

	DoFilter();

	d3d_device->SetRenderTarget(0,render_target);
	render_target->Release();

	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	//IDirect3DSurface9 *surface;
	//front_texture->GetSurfaceLevel(0,&surface);
	
	//D3DXSaveSurfaceToFile("out texture.bmp",D3DXIFF_BMP,surface,NULL,NULL);
	//surface->Release();

/*	d3d_device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);*/
		d3d_device->SetSamplerState(0,D3DSAMP_MAXANISOTROPY,8);
		d3d_device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);
		d3d_device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);
		d3d_device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);


}

void StarTexture::ResetForFull()
{
	time_to_filter = 1.0/10.0;
	heat_added = 0;
	IDirect3DTexture9* temp_texture;
	temp_texture = front_texture;
	front_texture = back_texture;
	back_texture = temp_texture;

	IDirect3DDevice9* d3d_device = gengine->GetD3DDevice();
	IDirect3DSurface9 *render_target;
	d3d_device->GetRenderTarget(0,&render_target);
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	d3d_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE  );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	d3d_device->SetVertexShader(vertex_shader);
	d3d_device->SetPixelShader(pixel_shader);
	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
/*	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);*/

	D3DXMATRIX temp;
	D3DXMatrixPerspectiveFovLH( &temp, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );

	D3DXMatrixOrthoLH(&temp,1,1,0,1);

	D3DXMatrixTranspose( &temp, &temp );

	d3d_device->SetVertexShaderConstantF(0,temp,4);
	
	
	d3d_device->SetVertexDeclaration(point_vertex_decl);
	d3d_device->SetStreamSource(0,point_vertex_buffer,0,sizeof(PointVertex));
	d3d_device->SetVertexShaderConstantF(4,D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(5,D3DXVECTOR4(1.0f,1.0f,1.0f,1.0f),1);
	d3d_device->SetPixelShaderConstantF(0,D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f),1);
	d3d_device->SetPixelShaderConstantF(1,D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),1);


	
	
	
	IDirect3DSurface9 *surface;
	back_texture->GetSurfaceLevel(0,&surface);
	d3d_device->SetRenderTarget(0,surface);
	surface->Release();

	d3d_device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_ARGB(256,0,0,0),1.0f,0);
	d3d_device->BeginScene();

	//d3d_device->SetTexture(0,back_texture);
	//d3d_device->DrawPrimitive(D3DPT_POINTLIST,0,NUM_POINTS);
	
	d3d_device->EndScene();
	
	d3d_device->SetRenderTarget(0,render_target);
	render_target->Release();
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);

	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	//IDirect3DSurface9 *surface;
	//front_texture->GetSurfaceLevel(0,&surface);
	
	//D3DXSaveSurfaceToFile("out texture.bmp",D3DXIFF_BMP,surface,NULL,NULL);
	//surface->Release();

}

void StarTexture::CreateRectangleBuffer()
{
	vector<PointVertex> buffer;

/*	for(float theta = 0;theta <= PI;theta += PI/SPHERE_CUTS)
	{
		buffer.push_back(SpriteVertex(0,cos(theta-PI),sin(theta),0.5f,(cos(theta)+1)/2));

	}
*/

	buffer.push_back(PointVertex(-1,-1));
	buffer.push_back(PointVertex(-1,1));
	buffer.push_back(PointVertex(1,-1));
	buffer.push_back(PointVertex(-1,1));
	buffer.push_back(PointVertex(1,1));
	buffer.push_back(PointVertex(1,-1));

	PointVertex* tempv;

	gengine->GetD3DDevice()->CreateVertexBuffer(buffer.size() * sizeof(PointVertex),D3DUSAGE_WRITEONLY,0,D3DPOOL_DEFAULT,&rect_vertex_buffer,NULL);
	rect_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	memcpy(tempv,&(buffer[0]),buffer.size()*sizeof(PointVertex));
	rect_vertex_buffer->Unlock();

}

void StarTexture::DoCool()
{
	/*double amount = floor(heat_added/(width*height/256.0));
	heat_added -= (width*height/256.0);
	amount = 1/256.0;*/
	
	float amount = heat_added/(width*height);
	heat_added -= (double)amount*width*height;
	
	IDirect3DTexture9* temp_texture;
	temp_texture = front_texture;
	front_texture = back_texture;
	back_texture = temp_texture;

	IDirect3DDevice9* d3d_device = gengine->GetD3DDevice();
	IDirect3DSurface9 *render_target;
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	d3d_device->GetRenderTarget(0,&render_target);
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	d3d_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE  );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	d3d_device->SetVertexShader(vertex_shader);
	d3d_device->SetPixelShader(cool_pixel_shader);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
/*	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);*/

	D3DXMATRIX temp;
	D3DXMatrixPerspectiveFovLH( &temp, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );

	D3DXMatrixOrthoLH(&temp,1,1,0,1);

	D3DXMatrixTranspose( &temp, &temp );

	d3d_device->SetVertexShaderConstantF(0,temp,4);
	
	
	d3d_device->SetVertexDeclaration(point_vertex_decl);
	d3d_device->SetStreamSource(0,rect_vertex_buffer,0,sizeof(PointVertex));
	d3d_device->SetVertexShaderConstantF(4,D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(5,D3DXVECTOR4(0.5f,1.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(6,D3DXVECTOR4(1.0/width,1.0/height,1.0/(width*2),1.0/(height*2)),1);
	d3d_device->SetPixelShaderConstantF(0,D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f),1);
	d3d_device->SetPixelShaderConstantF(1,D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),1);
	d3d_device->SetPixelShaderConstantF(2,D3DXVECTOR4(-amount,-amount,-amount,1.0f),1);


	
	
	
	IDirect3DSurface9 *surface;
	front_texture->GetSurfaceLevel(0,&surface);
	d3d_device->SetRenderTarget(0,surface);
	surface->Release();

	//d3d_device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_ARGB(128,128,128,128),1.0f,0);
	d3d_device->BeginScene();

	d3d_device->SetTexture(0,back_texture);
	d3d_device->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
	
	d3d_device->EndScene();
	
	d3d_device->SetRenderTarget(0,render_target);
	render_target->Release();
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW);

	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	//IDirect3DSurface9 *surface;
	//front_texture->GetSurfaceLevel(0,&surface);
	
	//D3DXSaveSurfaceToFile("out texture.bmp",D3DXIFF_BMP,surface,NULL,NULL);
	//surface->Release();
}

void StarTexture::DoFilter()
{

	static bool skipframe = false;
	skipframe = !skipframe;
	//if(skipframe) return;
	if(time_to_filter > 0)
	{
		time_to_filter -= gengine->time_passed;
		return;
	}
	else time_to_filter += FILTER_SPEED;
	float time = gengine->time_passed;
	IDirect3DTexture9* temp_texture;
	
	IDirect3DDevice9* d3d_device = gengine->GetD3DDevice();
	IDirect3DSurface9 *render_target;
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	d3d_device->GetRenderTarget(0,&render_target);
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);
	d3d_device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE  );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, D3DZB_FALSE );

	d3d_device->SetVertexShader(filter_vertex_shader);
	d3d_device->SetPixelShader(filter_pixel_shader);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	//d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG2);
/*	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);*/

	D3DXMATRIX temp;
	D3DXMatrixPerspectiveFovLH( &temp, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );

	D3DXMatrixOrthoLH(&temp,1,1,0,1);

	D3DXMatrixTranspose( &temp, &temp );

	d3d_device->SetVertexShaderConstantF(0,temp,4);
	
	
	d3d_device->SetVertexDeclaration(point_vertex_decl);
	d3d_device->SetStreamSource(0,rect_vertex_buffer,0,sizeof(PointVertex));
	d3d_device->SetVertexShaderConstantF(4,D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(5,D3DXVECTOR4(0.5f,1.0f,1.0f,1.0f),1);
	d3d_device->SetVertexShaderConstantF(6,D3DXVECTOR4(1.0/width,1.0/height,1.0/(width*2),1.0/(height*2)),1);
	d3d_device->SetPixelShaderConstantF(0,D3DXVECTOR4(0.0f,0.0f,0.0f,0.0f),1);
	d3d_device->SetPixelShaderConstantF(1,D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),1);
	d3d_device->SetPixelShaderConstantF(2,D3DXVECTOR4(1.0/5.0,1.0/5.0,1.0/5.0,1.0/5.0),1);
	d3d_device->SetPixelShaderConstantF(10,D3DXVECTOR4(FILTER_SPEED*time,1/5.0f/*((FILTER_SPEED*time*4)+1)*/,/*FILTER_SPEED**/time,/*FILTER_SPEED**/time),1);
	d3d_device->SetPixelShaderConstantF(4,D3DXVECTOR4(1/(FILTER_SPEED*time*4+1),1/(FILTER_SPEED*time*4+1),1/(FILTER_SPEED*time*4+1),1/(FILTER_SPEED*time*4+1)),1);


	
	
	
	IDirect3DSurface9 *surface;
	front_texture->GetSurfaceLevel(0,&surface);
	d3d_device->SetRenderTarget(0,surface);
	surface->Release();

	//d3d_device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_ARGB(128,128,128,128),1.0f,0);
	d3d_device->BeginScene();

	d3d_device->SetTexture(0,back_texture);
	d3d_device->SetTexture(1,back_texture);
	d3d_device->SetTexture(2,back_texture);
	d3d_device->SetTexture(3,back_texture);
	d3d_device->SetTexture(4,back_texture);
	d3d_device->DrawPrimitive(D3DPT_TRIANGLELIST,0,2);
	
	d3d_device->EndScene();
	
	temp_texture = front_texture;
	front_texture = back_texture;
	back_texture = temp_texture;

	//d3d_device->SetRenderTarget(0,render_target);
	//render_target->Release();
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW);

	//D3DXFilterTexture(front_texture,NULL,D3DX_DEFAULT,D3DX_DEFAULT);

	//IDirect3DSurface9 *surface;
	//front_texture->GetSurfaceLevel(0,&surface);
	
	//D3DXSaveSurfaceToFile("out texture.bmp",D3DXIFF_BMP,surface,NULL,NULL);
	//surface->Release();

}
