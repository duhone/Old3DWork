#pragma once
#include "Resource.h"
#include "IResource.h"

namespace graphicsengine
{
	namespace resources
	{
		class Texture : public IResource , public Resource
		{
		private:
			LPDIRECT3DTEXTURE9 texture;
			int width;
			int height;
			int ncomponents;
			int bpc;
			unsigned char PaethPredictor(unsigned char a,unsigned char b,unsigned char c);
		public:
			Texture(IDirect3DDevice9* d3d_device);
			int Width() {return width;}
		public:
			virtual ~Texture(void);
		public:
			virtual void BuildResource(void);
		public:
			virtual void FreeResource(void);
		public:
			virtual void Release(void);
			LPDIRECT3DTEXTURE9 GetTexture() {return texture;}
		private:
			void DecompressTexture(unsigned char* frame,int frameWidth);
			D3DFORMAT GetFormat(void);
		private:
			void FilterLeft(unsigned char* row,int frameWidth);
			void FilterUp(unsigned char* prevrow,unsigned char* row,int frameWidth);
			void FilterAvg(unsigned char* prevrow,unsigned char* row,int frameWidth,int y);
			void FilterPaeth(unsigned char* prevrow,unsigned char* row,int frameWidth,int y);
			void FilterDx(unsigned char* row,int frameWidth);
			void FilterDy(unsigned char* prevrow2,unsigned char* prevrow,unsigned char* row,int frameWidth,int y);
		private:
			void CombineFrame(char* frame, char* textureBuffer, int frameWidth, int component,int pitch);
		};
	}
}
