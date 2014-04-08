
namespace graphicsengine
{
	namespace renderables
	{

		class WorldExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
		public:
			WorldExecutePlan(Effect* effect,D3DXHANDLE handle,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->world = world;
			}
			void Execute()
			{
				effect->SetMatrix(handle,world);
			}
		};

		class WorldInverseExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
		public:
			WorldInverseExecutePlan(Effect* effect,D3DXHANDLE handle,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->world = world;
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixInverse(&matrix,NULL,world);
				effect->SetMatrix(handle,&matrix);
			}
		};

		class ViewExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			const D3DXMATRIX* view;
		public:
			ViewExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine)
			{
				this->effect = effect;
				this->handle = handle;
				this->view = gengine->View();
			}
			void Execute()
			{
				effect->SetMatrix(handle,view);
			}
		};

		class ViewInverseExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			const D3DXMATRIX* view;
		public:
			ViewInverseExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine)
			{
				this->effect = effect;
				this->handle = handle;
				this->view = gengine->View();
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixInverse(&matrix,NULL,view);
				effect->SetMatrix(handle,&matrix);
			}
		};

		class WorldViewExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
			const D3DXMATRIX* view;
		public:
			WorldViewExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->view = gengine->View();
				this->world = world;
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixMultiply(&matrix,world,view);
				effect->SetMatrix(handle,&matrix);
			}
		};

		class WorldViewInverseExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
			const D3DXMATRIX* view;
		public:
			WorldViewInverseExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->view = gengine->View();
				this->world = world;
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixMultiply(&matrix,world,view);
				D3DXMatrixInverse(&matrix,NULL,&matrix);
				effect->SetMatrix(handle,&matrix);
			}
		};

		class WorldViewProjectionExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
			const D3DXMATRIX* viewProj;
		public:
			WorldViewProjectionExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->viewProj = gengine->ViewProj();
				this->world = world;
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixMultiply(&matrix,world,viewProj);
				effect->SetMatrix(handle,&matrix);
			}
		};

		class WorldViewParallelExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXMATRIX* world;
			const D3DXMATRIX* viewPara;
		public:
			WorldViewParallelExecutePlan(Effect* effect,D3DXHANDLE handle,GraphicsEngine* gengine,D3DXMATRIX* world)
			{
				this->effect = effect;
				this->handle = handle;
				this->viewPara = gengine->ViewPara();
				this->world = world;
			}
			void Execute()
			{
				D3DXMATRIX matrix;
				D3DXMatrixMultiply(&matrix,world,viewPara);
				effect->SetMatrix(handle,&matrix);
			}
		};
		class FrameNumberExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			FrameSet **currentframeSet;
		public:
			FrameNumberExecutePlan(Effect* effect,D3DXHANDLE handle,FrameSet **currentframeSet)
			{
				this->effect = effect;
				this->handle = handle;
				this->currentframeSet = currentframeSet;
			}
			void Execute()
			{
				effect->SetInt(handle,(*currentframeSet)->CurrentFrame());
			}
		};

		class FrameWidthExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			float width;
		public:
			FrameWidthExecutePlan(Effect* effect,D3DXHANDLE handle,float width)
			{
				this->effect = effect;
				this->handle = handle;
				this->width = width;
			}
			void Execute()
			{
				effect->SetFloat(handle,width);
			}
		};

		class ColorExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXVECTOR4 *color;
		public:
			ColorExecutePlan(Effect* effect,D3DXHANDLE handle,D3DXVECTOR4 *color)
			{
				this->effect = effect;
				this->handle = handle;
				this->color = color;
			}
			void Execute()
			{
				effect->SetVector(handle,color);
			}
		};

		class CustomExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
			D3DXHANDLE handle;
			D3DXVECTOR4 *value;
		public:
			CustomExecutePlan(Effect* effect,D3DXHANDLE handle,D3DXVECTOR4 *value)
			{
				this->effect = effect;
				this->handle = handle;
				this->value = value;
			}
			void Execute()
			{
				effect->SetVector(handle,value);
			}
		};

		class CommitExecutePlan : public IExecuteSemantic
		{
		private:
			Effect* effect;
		public:
			CommitExecutePlan(Effect* effect)
			{
				this->effect = effect;
			}
			void Execute()
			{
				effect->CommitChanges();
			}
		};

		class ExecutionPlanBuilder
		{
		private:
			ObjectExecutionPlan *plan;
			Effect *effect;
			Sprite *sprite;
		public:
			ExecutionPlanBuilder(ObjectExecutionPlan *plan,Effect *effect,Sprite* sprite)
			{
				this->plan = plan;
				this->effect = effect;
				this->sprite = sprite;
			}
			void operator()(Semantics::SEMANTICS semantic)
			{
				D3DXHANDLE handle = effect->GetHandleForSemantic(semantic);

				switch(semantic)
				{
				case Semantics::World:
					plan->AddExecute(new WorldExecutePlan(effect,handle,sprite->World()));
					break;
				case Semantics::WorldInverse:
					plan->AddExecute(new WorldInverseExecutePlan(effect,handle,sprite->World()));
					break;
				case Semantics::View:
					plan->AddExecute(new ViewExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance()));
					break;
				case Semantics::ViewInverse:
					plan->AddExecute(new ViewInverseExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance()));
					break;
				case Semantics::WorldView:
					plan->AddExecute(new WorldViewExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance(),sprite->World()));
					break;
				case Semantics::WorldViewInverse:
					plan->AddExecute(new WorldViewInverseExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance(),sprite->World()));
					break;
				case Semantics::WorldViewProjection:
					plan->AddExecute(new WorldViewProjectionExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance(),sprite->World()));
					break;
				case Semantics::WorldViewParallel:
					plan->AddExecute(new WorldViewParallelExecutePlan(effect,handle,
						(GraphicsEngine*)IGraphicsEngine::getInstance(),sprite->World()));
					break;
				case Semantics::Color:
					plan->AddExecute(new ColorExecutePlan(effect,handle,sprite->Color()));
					break;
				case Semantics::Texture0:
					break;
				case Semantics::FrameWidth:
					plan->AddExecute(new FrameWidthExecutePlan(effect,handle,
						sprite->GetFrameSet()->frameWidth/(float)sprite->GetCurrentTexture()->Width()));
					break;
				case Semantics::FrameNumber:
					plan->AddExecute(new FrameNumberExecutePlan(effect,handle,sprite->GetFrameSetPtr()));
					break;
				};
			}
		};
	}
}