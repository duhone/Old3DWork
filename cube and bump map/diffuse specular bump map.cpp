// vertex phong.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "object_sphere.h"
#include "object_light.h"
#include "object_plane.h"
#include<stdlib.h>

#include<vector>
using namespace std;

LPDIRECT3D8             pd3d; // Used to create the D3DDevice
LPDIRECT3DDEVICE8       d3ddevice; // Our rendering device
vector<object*> objects;
object* light;
float plane_color[3];

//shaders
DWORD basic_shader;
DWORD phong_shader;
DWORD cube_shader;
DWORD basic_pixel;
DWORD spec_pixel;
DWORD cube_pixel;

D3DXMATRIX matView, matProj;
D3DXVECTOR3 view_pos;
bool done = false;

LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int count;
 switch(message)
 {
 
 case WM_TIMER:
	 for(count = 0;count < objects.size();count++)
	 {
		 objects[count]->IncAngle();
	 }
	 int temp;
	 temp = rand() % 6;
	 switch(temp)
	 {
	 case 0:
		 plane_color[0] -= .02f;
		 if(plane_color[0] < 0) plane_color[0] = 0;
		 break;
	 case 1:
		 plane_color[0] += .02f;
		 if(plane_color[0] > 1) plane_color[0] = 1;
		 break;
	 case 2:
		 plane_color[1] -= .02f;
		 if(plane_color[1] < 0) plane_color[1] = 0;
		 break;
	 case 3:
		 plane_color[1] += .02f;
		 if(plane_color[1] > 1) plane_color[1] = 1;
		 break;
	 case 4:
		 plane_color[2] -= .02f;
		 if(plane_color[2] < 0) plane_color[2] = 0;
		 break;
	 case 5:
		 plane_color[2] += .02f;
		 if(plane_color[2] > 1) plane_color[2] = 1;
		 break;
	 };
	objects[objects.size()-2]->SetColor(plane_color[0],plane_color[1],plane_color[2],1);
	 return 0;
  case WM_KEYDOWN:
	  done = true;	
	  PostQuitMessage(0);
	 return 0;
	 
 case WM_DESTROY:
	 done = true;
	 return 0;
 case WM_QUIT:
	 done = true;
	 return 0;


 }




 return DefWindowProc(hwnd,message,wParam,lParam);
}






void Render()
{
	float light_pos[3];
	light->GetPosition(light_pos[0],light_pos[1],light_pos[2]);

	for(int count = 0;count < objects.size()-1;count++)
	 {
		objects[count]->SetLightPos(light_pos); 
		objects[count]->SetShaderNumber(0);
	 }

	
//render cube maps
	LPDIRECT3DCUBETEXTURE8 cube_texture;
	IDirect3DSurface8* depth;
	d3ddevice->GetDepthStencilSurface(&depth);
	LPDIRECT3DSURFACE8 pBackBuffer;
    d3ddevice->GetRenderTarget( &pBackBuffer );
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/2, 1.0f, 0.5f, 100.0f );

	for(count = 0;count < objects.size()-2;count++)
	{
		LPDIRECT3DSURFACE8 pFace;
		cube_texture = objects[count]->GetCubeTexture();
		float obj_pos[3];
		objects[count]->GetPosition(obj_pos[0],obj_pos[1],obj_pos[2]);
		D3DXVECTOR3 vEnvEyePt = D3DXVECTOR3( obj_pos[0], obj_pos[1], obj_pos[2] );
		D3DXVECTOR3 vLookatPt, vUpVec;
		view_pos = vEnvEyePt;
		for(int count2 = 0;count2 < 6;count2++)
		{
		
			switch( count2)
			{
				case D3DCUBEMAP_FACE_POSITIVE_X:
					vLookatPt = D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_X:
					vLookatPt = D3DXVECTOR3(-1.0f, 0.0f, 0.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
					break;
				case D3DCUBEMAP_FACE_POSITIVE_Y:
					vLookatPt = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 0.0f,-1.0f );
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_Y:
					vLookatPt = D3DXVECTOR3( 0.0f,-1.0f, 0.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
					break;
				case D3DCUBEMAP_FACE_POSITIVE_Z:
					vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
					break;
				case D3DCUBEMAP_FACE_NEGATIVE_Z:
					vLookatPt = D3DXVECTOR3( 0.0f, 0.0f,-1.0f ) + vEnvEyePt;
					vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
					break;
			}

			D3DXMatrixLookAtLH( &matView, &vEnvEyePt, &vLookatPt, &vUpVec );
			cube_texture->GetCubeMapSurface((D3DCUBEMAP_FACES)count2, 0, &pFace);
			d3ddevice->SetRenderTarget ( pFace , depth );
			pFace->Release();	
			d3ddevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
			d3ddevice->BeginScene();
		
			for(int count3 = 0;count3 < objects.size();count3++)
			{
				if((count3 != count) && (count3 != objects.size()-2)) objects[count3]->Cull(&(vLookatPt - vEnvEyePt),&view_pos);
			}
			for(count3 = 0;count3 < objects.size();count3++)
			{
				if(count3 != count) objects[count3]->render();
			}
			d3ddevice->EndScene();

		}
	}

//reset to main view and render target	
	d3ddevice->SetRenderTarget ( pBackBuffer , depth );
	pBackBuffer->Release();
	depth->Release();
	for(count = 0;count < objects.size();count++)
	 {
		objects[count]->SetShaderNumber(1);
	 }
	view_pos = D3DXVECTOR3(0,0,-15);

	D3DXMatrixLookAtLH( &matView, &view_pos,
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.333f, 1.0f, 100.0f );
	
	d3ddevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	d3ddevice->BeginScene();
	
	for(count = 0;count < objects.size();count++)
	 {
		objects[count]->render();
	 }
	d3ddevice->EndScene();
	d3ddevice->Present( NULL, NULL, NULL, NULL );

}

void CreateShaders()
{
LPD3DXBUFFER errors = NULL;
char *errorst;


DWORD dwDecl[] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(D3DVSDE_POSITION,  D3DVSDT_FLOAT3),
  D3DVSD_END()
};
LPD3DXBUFFER pCode;
D3DXAssembleShaderFromFile("basic shader.txt",0,NULL,&pCode,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}

if(d3ddevice->CreateVertexShader( dwDecl, (DWORD*)pCode->GetBufferPointer(), &basic_shader, 0 ) != D3D_OK)
	MessageBox(NULL,"Failed to create basic vertex shader","error",MB_OK);


DWORD dwDeclp[] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(0,  D3DVSDT_FLOAT3),
    D3DVSD_REG( 1, D3DVSDT_FLOAT3 ),
	D3DVSD_REG( 2, D3DVSDT_FLOAT2 ),
	D3DVSD_REG( 3, D3DVSDT_FLOAT3 ),
	D3DVSD_REG( 4, D3DVSDT_FLOAT3 ),
    D3DVSD_END()
};

LPD3DXBUFFER pCode2;
D3DXAssembleShaderFromFile("diffuse specular bump map.txt",0,NULL,&pCode2,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}
if(d3ddevice->CreateVertexShader( dwDeclp, (DWORD*)pCode2->GetBufferPointer(), &phong_shader, 0 ) != D3D_OK)
	MessageBox(NULL,"Failed to create phong vertex shader","error",MB_OK);

LPD3DXBUFFER pCode3;
D3DXAssembleShaderFromFile("cube and bump map.txt",0,NULL,&pCode3,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}
if(d3ddevice->CreateVertexShader( dwDeclp, (DWORD*)pCode3->GetBufferPointer(), &cube_shader, 0 ) != D3D_OK)
	MessageBox(NULL,"Failed to create cube and bumpmap vertex shader","error",MB_OK);


LPD3DXBUFFER pCode4;
D3DXAssembleShaderFromFile("basic pixel.txt",0,NULL,&pCode4,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}
if(d3ddevice->CreatePixelShader( (DWORD*)pCode4->GetBufferPointer(), &basic_pixel) != D3D_OK)
	MessageBox(NULL,"Failed to create basic pixel shader","error",MB_OK);

LPD3DXBUFFER pCode5;
D3DXAssembleShaderFromFile("diffuse specular bump pixel.txt",0,NULL,&pCode5,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}
if(d3ddevice->CreatePixelShader( (DWORD*)pCode5->GetBufferPointer(), &spec_pixel) != D3D_OK)
	MessageBox(NULL,"Failed to create phong pixel shader","error",MB_OK);

LPD3DXBUFFER pCode6;
D3DXAssembleShaderFromFile("cube and bump pixel.txt",0,NULL,&pCode6,&errors);
if(errors != NULL)
{
	errorst = (char*)errors->GetBufferPointer();
	MessageBox(NULL,errorst,"error",MB_OK);
}
if(d3ddevice->CreatePixelShader( (DWORD*)pCode6->GetBufferPointer(), &cube_pixel) != D3D_OK)
	MessageBox(NULL,"Failed to create cubemap and bumpmap pixel shader","error",MB_OK);


};

void CreateObjects()
{
	object_sphere *spheret;
	object_plane *spherep;
//gold sphere	
	spheret = new object_sphere();
	spheret->SetCenterPosition(-5,3,0);
	spheret->SetColor(0.9f,0.85f,0.2f,1);
	spheret->SetMaterial(0.3f,1.0f);
	spheret->SetSpecPower(12);
	spheret->LoadTexture("gold bump map.png");
	objects.push_back(spheret);
//green sphere	
	spheret = new object_sphere();
	spheret->SetCenterPosition(-5,-3,0);
	spheret->SetColor(0,1,0,1);
	spheret->SetMaterial(0.9f,0.2f);
	spheret->SetSpecPower(2);
	spheret->LoadTexture("green bump map.png");
	objects.push_back(spheret);
//blue sphere
	spheret = new object_sphere();
	spheret->SetCenterPosition(5,3,0);
	spheret->SetColor(0,0,1,1);
	spheret->SetMaterial(0.7f,0.5f);
	spheret->SetSpecPower(5);
	spheret->LoadTexture("blue bump map.png");
	objects.push_back(spheret);
//red sphere
	spheret = new object_sphere();
	spheret->SetCenterPosition(5,-3,0);
	spheret->SetColor(1,0,0,1);
	spheret->SetMaterial(0.4f,0.8f);
	spheret->SetSpecPower(10);
	spheret->LoadTexture("red bump map.png");
	objects.push_back(spheret);
//ground plane
	spherep = new object_plane();
	spherep->SetCenterPosition(0,-4,0);
	spherep->SetRotationRadius(0);
	plane_color[0] = 0.6f;
	plane_color[1] = 0.6f;
	plane_color[2] = 0.6f;
	spherep->SetColor(.6f,.6f,.6f,1);
	spherep->SetRotate(false);
	objects.push_back(spherep);

	object_light *spherel;
//light sphere
	spherel = new object_light();
	spherel->SetCenterPosition(0,0,0);
	spherel->SetColor(1,1,1,1);
	spherel->SetMaterial(1.0f,1.0f);
	spherel->SetRotationRadius(6);
	objects.push_back(spherel);
	light = spherel;

}

void setup()
{
    d3ddevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);

    d3ddevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );
	d3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE );
	d3ddevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3ddevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3ddevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(1,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(1,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(2,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(2,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(3,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(3,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(4,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(4,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(5,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(5,D3DTSS_MINFILTER,D3DTEXF_LINEAR);

 
	d3ddevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3ddevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
 	
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	view_pos = D3DXVECTOR3(0,0,-15);
	D3DXMatrixLookAtLH( &matView, &view_pos,
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.333f, 1.0f, 100.0f );

	CreateShaders();
    CreateObjects();
}

void shutdown()
{
	 object* temp;
	 for(int count = 0;count < objects.size();count++)
	 {
		 temp = objects[count];
		 delete temp;
	 }
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
//create window
	HWND hwnd;
	MSG msg;
	char appname[6];
	strcpy(appname,"test1");
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = appname;
	RegisterClass(&wc);
	hwnd = CreateWindowEx(0,appname,NULL,WS_VISIBLE | WS_BORDER | WS_SYSMENU,0,0,800,600,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,SW_SHOW);
	SetFocus(hwnd);


	if(NULL == (pd3d = Direct3DCreate8( D3D_SDK_VERSION ))) 
	{
		MessageBox(hwnd,"Failed to create D3D object",ERROR,MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);
		return false;
	}

	D3DDEVTYPE devtype = D3DDEVTYPE_HAL;

//check device caps
	D3DCAPS8 caps;
	pd3d->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&caps);
	int pixmaj = caps.PixelShaderVersion & 0x0000FF00;
	int pixmin = caps.PixelShaderVersion & 0x000000FF;
	if((pixmaj >= 256))
	{
		if(pixmin < 4)
		{
			MessageBox(NULL,
				"You video card does not support pixel shader version 1.4. Switching to refernece drivers"
				,"ERROR",MB_OK);
				devtype = D3DDEVTYPE_REF;

		}
	}
	else
	{
		MessageBox(NULL,
				"You video card does not support pixel shaders. Switching to refernece drivers"
				,"ERROR",MB_OK);
			devtype = D3DDEVTYPE_REF;


	}



//create d3d device	
	D3DPRESENT_PARAMETERS d3dpp; 
	D3DDISPLAYMODE d3ddm;
    pd3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed   = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	if(FAILED(pd3d->CreateDevice( D3DADAPTER_DEFAULT, devtype, hwnd,
                                  D3DCREATE_PUREDEVICE | D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &d3ddevice )))
	{
		MessageBox(hwnd,"Failed to Initialize D3D object",ERROR,MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);
			return false;
	}


  setup();
   


	SetTimer(hwnd,1,20,NULL);
//main loop
	while(!done)
	{
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Render();
	}
	KillTimer(hwnd,1);
	shutdown();
	if( d3ddevice != NULL)
        d3ddevice->Release();
    if( pd3d != NULL)
        pd3d->Release();

	return 0;
}



