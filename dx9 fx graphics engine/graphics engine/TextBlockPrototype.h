#pragma once
#include "Resource.h"

namespace graphicsengine
{
	namespace resources
	{
		class TextBlockPrototype :
			public Resource
		{
		private:
			std::string *text;
			int anchor;
			std::string *fontName;
		public:
			TextBlockPrototype(IDirect3DDevice9* d3d_device);
			virtual void BuildResource();
			virtual void FreeResource();
			virtual void Release(void);
			std::string GetFontName() { return *fontName; }
			std::string GetText() { return *text; }
			int GetAnchor() {return anchor; }
		public:
			virtual ~TextBlockPrototype(void);
		};
	}
}
