#pragma once
#include "IRenderable.h"

namespace graphicsengine
{
	class ISprite : public IRenderable
	{
	public:

		ISprite(void)
		{
		}
	public:

		virtual ~ISprite(void)
		{
		}
	public:
		virtual float X(void) = 0;
		virtual float Y(void) = 0;
		virtual float Z(void) = 0;
		virtual void SetPosition(float x, float y, float z) = 0;
		virtual void SetFrameSet(std::string set) = 0;
		virtual std::string GetCurrentFrameSet() = 0;
		virtual void Move(float x, float y, float z) = 0;
		virtual void SetScale(float x, float y) = 0;
		virtual void ResetRotation(void) = 0;
		virtual void RotateX(float angle) = 0;
		virtual void RotateY(float angle) = 0;
		virtual void RotateZ(float angle) = 0;
		virtual void SetColor(float red, float green, float blue, float alpha) = 0;
		virtual void Animate(bool animate) = 0;
		virtual void SetCustomParameter(const std::string& parameter,float x,float y,float z,float w) = 0;
		virtual void Visible(bool visible) = 0;
		virtual bool Visible() const = 0;
	};
}