#pragma once

#include "IRenderable.h"

namespace graphicsengine
{
	class ITextBlock : public IRenderable
	{
	public:
		ITextBlock(void);
	public:
		static const int ANCHOR_FLOAT = 0;
		static const int ANCHOR_LEFT = 0x01;
		static const int ANCHOR_RIGHT = 0x02;
		static const int ANCHOR_TOP = 0x04;
		static const int ANCHOR_BOTTOM = 0x08;

		virtual ~ITextBlock(void);
		virtual void SetText(const std::string& text) = 0;
		virtual void SetLocation(const float& x,const float& y) = 0;
		virtual void SetColor(const float& r,const float& g,const float& b,const float& a) = 0;
		virtual void SetAnchor(int anchor) = 0;
	};
}
