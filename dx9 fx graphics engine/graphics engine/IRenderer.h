#pragma once


namespace graphicsengine
{
	namespace resources
	{
		class Effect;
	}
	namespace renderables
	{
		class Renderable;
		class ObjectExecutionPlan;
	}
	namespace renderers
	{
		class IRenderer
		{
		public:
			enum RendererType
			{
				TEXT_BLOCK,
				SPRITE,
				MAX
			};
		private:
			RendererType type;
		public:

			IRenderer(RendererType type)
			{
				this->type = type;
			}

			virtual ~IRenderer(void)
			{
			}
			virtual void AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect) = 0;
			virtual void RemoveRenderable(graphicsengine::renderables::Renderable* renderable) = 0;
			virtual void Render() = 0;
			virtual bool Empty() = 0;
			virtual void CopyNewValues() = 0;
		};
	}
}
