#include "StdAfx.h"
#include ".\font.h"
#include ".\graphicsengine.h"
#include "IGraphicsEngine.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace graphicsengine::implementation;
using namespace std;

graphicsengine::resources::Font::Font(IDirect3DDevice9* d3d_device) :
Resource(d3d_device)
{
	font = NULL;
}

graphicsengine::resources::Font::~Font(void)
{
	if(RefCount() > 0) FreeResource();
}


void graphicsengine::resources::Font::BuildResource()
{
	ResetFile();
	float sizeFactor = ((GraphicsEngine*)IGraphicsEngine::getInstance())->GetScreenHeight()/768.0f;
	int height = int(GetInt()*sizeFactor);
	int width = int(GetInt()*sizeFactor);
	int weight = GetInt();
	bool italic = GetBool();
	string* facename = GetString();
	D3DXCreateFont(d3d_device,height,width,weight,4,italic,ANSI_CHARSET,OUT_DEFAULT_PRECIS,ANTIALIASED_QUALITY,DEFAULT_PITCH | FF_DONTCARE,facename->c_str(),&font);

}

void graphicsengine::resources::Font::FreeResource()
{
	font->Release();
	font = NULL;
}

void graphicsengine::resources::Font::Release()
{
	this->SubRef();
}

