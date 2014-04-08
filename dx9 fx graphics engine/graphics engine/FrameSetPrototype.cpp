#include "StdAfx.h"
#include "FrameSetPrototype.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;

FrameSetPrototype::FrameSetPrototype(std::string* name,std::string* texture,std::string* effect,int framewidth,float fps)
{
	this->name = *name;
	this->texture = *texture;
	this->effect = *effect;
	this->framewidth = framewidth;
	this->fps = fps;
}

FrameSetPrototype::~FrameSetPrototype(void)
{
}
