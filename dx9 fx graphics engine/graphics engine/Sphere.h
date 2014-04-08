#pragma once

#include "stdafx.h"
#include "IGraphicsEngine.h"

namespace graphicsengine
{
	namespace implementation
	{
		class Sphere
		{
		public:
			Sphere(void);
			virtual ~Sphere(void);

			LPD3DXMESH CreateMappedSphere(IGraphicsEngine* gEngine,float fRad,int slices,int stacks);

		};
	}
}
