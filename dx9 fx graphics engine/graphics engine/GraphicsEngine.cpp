#include "StdAfx.h"
#include ".\graphicsengine.h"
#include "Font.h"
#include "TextBlock.h"
#include "IQualityChangedObserver.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;
using namespace std;
using namespace graphicsengine::resources;
using namespace graphicsengine::manager;
using namespace graphicsengine::renderables;

bool GraphicsEngine::done = false;
HANDLE GraphicsEngine::hThread = NULL;

GraphicsEngine::GraphicsEngine(void)
: refCount(0)
, screenWidth(0)
, screenHeight(0)
{
	d3d = NULL;
	d3d_device = NULL;
	if( NULL == ( d3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
	{
	  MessageBox(NULL,"Could not create directx9 device, make sure directx9 is installed","error",MB_OK);
	  exit(0);
	}
	
}

GraphicsEngine::~GraphicsEngine(void)
{
	done = true;
	SetEvent(renderEvent);
	WaitForSingleObject(hThread,INFINITE);

	for(unsigned int i = 0;i < insertQueue.size(); i++)
	{
		delete insertQueue[i];
	}
	insertQueue.clear();
	for(unsigned int i = 0;i < deleteQueue.size(); i++)
	{
		delete deleteQueue[i];
	}
	deleteQueue.clear();

	if(d3d_device != NULL)
	{
		d3d_device->Release();
	}
	if(d3d == NULL) d3d->Release();
	delete resourceManager;
	delete renderManager;
}



void GraphicsEngine::Initialize(WindowSettings* windowSettings)
{
	if(d3d_device != NULL)
	{
		d3d_device->Release();
	}
	d3d_device = NULL;
	

//find matching depth format
	D3DFORMAT depth_format = D3DFMT_D32;
	D3DDISPLAYMODE d3d_mode;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3d_mode);
	screenWidth = d3d_mode.Width;
	screenHeight = d3d_mode.Height;
	aspectRatio = (float)screenWidth/screenHeight;
	if(FAILED(d3d->CheckDeviceType(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,d3d_mode.Format,TRUE)))
	{
		MessageBox(NULL,"Display settings not compatible with directx. try swithcing to 32 color for your desktop","error",MB_OK);
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
					MessageBox(NULL,"Could not find a compatible depth buffer format. make sure your desktop is set to 32 bit color.","error",MB_OK);
					d3d->Release();
					d3d = NULL;
					exit(0);
					
				}
				
			}
			
		}
		
	}
	if(FAILED(d3d->CheckDeviceFormat(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,d3d_mode.Format,0,D3DRTYPE_TEXTURE,D3DFMT_A8R8G8B8)))
	{
		MessageBox(NULL,"Device does not support required texture formats. A8R8G8B8 format support","error",MB_OK);
		d3d->Release();
		d3d = NULL;
		exit(0);

	}

	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = d3d_mode.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.hDeviceWindow = windowSettings->hwnd;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = depth_format;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if( FAILED( d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowSettings->hwnd,
                                  D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                  &d3dpp, &d3d_device ) ) )
	{
		MessageBox(NULL,"Could not create a directx9 window, make sure you have the latest drivers","error",MB_OK);
		d3d->Release();
		d3d = NULL;
		exit(0);
	}
	
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW);
    d3d_device->SetRenderState( D3DRS_AMBIENT, 0x00000000 );
	d3d_device->SetRenderState(D3DRS_ALPHABLENDENABLE ,TRUE );
	d3d_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	d3d_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	d3d_device->SetRenderState( D3DRS_ZENABLE, TRUE );
    d3d_device->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3( 0.0f, 0.0f, -1.0f ),
                              &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ),
                              &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) );
	/*if(windowSettings.widescreen) D3DXMatrixPerspectiveFovLH( &matproj, D3DX_PI/4, d3d_mode.Width/(float)d3d_mode.Height, 1.0f, 1000000.0f );
	else*/ D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, d3d_mode.Width/(float)d3d_mode.Height, 1.0f, 1000000.0f );
	D3DXMatrixOrthoLH(&matPara,d3d_mode.Width/(float)d3d_mode.Height,1.0f,1.0f,1000000.0f);

	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE);
	d3d_device->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);

	renderEvent = CreateEvent(NULL,false,false,NULL);
	copyDataEvent = CreateEvent(NULL,false,true,NULL);


	resourceManager = new ResourceManager(d3d_device);
	renderManager = new RenderManager(d3d_device);
	hThread = (HANDLE)_beginthreadex(NULL,0,RenderThread,NULL,0,NULL);

	LARGE_INTEGER temp;
	QueryPerformanceFrequency(&temp);
	timerfreq = 1.0/temp.QuadPart;
	QueryPerformanceCounter(&starttime);
	QueryPerformanceCounter(&endtime);
	time = 0;

}
void graphicsengine::implementation::GraphicsEngine::setBackgroundColor(const float& red,const float& green,const float& blue)
{
	backgroundColor = D3DCOLOR_XRGB((int)(red*255),(int)(green*255),(int)(blue*255));
}

void GraphicsEngine::Commit()
{
	QueryPerformanceCounter(&endtime);
	time = (float)((endtime.QuadPart-starttime.QuadPart)*timerfreq);
	starttime = endtime;

	WaitForSingleObject(copyDataEvent,INFINITE);
	for(unsigned int i = 0;i < insertQueue.size(); i++)
	{
		insertQueue[i]->SetRenderManager(renderManager);
	}
	insertQueue.clear();
	for(unsigned int i = 0;i < deleteQueue.size(); i++)
	{
		delete deleteQueue[i];
	}
	deleteQueue.clear();
	renderManager->CopyData();
	SetEvent(renderEvent);
}

void graphicsengine::implementation::GraphicsEngine::Render(void)
{
	WaitForSingleObject(renderEvent,INFINITE);
	if(done) return;
	D3DXMatrixMultiply(&matViewProj,&matView,&matProj);
	D3DXMatrixMultiply(&matViewPara,&matView,&matPara);

	d3d_device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,backgroundColor,1.0f,0);
	d3d_device->BeginScene();

	renderManager->Render();

	d3d_device->EndScene();
	d3d_device->Present(NULL,NULL,NULL,NULL);

	SetEvent(copyDataEvent);

}

unsigned int _stdcall graphicsengine::implementation::GraphicsEngine::RenderThread(void *dummy)
{
	while(!done)
	{
		((GraphicsEngine*)GraphicsEngine::getInstance())->Render();
		
	}
	return 0;
}

IDirect3DDevice9* graphicsengine::implementation::GraphicsEngine::getD3DDevice(void)
{
	return d3d_device;
}

void GraphicsEngine::LoadData(const std::string& fileName)
{
	resourceManager->LoadData(fileName);
}

ITextBlock* GraphicsEngine::CreateTextBlock(const std::string& prototypeName)
{
	TextBlockPrototype* temp = resourceManager->GetTextBlock(prototypeName);
	TextBlock* result = new TextBlock(temp);
	insertQueue.push_back(result);
	return result;
}

ISprite* GraphicsEngine::CreateSprite(const std::string& prototypeName)
{
	SpritePrototype* temp = resourceManager->GetSprite(prototypeName);
	Sprite* result = new Sprite(temp);
	insertQueue.push_back(result);
	return result;
}
void graphicsengine::implementation::GraphicsEngine::AddToDeleteQueue(IRenderable *renderable)
{
	deleteQueue.push_back((Renderable*)renderable);
}

int graphicsengine::implementation::GraphicsEngine::GetHighestValidQuality(void)
{
	return highestQuality-1;
}

void graphicsengine::implementation::GraphicsEngine::SetQuality(int quality)
{
	if(quality < highestQuality && quality != this->quality)
	{
		this->quality = quality;
		for(unsigned int i=0;i < qualityObservers.size();i++)
		{
			qualityObservers[i]->QualityChanged(this->quality);
		}
	}
}

void graphicsengine::implementation::GraphicsEngine::MarkQualityAsInvalid(int quality)
{
	if(quality < highestQuality)
		highestQuality = quality;
}

void graphicsengine::implementation::GraphicsEngine::RegisterQualityChangeObserver(IQualityChangedObserver* observer)
{
	qualityObservers.push_back(observer);
}
