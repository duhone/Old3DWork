#pragma once
#include"Font.h"
#include "TextBlock.h"
#include "Sprite.h"
#include "Texture.h"
#include "IRenderer.h"

namespace graphicsengine
{
	namespace renderers
	{
		class TextBlockRenderer;
		class SpriteRenderer;
	}
	namespace manager
	{
		class RenderManager
		{
		private:
			std::vector<graphicsengine::renderables::Renderable*> moveList;
			IDirect3DDevice9* d3d_device;
			graphicsengine::renderers::IRenderer* renderers[graphicsengine::renderers::IRenderer::MAX];
		public:
			RenderManager(IDirect3DDevice9* d3d_device);
			virtual ~RenderManager(void);
			void AddRenderable(graphicsengine::renderables::Renderable* renderable);
			void RemoveRenderable(graphicsengine::renderables::Renderable* renderable);
			void MoveRenderable(graphicsengine::renderables::Renderable* renderable);
			void Render();
			virtual void CopyData(void);
		};
	}
}
