#include "StdAfx.h"
#include "ResourceManager.h"
#include "TextBlockPrototype.h"
#include "NullEffect.h"

using namespace stdext;
using namespace graphicsengine;
using namespace std;
using namespace stdext;
using namespace graphicsengine::manager;
using namespace graphicsengine::resources;


graphicsengine::manager::ResourceManager::ResourceManager(IDirect3DDevice9* d3d_device)
{
	file = NULL;
	this->d3d_device = d3d_device;
}

graphicsengine::manager::ResourceManager::~ResourceManager(void)
{
	if(file != NULL)
	{
		fclose(file);
		file = NULL;
	}
	Clear();
}

void graphicsengine::manager::ResourceManager::Clear(void)
{
	ClearFonts();
	ClearTextBlocks();
	ClearEffects();
	ClearTextures();
	ClearSprites();
}

void graphicsengine::manager::ResourceManager::ClearFonts(void)
{
	hash_map<string,Font*>::iterator iterator =  fonts.begin();
	while(iterator != fonts.end())
	{
		Font* font = iterator->second;
		delete font;
		iterator++;
		
	}
	fonts.clear();
	
}

void graphicsengine::manager::ResourceManager::ClearTextBlocks(void)
{
	
	hash_map<string,TextBlockPrototype*>::iterator iterator =  textBlocks.begin();
	while(iterator != textBlocks.end())
	{
		TextBlockPrototype* textBlock = iterator->second;
		delete textBlock;
		iterator++;
		
	}
	textBlocks.clear();
}

void graphicsengine::manager::ResourceManager::ClearEffects(void)
 {
	hash_map<string,Effect*>::iterator iterator =  effects.begin();
	while(iterator != effects.end())
	{
		Effect* effect = iterator->second;
		delete effect;
		iterator++;
		
	}
	effects.clear();
 }

void graphicsengine::manager::ResourceManager::ClearTextures(void)
{
	hash_map<string,Texture*>::iterator iterator =  textures.begin();
	while(iterator != textures.end())
	{
		Texture* texture = iterator->second;
		delete texture;
		iterator++;
		
	}
	textures.clear();
	
}

void graphicsengine::manager::ResourceManager::ClearSprites(void)
{
	hash_map<string,SpritePrototype*>::iterator iterator =  sprites.begin();
	while(iterator != sprites.end())
	{
		SpritePrototype* sprite = iterator->second;
		delete sprite;
		iterator++;
		
	}
	sprites.clear();
	
}

 void ResourceManager::LoadData(const std::string& fileName)
 {
	if(file != NULL) fclose(file);
	Clear();
	fopen_s(&file,fileName.c_str(),"rb");
	LoadFonts();
	LoadTextBlocks();
	LoadEffects();
	LoadTextures();
	LoadSprites();
 }

 Font* ResourceManager::GetFont(const std::string& name)
 {
	 hash_map<string,Font*>::iterator iterator = fonts.find(name);
	 if(iterator == fonts.end()) return NULL;
	 Font* result = iterator->second;
	 result->AddRef();
	 return result;
 }

 Effect* ResourceManager::GetEffect(const std::string& name)
 {
	 hash_map<string,Effect*>::iterator iterator = effects.find(name);
	 if(iterator == effects.end()) return NULL;
	 Effect* result = iterator->second;
	 result->AddRef();
	 return result;
 }

 TextBlockPrototype* ResourceManager::GetTextBlock(const std::string& name)
 {
	 hash_map<string,TextBlockPrototype*>::iterator iterator = textBlocks.find(name);
	 if(iterator == textBlocks.end()) return NULL;
	 TextBlockPrototype* result = iterator->second;
	 return result;
 }

 Font* ResourceManager::GetFontInternal(const std::string& name)
 {
	 hash_map<string,Font*>::iterator iterator = fonts.find(name);
	 if(iterator == fonts.end()) return NULL;
	 Font* result = iterator->second;
	 return result;
 }

 Texture* ResourceManager::GetTexture(const std::string& name)
 {
	 hash_map<string,Texture*>::iterator iterator = textures.find(name);
	 if(iterator == textures.end()) return NULL;
	 Texture* result = iterator->second;
	 result->AddRef();
	 return result;
 }

 SpritePrototype* ResourceManager::GetSprite(const std::string& name)
 {
	 hash_map<string,SpritePrototype*>::iterator iterator = sprites.find(name);
	 if(iterator == sprites.end()) return NULL;
	 SpritePrototype* result = iterator->second;
	 return result;
 }

 void graphicsengine::manager::ResourceManager::LoadFonts(void)
 {
	 int nfonts = 0;
	 fread(&nfonts,sizeof(int),1,file);
	 for(int count = 0;count < nfonts;count++)
	 {
		int recordSize;
		fread(&recordSize,sizeof(int),1,file);
		Font* font = new Font(d3d_device);
		fpos_t filepos;
		fgetpos(file,&filepos);
		font->SetFilePosition(file,filepos);
		fseek(file,(long)filepos,SEEK_SET);
		fseek(file,recordSize,SEEK_CUR);
		fonts[font->Name()] = font;
	 }
 }

 void graphicsengine::manager::ResourceManager::LoadTextBlocks(void)
 {
	 int nblocks = 0;
	 fread(&nblocks,sizeof(int),1,file);
	 for(int count = 0;count < nblocks;count++)
	 {
		int recordSize;
		fread(&recordSize,sizeof(int),1,file);
		TextBlockPrototype* textBlock = new TextBlockPrototype(d3d_device);
		fpos_t filepos;
		fgetpos(file,&filepos);
		textBlock->SetFilePosition(file,filepos);
		fseek(file,(long)filepos,SEEK_SET);
		fseek(file,recordSize,SEEK_CUR);
		textBlocks[textBlock->Name()] = textBlock;
	 }
 }
 void graphicsengine::manager::ResourceManager::LoadEffects(void)
 {
	 int nblocks = 0;
	 fread(&nblocks,sizeof(int),1,file);
	 for(int count = 0;count < nblocks;count++)
	 {
		int recordSize;
		fread(&recordSize,sizeof(int),1,file);
		Effect* effect = new Effect(d3d_device);
		fpos_t filepos;
		fgetpos(file,&filepos);
		effect->SetFilePosition(file,filepos);
		effect->SubRef();
		fseek(file,(long)filepos,SEEK_SET);
		fseek(file,recordSize,SEEK_CUR);
		effects[effect->Name()] = effect;
	 }

	 effects["null"] = new NullEffect(d3d_device);
 }
void graphicsengine::manager::ResourceManager::LoadTextures(void)
 {
	 int nblocks = 0;
	 fread(&nblocks,sizeof(int),1,file);
	 for(int count = 0;count < nblocks;count++)
	 {
		int recordSize;
		fread(&recordSize,sizeof(int),1,file);
		Texture* texture = new Texture(d3d_device);
		fpos_t filepos;
		fgetpos(file,&filepos);
		texture->SetFilePosition(file,filepos);
		fseek(file,(long)filepos,SEEK_SET);
		fseek(file,recordSize,SEEK_CUR);
		textures[texture->Name()] = texture;
	 }
 }
 void graphicsengine::manager::ResourceManager::LoadSprites(void)
 {
	 int nblocks = 0;
	 fread(&nblocks,sizeof(int),1,file);
	 for(int count = 0;count < nblocks;count++)
	 {
		int recordSize;
		fread(&recordSize,sizeof(int),1,file);
		SpritePrototype* sprite = new SpritePrototype(d3d_device);
		fpos_t filepos;
		fgetpos(file,&filepos);
		sprite->SetFilePosition(file,filepos);
		fseek(file,(long)filepos,SEEK_SET);
		fseek(file,recordSize,SEEK_CUR);
		sprites[sprite->Name()] = sprite;
	 }
 }
