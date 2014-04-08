#pragma once

#include "RenderList.h"

namespace graphicsengine
{
	
	namespace resources
	{
		class Texture;
		class Font;
	}
	namespace renderables
	{
		class Renderable;
	}
	namespace renderers
	{
		class FontRenderer
		{
		private:
			graphicsengine::resources::Font* font;
		private:			
			RenderList<graphicsengine::renderables::Renderable> renderList;
		public:
			FontRenderer(graphicsengine::resources::Font* font);
		public:
			virtual ~FontRenderer(void);
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect);
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			virtual void Render();
			virtual bool Empty();;
			virtual void CopyNewValues();
		};
	}
}
