#include "StdAfx.h"
#include "SpritePrototype.h"
#include "FrameSetPrototype.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace std;

SpritePrototype::SpritePrototype(IDirect3DDevice9* d3d_device) :
Resource(d3d_device)
{
}

SpritePrototype::~SpritePrototype(void)
{
	if(RefCount() > 0) FreeResource();
}

void SpritePrototype::BuildResource()
{
	ResetFile();
	alpha = GetBool();
	int framesetcount = GetInt();
	for(int i = 0;i< framesetcount;i++)
	{
		string* name = GetString();
		string* texture = GetString();
		string* effect = GetString();
		int framewidth = GetInt();
		float fps = GetFloat();
		FrameSetPrototype *frameset = new FrameSetPrototype(name,texture,effect,framewidth,fps);
		framesets.push_back(frameset);
		delete name;
		delete texture;
	}
}

void SpritePrototype::FreeResource()
{
	for(unsigned int i = 0;i < framesets.size();i++)
	{
		delete framesets[i];
	}
	framesets.clear();
}

void SpritePrototype::Release()
{
	this->SubRef();
}