#pragma once
#include "Effect.h"

namespace graphicsengine
{
	namespace resources
	{
		class NullEffect :
			public Effect
		{
		public:
			NullEffect(IDirect3DDevice9* d3d_device);
		public:
			virtual ~NullEffect(void);
			virtual void BuildResource(void);
		};
	}
}
