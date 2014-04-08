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
		template<class T>
		class RenderFO
		{
		public:
			void operator () (std::pair<int,T> object)
			{
				object.second->Render();
			}
		};

		template<class T>
		class CopyDataFO
		{
		public:
			void operator () (std::pair<int,T> object)
			{
				object.second->CopyNewValues();
			}
		};

		template<class Holder,class Type,class Item>
		class RendererList
		{
		private:
			stdext::hash_map<int,Holder*> renderables;
		public:
			RendererList() {};
			virtual ~RendererList(void) {};
			inline void AddRenderable(Type* type,Item* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
			{
				if(!Contains(type->GetId()))
				{
					renderables.insert(std::pair<int,Holder*>(type->GetId(),new Holder(type)));
				}

				(*this)[type->GetId()]->AddRenderable(renderable,plan,effect);
			};
			inline void RemoveRenderable(Type* type,Item* renderable)
			{
				if(Contains(type->GetId()))
				{
					(*this)[type->GetId()]->RemoveRenderable(renderable);
				}
				if((*this)[type->GetId()]->Empty())
				{
					delete (*this)[type->GetId()];
					renderables.erase(type->GetId());
				}
			};
			inline Holder* operator[] (int id)
			{
				stdext::hash_map<int,Holder*>::iterator iterator = renderables.find(id);
				if(iterator == renderables.end())
					return NULL;
				else
					return iterator->second;
			}
			inline bool Contains(int id) const
			{
				stdext::hash_map<int,Holder*>::const_iterator iterator = renderables.find(id);
				if(iterator == renderables.end())
					return false;
				else
					return true;
			}
			inline void Render() const
			{
				for_each(renderables.begin(),renderables.end(),RenderFO<Holder*>());
			}
			inline bool Empty() const
			{
				return renderables.empty();
			}
			inline void CopyNewValues()
			{
				for_each(renderables.begin(),renderables.end(),CopyDataFO<Holder*>());
			}
			template<class Ftor>
			inline void ForAll( Ftor ftor)
			{
				for_each(renderables.begin(),renderables.end(),ftor);
			}
		};

		template<class Item>
		class RenderList
		{
		private:
			stdext::hash_map<int,Item*> renderables;
		public:
			RenderList() {};
			virtual ~RenderList(void) {};
			inline void AddRenderable(Item* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
			{
				if(!Contains(renderable->GetId()))
				{
					renderables.insert(std::pair<int,Item*>(renderable->GetId(),renderable));
					renderable->BuildExecutionPlan(plan,effect);
				}
			};
			inline void RemoveRenderable(Item* renderable)
			{
				if(Contains(renderable->GetId()))
				{
					renderables.erase(renderable->GetId());
				}
			};
			inline Item* operator[] (int id)
			{
				stdext::hash_map<int,Item*>::iterator iterator = renderables.find(id);
				if(iterator == renderables.end())
					return NULL;
				else
					return iterator->second;
			}
			inline bool Contains(int id) const
			{
				stdext::hash_map<int,Item*>::const_iterator iterator = renderables.find(id);
				if(iterator == renderables.end())
					return false;
				else
					return true;
			}
			inline void Render() const
			{
				for_each(renderables.begin(),renderables.end(),RenderFO<Item*>(/*effect*/));
			}
			void CopyNewValues()
			{
				for_each(renderables.begin(),renderables.end(),CopyDataFO<Item*>());
			}
			inline bool Empty() const
			{
				return renderables.empty();
			}
			template<class Ftor>
			inline void ForAll( Ftor ftor)
			{
				for_each(renderables.begin(),renderables.end(),ftor);
			}
		};
	}
}
