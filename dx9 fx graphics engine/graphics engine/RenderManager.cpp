#include "StdAfx.h"
#include "RenderManager.h"
#include "TextBlockRenderer.h"
#include "SpriteRenderer.h"

using namespace stdext;
using namespace graphicsengine;
using namespace std;
using namespace stdext;
using namespace graphicsengine::manager;
using namespace graphicsengine::resources;
using namespace graphicsengine::renderables;
using namespace graphicsengine::renderers;

RenderManager::RenderManager(IDirect3DDevice9* d3d_device)
{
	this->d3d_device = d3d_device;
	renderers[IRenderer::TEXT_BLOCK] = new TextBlockRenderer();
	renderers[IRenderer::SPRITE] = new SpriteRenderer();
}

RenderManager::~RenderManager(void)
{
	delete renderers[IRenderer::TEXT_BLOCK];
	delete renderers[IRenderer::SPRITE];
}

void RenderManager::AddRenderable(Renderable* renderable)
{
	renderers[renderable->GetRenderer()]->AddRenderable(renderable,NULL,NULL);
}

void RenderManager::RemoveRenderable(Renderable* renderable)
{
	renderers[renderable->GetRenderer()]->RemoveRenderable(renderable);
}


void RenderManager::MoveRenderable(graphicsengine::renderables::Renderable* renderable)
{
	moveList.push_back(renderable);
}

void RenderManager::Render()
{
	for(int i = 0;i < moveList.size();++i)
	{
		renderers[moveList[i]->GetRenderer()]->RemoveRenderable(moveList[i]);
		moveList[i]->ReadyToMove();
		renderers[moveList[i]->GetRenderer()]->AddRenderable(moveList[i],NULL,NULL);
	}

	moveList.clear();

	for(int i =0;i < IRenderer::MAX;i++)
	{
		renderers[i]->Render();
	}
}

void graphicsengine::manager::RenderManager::CopyData(void)
{
	
	for(int i =0;i < IRenderer::MAX;i++)
	{
		renderers[i]->CopyNewValues();
	}
	
}