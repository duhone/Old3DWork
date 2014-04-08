#pragma once

namespace graphicsengine
{
	namespace resources
	{
		class Texture;
		class Effect;
	}
	namespace renderables
	{
		class FrameSet
		{
		public:
			FrameSet(std::string* name,graphicsengine::resources::Texture* texture,
				graphicsengine::resources::Effect* effect,int framewidth, float fps);
		public:
			virtual ~FrameSet(void);
		public:
			std::string name;
		public:
			graphicsengine::resources::Texture* texture;
			graphicsengine::resources::Effect* effect;
			graphicsengine::resources::Effect* GetEffect(void);
		public:
			int frameWidth;
			void Animate(float time);
			void InitAnimation(void);
			int CurrentFrame() { return currentFrame;}
		private:
			float fps;
			int nframes;
			int currentFrame;
			float timeBetweenFrames;
			float timeTillNextFrame;
		};
	}
}
