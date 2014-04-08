#pragma once
#include"Font.h"
#include "TextBlockPrototype.h"
#include "Effect.h"
#include "Texture.h"
#include "SpritePrototype.h"

namespace graphicsengine
{
	namespace manager
	{
		class ResourceManager
		{
		private:
			stdext::hash_map<std::string,graphicsengine::resources::Font*> fonts;
			stdext::hash_map<std::string,graphicsengine::resources::TextBlockPrototype*> textBlocks;
			stdext::hash_map<std::string,graphicsengine::resources::Effect*> effects;
			stdext::hash_map<std::string,graphicsengine::resources::Texture*> textures;
			stdext::hash_map<std::string,graphicsengine::resources::SpritePrototype*> sprites;

			FILE* file;
			IDirect3DDevice9* d3d_device;
			virtual void ClearFonts(void);
			virtual void ClearTextBlocks(void);
			virtual void ClearTextures(void);
			virtual void ClearSprites(void);
			void ClearEffects(void);
		public:
			ResourceManager(IDirect3DDevice9* d3d_device);
			virtual ~ResourceManager(void);
			virtual void Clear(void);
			virtual void LoadData(const std::string& fileName);
			virtual graphicsengine::resources::Font* GetFont(const std::string& name);
			virtual graphicsengine::resources::Effect* GetEffect(const std::string& name);
			virtual graphicsengine::resources::TextBlockPrototype* GetTextBlock(const std::string& name);
			virtual graphicsengine::resources::Font* GetFontInternal(const std::string& name);
			virtual graphicsengine::resources::Texture* GetTexture(const std::string& name);
			virtual graphicsengine::resources::SpritePrototype* GetSprite(const std::string& name);
		private:
			void LoadFonts(void);
			void LoadTextBlocks(void);
			void LoadEffects(void);
			void LoadTextures(void);
			void LoadSprites(void);

		};
	}
}