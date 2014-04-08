#include "StdAfx.h"
#include ".\igraphicsengine.h"
#include "graphicsengine.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;

IGraphicsEngine* IGraphicsEngine::instance = NULL;

IGraphicsEngine::IGraphicsEngine(void)
{
}

IGraphicsEngine::~IGraphicsEngine(void)
{
}


IGraphicsEngine* IGraphicsEngine::getInstance(void)
{
	if(instance==NULL) instance = new GraphicsEngine();
	return instance;
}
void graphicsengine::IGraphicsEngine::Shutdown(void)
{
	delete instance;
}
