#pragma once
#include "IRenderer.h"
#include "RenderList.h"
#include "TextureRenderer.h"

namespace graphicsengine
{
	
	namespace resources
	{
		class Texture;
		class Effect;
	}
	namespace renderers
	{
		class EffectRenderer
		{
		private:
			graphicsengine::resources::Effect* effect;
			RendererList<TextureRenderer,graphicsengine::resources::Texture,graphicsengine::renderables::Renderable> renderList;
		public:
			EffectRenderer(graphicsengine::resources::Effect* effect);
		public:
			virtual ~EffectRenderer(void);
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect);
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			virtual void Render();
			virtual bool Empty();
			virtual void CopyNewValues();
		};
	}
}