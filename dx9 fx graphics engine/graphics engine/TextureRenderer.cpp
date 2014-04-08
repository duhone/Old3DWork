#include "StdAfx.h"
#include "TextureRenderer.h"
#include "Texture.h"
#include "Sprite.h"
#include "ObjectExecutionPlan.h"
#include "Effect.h"
#include "Semantics.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace graphicsengine::renderers;
using namespace graphicsengine::resources;
using namespace graphicsengine::implementation;

namespace graphicsengine
{
	namespace resources
	{
		class TextureExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			Texture* texture;
		public:
			TextureExecutePlan(Effect* effect,D3DXHANDLE handle,Texture* texture)
			{
				this->effect = effect;
				this->handle = handle;
				this->texture = texture;
			}
			void Execute()
			{
				effect->SetTexture(handle,texture);
			}
		};
	}
}

TextureRenderer::TextureRenderer(Texture* texture)
{
	this->texture = texture;
}

TextureRenderer::~TextureRenderer(void)
{
}

void TextureRenderer::AddRenderable(Renderable* renderable,ObjectExecutionPlan* plan,Effect* effect)
{
	D3DXHANDLE handle = effect->GetHandleForSemantic(Semantics::Texture0);
	if(handle != NULL)
		plan->AddExecute(new TextureExecutePlan(effect,handle,texture));
	renderList.AddRenderable(renderable,plan,effect);
}

void TextureRenderer::RemoveRenderable(Renderable* renderable)
{
	renderList.RemoveRenderable(renderable);
}

void TextureRenderer::Render()
{
	renderList.Render();
}

bool TextureRenderer::Empty()
{
	return renderList.Empty();
}

void TextureRenderer::CopyNewValues()
{	
	renderList.CopyNewValues();
}	