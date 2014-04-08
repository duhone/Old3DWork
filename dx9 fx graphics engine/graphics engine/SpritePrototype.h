#pragma once
#include "Resource.h"

namespace graphicsengine
{
	namespace resources
	{
		class FrameSetPrototype;

		class SpritePrototype :
			public Resource
		{
		private:
			bool alpha;
			std::vector<FrameSetPrototype*> framesets;
		public:
			SpritePrototype(IDirect3DDevice9* d3d_device);
		public:
			virtual ~SpritePrototype(void);
			virtual void BuildResource();
			virtual void FreeResource();
			virtual void Release(void);
			bool GetAlpha() { return alpha; }
			std::vector<FrameSetPrototype*>* GetFrameSets() { return &framesets;}
		};
	}
}
