#pragma once

#include "IRenderer.h"
#include "FontRenderer.h"

namespace graphicsengine
{
	namespace resources
	{
		class Font;
	}
	namespace renderables
	{
		class TextBlock;
	}
	namespace renderers
	{
		class TextBlockRenderer : public IRenderer
		{
		private:	
			RendererList<FontRenderer,graphicsengine::resources::Font,graphicsengine::renderables::TextBlock> renderList;
		public:
			TextBlockRenderer(void);
		public:
			virtual ~TextBlockRenderer(void);
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect);
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			virtual void Render();
			virtual bool Empty();
			virtual void CopyNewValues();
		};
	}
}
