#pragma once

#include "RenderList.h"

namespace graphicsengine
{
	
	namespace resources
	{
		class Texture;
		class Effect;
	}
	namespace renderables
	{
		class Renderable;
	}
	namespace renderers
	{
		class TextureRenderer
		{
		private:
			graphicsengine::resources::Texture* texture;
			RenderList<graphicsengine::renderables::Renderable> renderList;
		public:
			TextureRenderer(graphicsengine::resources::Texture* texture);
		public:
			virtual ~TextureRenderer(void);
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect);
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			virtual void Render();
			virtual bool Empty();
			virtual void CopyNewValues();
		};
	}
}
