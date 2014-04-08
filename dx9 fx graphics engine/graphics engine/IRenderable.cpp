#include "StdAfx.h"
#include "IRenderable.h"
#include "GraphicsEngine.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;

IRenderable::IRenderable(void)
{
}

IRenderable::~IRenderable(void)
{
}

void IRenderable::Release()
{
	((GraphicsEngine*)IGraphicsEngine::getInstance())->AddToDeleteQueue(this);
}
