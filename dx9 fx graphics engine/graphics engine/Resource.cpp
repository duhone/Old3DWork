#include "StdAfx.h"
#include "Resource.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace std;

unsigned long Resource::nextId = 1;

graphicsengine::resources::Resource::Resource(IDirect3DDevice9* d3d_device)
{
	this->d3d_device = d3d_device;
	refCount = 0;
	id = nextId;
	nextId++;
}

graphicsengine::resources::Resource::~Resource(void)
{
	
}


void graphicsengine::resources::Resource::AddRef(void)
{
	if(refCount == 0) BuildResource();
	refCount++;
	
}

void graphicsengine::resources::Resource::SubRef(void)
{
	if(refCount == 0) return;
	refCount--;
	if(refCount == 0) FreeResource();
}


