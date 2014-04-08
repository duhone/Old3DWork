#pragma once
#include"Renderable.h"
#include "ITextblock.h"

namespace graphicsengine
{
	namespace resources
	{
		class TextBlockPrototype;
		class Effect;
		class Font;
	}

	namespace renderables
	{
		class TextBlock :
			public ITextBlock , public graphicsengine::renderables::Renderable
		{
		private:
			graphicsengine::resources::Font* newfont;
			graphicsengine::resources::Font* font;
			D3DCOLOR newcolor;
			D3DCOLOR color;
			std::string newtext;
			std::string text;
			RECT bounds;
			float xlocation;
			float ylocation;
			int anchor;
			int newanchor;
			graphicsengine::resources::TextBlockPrototype* prototype;
			void SwitchFont();
			void BuildBoundsRect();
			graphicsengine::resources::Effect* effect;
		public:
			TextBlock(graphicsengine::resources::TextBlockPrototype *textBlockPrototype);
		public:
			virtual ~TextBlock(void);
			virtual void SetFont(graphicsengine::resources::Font* font);
			virtual graphicsengine::resources::Font* GetFont();
			virtual void SetText(const std::string& text);
			virtual void SetLocation(const float& x,const float& y);
			virtual void SetColor(const float& r,const float& g,const float& b,const float& a);
			virtual void CopyNewValues();
			D3DCOLOR GetColor() {return color;}
			std::string GetText() {return text;}
			virtual void SetAnchor(int anchor);
			virtual graphicsengine::renderers::IRenderer::RendererType GetRenderer();
			
			virtual const graphicsengine::resources::Resource* const GetResource(void) const;
			virtual void BuildExecutionPlan(graphicsengine::resources::Effect* effect) {};
		public:
			virtual void AssignToRenderManager(void);
		public:
			RECT* GetBounds(void);
		public:

			virtual graphicsengine::resources::Effect* GetEffect(void);
			virtual void Render();
		};
	}
}
