#include "StdAfx.h"
#include "EffectRenderer.h"
#include "Effect.h"
#include "Texture.h"
#include "Sprite.h"
#include "ObjectExecutionPlan.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace graphicsengine::renderers;
using namespace graphicsengine::resources;

EffectRenderer::EffectRenderer(Effect* effect)
{
	this->effect = effect;
}

EffectRenderer::~EffectRenderer(void)
{
}

void EffectRenderer::AddRenderable(Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
{
	ObjectExecutionPlan* theplan = new ObjectExecutionPlan();
	renderList.AddRenderable(dynamic_cast<Sprite*>(renderable)->GetCurrentTexture(),renderable,theplan,this->effect);
}

void EffectRenderer::RemoveRenderable(Renderable* renderable)
{
	renderList.RemoveRenderable(dynamic_cast<Sprite*>(renderable)->GetCurrentTexture(),renderable);
}

void EffectRenderer::Render()
{
	ID3DXEffect* effect = this->effect->GetEffect();

	unsigned int passes;
	effect->Begin(&passes,0);
	for(int i =0;i < passes;i++)
	{
		effect->BeginPass(i);
		renderList.Render();
		
		effect->EndPass();
	}
	effect->End();
}

bool EffectRenderer::Empty()
{
	return renderList.Empty();
}
void EffectRenderer::CopyNewValues()
{	
	renderList.CopyNewValues();
}