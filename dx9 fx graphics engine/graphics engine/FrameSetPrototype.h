#pragma once

namespace graphicsengine
{
	namespace resources
	{
		class FrameSetPrototype
		{
		private:
			std::string name;
			std::string texture;
			std::string effect;
			int framewidth;
			float fps;
		public:
			FrameSetPrototype(std::string* name,std::string* texture,std::string* effect,int framewidth,float fps);
		public:
			virtual ~FrameSetPrototype(void);
			std::string* GetName() { return &name; }
			std::string* GetTexture() { return &texture; }
			std::string* GetEffect() { return &effect; }
			int GetFrameWidth() {return framewidth; }
			float GetFPS() { return fps; }
		};
	}
}
