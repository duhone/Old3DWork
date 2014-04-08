#pragma once

#include"stdafx.h"

namespace graphicsengine
{
	class WindowSettings
	{
	public:
		WindowSettings(void);
		virtual ~WindowSettings(void);
		HWND hwnd;
		int antialiasing;
		int ansiotropicFiltering;
		int renderingQuality;
		
	};
}
