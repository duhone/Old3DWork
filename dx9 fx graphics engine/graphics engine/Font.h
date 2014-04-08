#pragma once

#include"Resource.h"

namespace graphicsengine
{
	namespace resources
	{
		class Font  : public Resource
		{
		public:
			Font(IDirect3DDevice9* d3d_device);
			virtual ~Font(void);
			virtual void BuildResource();
			virtual void FreeResource();
			virtual void Release(void);
			ID3DXFont* GetD3dFont() { return font;}
		private:
			ID3DXFont* font;
		};
	}
}
