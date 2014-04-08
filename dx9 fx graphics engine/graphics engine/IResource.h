#pragma once

namespace graphicsengine
{
	class IResource
	{
	public:
		IResource(void);
	public:
		virtual ~IResource(void);
		virtual void Release(void) = 0;
			
	};
}