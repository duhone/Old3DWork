// HPTGraphicsEngineInternal.cpp: implementation of the HPTGraphicsEngineInternal class.
//
//////////////////////////////////////////////////////////////////////

#include "GraphicsEngine.h"
#include"Object.h"
#include<vector>
#include "zlib.h"

extern GraphicsEngine *gengine;
extern HWND hwnd;
extern HINSTANCE hinstance;

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern char path[255];

extern char *hptstrcat(char *x,char *y);

GraphicsEngine::GraphicsEngine()
{
	sphere_cuts = 30;
	
	d3d = NULL;
	d3d_device = NULL;

	if( NULL == ( d3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	  MessageBox(NULL,"Could not create directx9 device, make sure directx9 is installed","error",MB_OK);

//find matching depth format
	D3DFORMAT depth_format = D3DFMT_D32;
	D3DDISPLAYMODE d3d_mode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3d_mode);
	
	if(FAILED(d3d->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,true)))
	{
		MessageBox(NULL,"Display settings not compatible with directx. try swithcing to 32 or 16 bit color for your desktop","error",MB_OK);
		d3d->Release();
		d3d = NULL;
		exit(0);

	}
	
	
	if(FAILED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,depth_format)))
	{
		depth_format = D3DFMT_D24X8;
		if(FAILED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,depth_format)))
		{
			depth_format = D3DFMT_D24S8;
			if(FAILED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,depth_format)))
			{
				depth_format = D3DFMT_D24FS8;
				if(FAILED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,depth_format)))
				{
					depth_format = D3DFMT_D16;
					if(FAILED(d3d->CheckDepthStencilMatch(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,depth_format)))
					{
						MessageBox(NULL,"Could not find a compatible depth buffer format","error",MB_OK);
						d3d->Release();
						d3d = NULL;
						exit(0);
					
					}
					
				}
				
			}
			
		}
		
	}

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3d_mode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = depth_format;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;


	if( FAILED( d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &d3d_device ) ) )
	{
		MessageBox(NULL,"Could not create a directx9 window, make sure you have the latest drivers","error",MB_OK);
		d3d->Release();
		d3d = NULL;
		exit(0);
	}
	CreateSphereVertexBuffer();
	LoadShaders();

	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW);
	d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE );
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
	D3DXMatrixLookAtLH(&matview, &D3DXVECTOR3( 0.0f, 0.0f, -1.0f ),
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH( &matproj, D3DX_PI/4, 1.33333333f, 1.0f, 1000000.0f );
	d3d_device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_POINT );
	d3d_device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
	D3DXCreateFont(d3d_device,10,10,700,1,false,ANSI_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Arial",&d3dfont);
}

GraphicsEngine::~GraphicsEngine()
{
	d3d_device->SetVertexShader(NULL);
	d3d_device->SetPixelShader(NULL);

	if(star_vertex_shader_heat != NULL) star_vertex_shader_heat->Release(); 
	if(star_pixel_shader_heat != NULL) star_pixel_shader_heat->Release(); 
	if(planck_vertex_shader != NULL) planck_vertex_shader->Release(); 
	if(planck_pixel_shader != NULL) planck_pixel_shader->Release(); 
	if(sphere_index_buffer != NULL) sphere_index_buffer->Release();
	d3dfont->Release();

	if(d3d_device != NULL)
		d3d_device->Release();
	if(d3d != NULL)
		d3d->Release();
}

void GraphicsEngine::Release()
{
	delete this;

}

Object* GraphicsEngine::CreateObject()
{
	return new Object();;
}

void GraphicsEngine::BeginFrame()
{
	d3d_device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0,1.0f,0);
	d3d_device->BeginScene();
}

void GraphicsEngine::EndFrame()
{
	d3d_device->EndScene();
	d3d_device->Present(NULL,NULL,NULL,NULL);
}


GraphicsEngine& GraphicsEngine::operator<<(char *arg)
{
	d3d_device->SetPixelShader(NULL);
	d3d_device->SetVertexShader(NULL);
	RECT tempr;
	tempr.left = text_positionx;
	tempr.top = text_positiony;
	tempr.right = tempr.left + 1;
	tempr.bottom = tempr.top + 1;
	d3dfont->DrawText(NULL,arg,-1,&tempr,DT_LEFT | DT_NOCLIP | DT_SINGLELINE,D3DXCOLOR(255,255,255,255));
	return *this;
}

GraphicsEngine& GraphicsEngine::operator<<(int arg)
{
	char temp[30];
	sprintf(temp,"%d",arg);
	int pos = 0;
	for(unsigned int count = 0;count < strlen(temp);count++)
	{
		if(temp[count] != '0') pos = count;
	}
	temp[pos+1] = 0;
	(*this) << temp;

	return *this;	
}

GraphicsEngine& GraphicsEngine::operator<<(unsigned int arg)
{
	char temp[30];
	sprintf(temp,"%d",arg);
	int pos = 0;
	for(unsigned int count = 0;count < strlen(temp);count++)
	{
		if(temp[count] != '0') pos = count;
	}
	temp[pos+1] = 0;
	(*this) << temp;

	return *this;	
}

GraphicsEngine& GraphicsEngine::operator<<(double arg)
{
		char temp[30];
	sprintf(temp,"%f",arg);
	int pos = 0;
	for(unsigned int count = 0;count < strlen(temp);count++)
	{
		if(temp[count] != '0') pos = count;
	}
	temp[pos+1] = 0;
	(*this) << temp;

	return *this;

}


GraphicsEngine& GraphicsEngine::Position(int x,int y)
{
	text_positionx = x;
	text_positiony = y;

	return *this;

}



void GraphicsEngine::CreateSphereVertexBuffer()
{
	vector<StarVertex> buffer;
	vector<unsigned short> ibuffer;

	double cd,ct,sd,st;
	double am = PI/sphere_cuts;
	double pinv = 1/PI;
	double p2inv = 1/(2*PI);
	bool done = false;
	for(double delta = 0;delta <= 2*PI/*+0.1f*/;delta += am)
	{
		cd = cos(delta);
		sd = sin(delta);
		if(fabs((2*PI)-delta) < (am/2))
		{
			delta = 6.2831853071796;
			done = true;
			cd = 1.0;
			sd = 0.0;

		}
		if(delta == 0)
		{
			cd = 1.0;
			sd = 0.0;
		}
		for(double theta = PI;theta >= 0/*-0.1f*/;theta -= am)
		{
			ct = cos(theta);
			st = sin(theta);
			buffer.push_back(StarVertex(st*sd,ct,-st*cd,  //position
				delta*p2inv,(theta)*pinv));  //binormal
			if(theta >= (PI-(am/2))) continue;
			if(delta <= am/2) continue;
			ibuffer.push_back((buffer.size()-1)-1-(sphere_cuts+1));
			ibuffer.push_back((buffer.size()-1));
			ibuffer.push_back((buffer.size()-1)-(sphere_cuts+1));
			ibuffer.push_back((buffer.size()-1)-1-(sphere_cuts+1));
			ibuffer.push_back((buffer.size()-1)-1);
			ibuffer.push_back((buffer.size()-1));

		}
		if(done) delta = 2*PI+1;
	}

	sphere_size = ibuffer.size()/3;
	sphere_v_size = buffer.size();

	StarVertex* tempv;

	d3d_device->CreateVertexBuffer(buffer.size() * sizeof(StarVertex),D3DUSAGE_WRITEONLY,0,D3DPOOL_DEFAULT,&sphere_vertex_buffer,NULL);
	sphere_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	memcpy(tempv,&(buffer[0]),buffer.size()*sizeof(StarVertex));
	sphere_vertex_buffer->Unlock();

	unsigned short* tempi;
	d3d_device->CreateIndexBuffer(sphere_size*6,D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_DEFAULT,&sphere_index_buffer,NULL);
	sphere_index_buffer->Lock(0,0,(void**)(&tempi),0/*D3DLOCK_DISCARD*/);
	memcpy(tempi,&(ibuffer[0]),ibuffer.size()*2);
	sphere_index_buffer->Unlock();


	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};

	d3d_device->CreateVertexDeclaration(decl,&star_vertex_decl);

}




void GraphicsEngine::ChangeGraphicsState(int arg)
{
	switch(arg)
	{
	case 2: //star
		d3d_device->SetVertexShader(star_vertex_shader_heat);
		d3d_device->SetPixelShader(star_pixel_shader_heat);
		d3d_device->SetVertexDeclaration(star_vertex_decl);
		d3d_device->SetStreamSource(0,sphere_vertex_buffer,0,sizeof(StarVertex));
		break;
	case 3: //planks star
		d3d_device->SetVertexShader(planck_vertex_shader);
		d3d_device->SetPixelShader(planck_pixel_shader);
		d3d_device->SetVertexDeclaration(star_vertex_decl);
		d3d_device->SetStreamSource(0,sphere_vertex_buffer,0,sizeof(StarVertex));
		break;
	}
	
}

void GraphicsEngine::LoadShaders()
{
	LPD3DXBUFFER tempvbufer;
	LPD3DXBUFFER emsg;


	if(D3DXAssembleShaderFromFile("planck vertex shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	d3d_device->CreateVertexShader((const unsigned long*)tempvbufer->GetBufferPointer(),&planck_vertex_shader);

	if(D3DXAssembleShaderFromFile("planck pixel shader.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	d3d_device->CreatePixelShader((const unsigned long*)tempvbufer->GetBufferPointer(),&planck_pixel_shader);

	if(D3DXAssembleShaderFromFile("star vertex shader heat.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	d3d_device->CreateVertexShader((const unsigned long*)tempvbufer->GetBufferPointer(),&star_vertex_shader_heat);

	if(D3DXAssembleShaderFromFile("star pixel shader heat.txt",NULL,NULL,0,&tempvbufer,&emsg) != D3D_OK)
	{
		MessageBox(NULL,(const char*)emsg->GetBufferPointer(),"error",MB_OK);
	}
	d3d_device->CreatePixelShader((const unsigned long*)tempvbufer->GetBufferPointer(),&star_pixel_shader_heat);

}
