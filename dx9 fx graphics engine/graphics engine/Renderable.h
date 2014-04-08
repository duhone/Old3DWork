#pragma once

#include "FileResource.h"
#include "d3dx9.h"
#include "IRenderer.h"

namespace graphicsengine
{
	namespace manager
	{
		class ResourceManager;
		class RenderManager;
	}
	namespace resources
	{
		class Effect;
		class Resource;
	}
}

namespace graphicsengine
{
	namespace renderables
	{
		class Renderable
		{
		protected:
			IDirect3DDevice9* d3d_device;
			graphicsengine::manager::RenderManager* renderManager;
			unsigned long id;
			static unsigned long nextId;
		public:
			Renderable();
		public:
			virtual ~Renderable(void);
			virtual void CopyNewValues() = 0;
			virtual void AssignToRenderManager() = 0;
			virtual void SetRenderManager(graphicsengine::manager::RenderManager* renderManager)
			{
				this->renderManager = renderManager;
				if(id != 0) AssignToRenderManager();
			};
			long GetId() { return id;}
			virtual graphicsengine::renderers::IRenderer::RendererType GetRenderer() = 0;
		public:
			virtual graphicsengine::resources::Effect* GetEffect(void) = 0;
			virtual const graphicsengine::resources::Resource* const GetResource(void) const = 0;
			virtual void Render() = 0;
			virtual void BuildExecutionPlan(graphicsengine::renderables::ObjectExecutionPlan* plan,
				graphicsengine::resources::Effect* effect) {};
			virtual void ReadyToMove() {};
		};
	}
}

