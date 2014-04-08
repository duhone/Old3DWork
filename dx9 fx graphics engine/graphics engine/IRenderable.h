#pragma once

#include"IResource.h"

namespace graphicsengine
{
	class IRenderable
	{
	public:
		IRenderable(void);
	public:
		virtual ~IRenderable(void);
		virtual void Release();
	};
}