// vertex phong.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "object_sphere.h"
#include "object_light.h"
#include<vector>
using namespace std;

	LPDIRECT3D8             pd3d; // Used to create the D3DDevice
	LPDIRECT3DDEVICE8       d3ddevice; // Our rendering device
//object *sphere1;
vector<object*> objects;
object* light;

DWORD basic_shader;
DWORD phong_shader;
DWORD basic_pixel;
DWORD spec_pixel;
D3DXMATRIX matView, matProj;
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


void StartFrame()
{
 d3ddevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
 d3ddevice->BeginScene();



  
}

void EndFrame()
{
	d3ddevice->EndScene();


	d3ddevice->Present( NULL, NULL, NULL, NULL );

}

void Render()
{
	float light_pos[3];
	light->GetPosition(light_pos[0],light_pos[1],light_pos[2]);
	for(int count = 0;count < objects.size();count++)
	 {
		objects[count]->SetLightPos(light_pos); 
		objects[count]->render();
	 }
	//sphere1->render();
}

void CreateShaders()
{
DWORD dwDecl[] =
{
    D3DVSD_STREAM(0),
    D3DVSD_REG(D3DVSDE_POSITION,  D3DVSDT_FLOAT3),
//    D3DVSD_REG( D3DVSDE_NORMAL, D3DVSDT_FLOAT3 ),
  D3DVSD_END()
};
LPD3DXBUFFER pCode;
D3DXAssembleShaderFromFile("basic shader.txt"/*basic,strlen(basic)*/,0,NULL,&pCode,NULL);
d3ddevice->CreateVertexShader( dwDecl, (DWORD*)pCode->GetBufferPointer(), &basic_shader, D3DUSAGE_SOFTWAREPROCESSING );

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
D3DXAssembleShaderFromFile("diffuse specular bump map.txt"/*phong,strlen(phong)*/,0,NULL,&pCode2,NULL);
d3ddevice->CreateVertexShader( dwDeclp, (DWORD*)pCode2->GetBufferPointer(), &phong_shader, D3DUSAGE_SOFTWAREPROCESSING );

LPD3DXBUFFER pCode3;
D3DXAssembleShaderFromFile("basic pixel.txt",0,NULL,&pCode3,NULL);
d3ddevice->CreatePixelShader( (DWORD*)pCode3->GetBufferPointer(), &basic_pixel);

LPD3DXBUFFER pCode4;
D3DXAssembleShaderFromFile("diffuse specular bump pixel.txt",0,NULL,&pCode4,NULL);
d3ddevice->CreatePixelShader( (DWORD*)pCode4->GetBufferPointer(), &spec_pixel);

};

void CreateObjects()
{
	object_sphere *spheret;
	
	spheret = new object_sphere();
	spheret->SetCenterPosition(-5,3,0);
	spheret->SetColor(0.7701f,0.6792f,0.2627f,1);
	spheret->SetMaterial(0.25f,0.75f);
	spheret->SetSpecPower(12);
	spheret->LoadTexture("gold bump map.png");
	objects.push_back(spheret);
	
	spheret = new object_sphere();
	spheret->SetCenterPosition(-5,-3,0);
	spheret->SetColor(0,1,0,1);
	spheret->SetMaterial(0.9f,0.1f);
	spheret->SetSpecPower(2);
	spheret->LoadTexture("green bump map.png");
	objects.push_back(spheret);

	spheret = new object_sphere();
	spheret->SetCenterPosition(5,3,0);
	spheret->SetColor(0,0,1,1);
	spheret->SetMaterial(0.7f,0.3f);
	spheret->SetSpecPower(5);
	spheret->LoadTexture("blue bump map.png");
	objects.push_back(spheret);

	spheret = new object_sphere();
	spheret->SetCenterPosition(5,-3,0);
	spheret->SetColor(1,0,0,1);
	spheret->SetMaterial(0.3f,0.7f);
	spheret->SetSpecPower(10);
	spheret->LoadTexture("red bump map.png");
	objects.push_back(spheret);

	object_light *spherel;

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
 // Turn off culling, so we see the front and back of the triangle
    d3ddevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    d3ddevice->SetRenderState( D3DRS_AMBIENT, 0x00000000 );
	d3ddevice->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE );
	d3ddevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3ddevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3ddevice->SetTextureStageState(0,D3DTSS_MAGFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState(0,D3DTSS_MINFILTER,D3DTEXF_LINEAR);
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_SELECTARG2);
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
	d3ddevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

 
	d3ddevice->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3ddevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
 	
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixLookAtLH( &matView, &D3DXVECTOR3( 0.0f, 0.0f,-15.0f ),
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
 	// TODO: Place code here.
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
	hwnd = CreateWindowEx(0/*WS_EX_TOPMOST*/,appname,NULL,WS_VISIBLE | WS_BORDER | WS_SYSMENU,0,0,800,600,NULL,NULL,hInstance,NULL);
	ShowWindow(hwnd,SW_SHOW);
	SetFocus(hwnd);


	if(NULL == (pd3d = Direct3DCreate8( D3D_SDK_VERSION ))) 
	{
		MessageBox(hwnd,"Failed to create D3D object",ERROR,MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);
		//PostQuitMessage(0);
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp; 
	D3DDISPLAYMODE d3ddm;
    /*d3ddm.Width = 800;
	d3ddm.Height = 600;
	d3ddm.RefreshRate = 0;
	d3ddm.Format = D3DFMT_A8R8G8B8;
	*/pd3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	/*d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.Windowed   = FALSE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
    d3dpp.hDeviceWindow = NULL;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER ;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; 
	d3dpp.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	*/d3dpp.Windowed   = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	if(FAILED(pd3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                  D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                  &d3dpp, &d3ddevice )))
	{
		MessageBox(hwnd,"Failed to Initialize D3D object",ERROR,MB_ICONERROR | MB_OK | MB_SYSTEMMODAL);
		//PostQuitMessage(0);
		return false;
	}


  setup();
   


	SetTimer(hwnd,1,20,NULL);
	//ShowCursor(false);
	while(!done)
	{
		while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//if(msg.message == WM_QUIT) break;
		StartFrame();
		Render();
		EndFrame();
	}
	KillTimer(hwnd,1);
	shutdown();
	if( d3ddevice != NULL)
        d3ddevice->Release();
    if( pd3d != NULL)
        pd3d->Release();
	//ShowCursor(true);

	return 0;
}



