#include "StdAfx.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "Sprite.h"
#include "IGraphicsEngine.h"
#include "GraphicsEngine.h"
#include "FrameSet.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace graphicsengine::renderables;
using namespace graphicsengine::renderers;
using namespace graphicsengine::implementation;
using namespace std;
using namespace stdext;

SpriteRenderer::SpriteRenderer(void) : IRenderer(IRenderer::SPRITE)
{
	IDirect3DDevice9* d3d_device = ((GraphicsEngine*)IGraphicsEngine::getInstance())->getD3DDevice();
	SpriteVertex spriteVertexs[4];

	spriteVertexs[0].x = -0.5f;
	spriteVertexs[0].y = -0.5f;
	spriteVertexs[0].z = 0;

	spriteVertexs[3].x = -0.5f;
	spriteVertexs[3].y = 0.5f;
	spriteVertexs[3].z = 0;

	spriteVertexs[2].x = 0.5f;
	spriteVertexs[2].y = 0.5f;
	spriteVertexs[2].z = 0;

	spriteVertexs[1].x = 0.5f;
	spriteVertexs[1].y = -0.5f;
	spriteVertexs[1].z = 0;

	SpriteVertex* tempv;
	d3d_device->CreateVertexBuffer(4 * sizeof(SpriteVertex),D3DUSAGE_WRITEONLY,0,D3DPOOL_DEFAULT,&sprite_vertex_buffer,NULL);
	sprite_vertex_buffer->Lock(0,0,(void**)&tempv,0/*D3DLOCK_DISCARD*/);
	memcpy(tempv,spriteVertexs,4*sizeof(SpriteVertex));
	sprite_vertex_buffer->Unlock();


	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};

	d3d_device->CreateVertexDeclaration(decl,&sprite_vertex_decl);
}

SpriteRenderer::~SpriteRenderer(void)
{
	sprite_vertex_buffer->Release();
	sprite_vertex_decl->Release();
}

void SpriteRenderer::AddRenderable(Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
{
	Sprite* sprite = dynamic_cast<Sprite*>(renderable);
	renderList.AddRenderable(renderable->GetEffect(),sprite,plan,effect);
}

void SpriteRenderer::RemoveRenderable(Renderable* renderable)
{
	Sprite* sprite = dynamic_cast<Sprite*>(renderable);
	renderList.RemoveRenderable(renderable->GetEffect(),sprite);
}

void SpriteRenderer::Render()
{
	IDirect3DDevice9* d3d_device = ((GraphicsEngine*)IGraphicsEngine::getInstance())->getD3DDevice();
	d3d_device->SetStreamSource( 0, sprite_vertex_buffer, 0, sizeof(SpriteVertex) );
	d3d_device->SetVertexDeclaration(sprite_vertex_decl);
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);

	renderList.Render();
	d3d_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW);
}

bool SpriteRenderer::Empty()
{
	return renderList.Empty();
}

void SpriteRenderer::CopyNewValues()
{	
	renderList.CopyNewValues();
}