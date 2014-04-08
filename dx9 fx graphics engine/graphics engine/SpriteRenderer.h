#pragma once

#include "IRenderer.h"
#include "RenderList.h"
#include "EffectRenderer.h"

namespace graphicsengine
{
	namespace resources
	{
		class Texture;
		class Effect;
	}
	namespace renderables
	{
		class Sprite;
	}
	namespace renderers
	{
		struct SpriteVertex
		{
			float x,y,z;
		};

		class SpriteRenderer : public IRenderer
		{
		private:
			IDirect3DVertexBuffer9* sprite_vertex_buffer;
			IDirect3DVertexDeclaration9* sprite_vertex_decl;
			RendererList<EffectRenderer,graphicsengine::resources::Effect,graphicsengine::renderables::Sprite> renderList;
		public:
			SpriteRenderer(void);
		public:
			virtual ~SpriteRenderer(void);
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect);
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			virtual void Render();
			virtual bool Empty();
			virtual void CopyNewValues();
		};
	}
}
