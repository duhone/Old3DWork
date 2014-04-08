#include "StdAfx.h"
#include "Renderable.h"
#include "IGraphicsEngine.h"
#include "GraphicsEngine.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace graphicsengine::manager;
using namespace graphicsengine::implementation;

unsigned long Renderable::nextId = 1;

Renderable::Renderable()
{
	this->d3d_device = ((GraphicsEngine*)IGraphicsEngine::getInstance())->getD3DDevice(); 
	id = nextId;
	nextId++;
}

Renderable::~Renderable(void)
{
}





