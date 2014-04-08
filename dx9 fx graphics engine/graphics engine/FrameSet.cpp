#include "StdAfx.h"
#include "FrameSet.h"
#include "Texture.h"
#include "Effect.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace graphicsengine::resources;

FrameSet::FrameSet(std::string* name,Texture* texture,Effect* effect,int framewidth, float fps)
: texture(NULL)
, frameWidth(0)
, fps(0)
{
	this->name = *name;
	this->texture = texture;
	texture->AddRef();
	this->effect = effect;
	effect->AddRef();
	this->frameWidth = framewidth;
	this->fps = fps;
	this->timeBetweenFrames = 1.0f/fps;
	this->timeTillNextFrame = timeBetweenFrames;
	nframes = texture->Width()/frameWidth;
	currentFrame = 0;
}

FrameSet::~FrameSet(void)
{
	texture->SubRef();
	effect->SubRef();
}

void graphicsengine::renderables::FrameSet::Animate(float time)
{
	timeTillNextFrame -= time;
	if(timeTillNextFrame <= 0)
	{
		timeTillNextFrame += timeBetweenFrames;
		currentFrame++;
		if(currentFrame >= nframes)
			currentFrame = 0;
	}
}

void graphicsengine::renderables::FrameSet::InitAnimation(void)
{
	currentFrame = 0;
	timeTillNextFrame += timeBetweenFrames;
}

Effect* graphicsengine::renderables::FrameSet::GetEffect(void)
{
	return effect;
}
