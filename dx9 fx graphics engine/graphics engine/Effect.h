#pragma once
#include "Resource.h"
#include "IResource.h"
#include "IQualityChangedObserver.h"
#include "Semantics.h"

namespace graphicsengine
{
	namespace renderables
	{
		class Renderable;
	}
	namespace resources
	{
		class Technique;
		class Texture;

		class Effect : public IResource, public Resource, public graphicsengine::implementation::IQualityChangedObserver
		{
		private:
			ID3DXEffect* effect;
			std::vector<Technique*> techniques;
			Technique* current;
			std::vector<graphicsengine::implementation::Semantics::SEMANTICS> semantics;
			stdext::hash_map<graphicsengine::implementation::Semantics::SEMANTICS,D3DXHANDLE> semanticLookup;
			stdext::hash_map<std::string,D3DXHANDLE> customSemanticLookup;
		public:
			Effect(IDirect3DDevice9* d3d_device);
			D3DXHANDLE GetHandleForSemantic(graphicsengine::implementation::Semantics::SEMANTICS semantic);
			const std::vector<graphicsengine::implementation::Semantics::SEMANTICS>& GetAvailableSemantics() const { return semantics; }
			const stdext::hash_map<std::string,D3DXHANDLE>& GetCustomSemantics() const { return customSemanticLookup; }
			void SetTexture(D3DXHANDLE handle,Texture* texture);
			void SetMatrix(D3DXHANDLE handle,const D3DXMATRIX *matrix);
			void SetInt(D3DXHANDLE handle,int arg);
			void SetFloat(D3DXHANDLE handle,float arg);
			void SetVector(D3DXHANDLE handle,const D3DXVECTOR4 *arg);
			void CommitChanges();
			int NumPasses() const;
		public:
			virtual ~Effect(void);
		public:
			virtual void BuildResource(void);
		public:
			virtual void FreeResource(void);
		public:
			virtual void Release(void);
			ID3DXEffect* GetEffect() {return effect;}
		public:
			virtual void QualityChanged(int newQuality);
		public:
			void BuildParameters(D3DXEFFECT_DESC desc);
		};
	}
}