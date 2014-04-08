#include "StdAfx.h"
#include "Texture.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;

Texture::Texture(IDirect3DDevice9* d3d_device) :
Resource(d3d_device)
{
}

Texture::~Texture(void)
{
	if(RefCount() > 0) FreeResource();
}

void Texture::BuildResource(void)
{
	ResetFile();
	width = this->GetInt();
	height = this->GetInt();
	bpc = this->GetInt();
	ncomponents = this->GetInt();
	int nframs = this->GetInt();
	int frameWidth = width/nframs;

	int compressedSize = this->GetInt();
	int decompressedSize = width*height*ncomponents*4;
	char* compressedData = GetCompressedData(compressedSize,decompressedSize);

	D3DXCreateTexture(d3d_device,width,height,D3DX_DEFAULT,0,GetFormat(),D3DPOOL_MANAGED ,&texture);

	
	D3DLOCKED_RECT lockedTexture;
	texture->LockRect(0,&lockedTexture,NULL,D3DLOCK_DISCARD);

	for(int frame = 0;frame < nframs;frame++)
	{
		for(int component = 0;component < ncomponents;component++)
		{
			char* frameBuffer = compressedData+frame*(frameWidth+1)*height*ncomponents+component*(frameWidth+1)*height;
			DecompressTexture((unsigned char*)frameBuffer,frameWidth);
			CombineFrame(frameBuffer,((char*)lockedTexture.pBits)+frame*frameWidth*ncomponents,frameWidth,component,lockedTexture.Pitch);

		}
	}

	texture->UnlockRect(0);
	D3DXFilterTexture(texture,NULL,0,D3DX_FILTER_BOX);
}

void Texture::FreeResource(void)
{
	texture->Release();
	texture = NULL;
}

void Texture::Release(void)
{
	this->SubRef();
}

D3DFORMAT graphicsengine::resources::Texture::GetFormat(void)
{
	switch (bpc)
	{
	case 1:
		switch(ncomponents)
		{
		case 1:
			return D3DFMT_A8;
		case 2:
			return D3DFMT_V8U8;
		case 3:
			return D3DFMT_X8R8G8B8;
		case 4:
			return D3DFMT_A8R8G8B8;
		};
		break;
	};
	return D3DFMT_A8R8G8B8;
}

void graphicsengine::resources::Texture::DecompressTexture(unsigned char* frame,int frameWidth)
{
	for(int y = 0;y<height;y++)
	{
		char type = frame[(frameWidth+1)*y];
		switch(type)
		{
		case 1:
			FilterLeft(frame+(frameWidth+1)*y+1,frameWidth);
			break;
		case 2:
			if(y>0)
				FilterUp(frame+(frameWidth+1)*(y-1)+1,frame+(frameWidth+1)*y+1,frameWidth);
			break;
		case 3:
			FilterAvg(frame+(frameWidth+1)*(y-1)+1,frame+(frameWidth+1)*y+1,frameWidth,y);
			break;
		case 4:
			FilterPaeth(frame+(frameWidth+1)*(y-1)+1,frame+(frameWidth+1)*y+1,frameWidth,y);
			break;
		case 5:
			FilterDx(frame+(frameWidth+1)*y+1,frameWidth);
			break;
		case 6:
			FilterDy(frame+(frameWidth+1)*(y-2)+1,frame+(frameWidth+1)*(y-1)+1,frame+(frameWidth+1)*y+1,frameWidth,y);
			break;
		};

	}
}

void graphicsengine::resources::Texture::FilterLeft(unsigned char* row,int frameWidth)
{
	for(int x=1;x<frameWidth;x++)
	{
		row[x] = row[x-1] + row[x];
	}
}

void graphicsengine::resources::Texture::FilterUp(unsigned char* prevrow,unsigned char* row,int frameWidth)
{
	for(int x=0;x<frameWidth;x++)
	{
		row[x] = prevrow[x] + row[x];
	}
}

void graphicsengine::resources::Texture::FilterAvg(unsigned char* prevrow,unsigned char* row,int frameWidth,int y)
{
	if(y == 0)
	{
		FilterLeft(row,frameWidth);
	}
	else
	{
		row[0] = prevrow[0] + row[0];
		for(int x=1;x<frameWidth;x++)
		{
			row[x] += (prevrow[x] + row[x-1])/(unsigned char)2;
		}
	}
}

void graphicsengine::resources::Texture::FilterPaeth(unsigned char* prevrow,unsigned char* row,int frameWidth,int y)
{
	for (int x = 0; x < frameWidth; x++)
    {
        unsigned char a, b, c;
        if (x == 0)
            a = 0;
        else a = row[x - 1];
        if (y == 0)
            b = 0;
        else
            b = prevrow[x];
        if (y == 0 || x == 0)
            c = 0;
        else
            c = prevrow[x - 1];
        row[x] += PaethPredictor(a, b, c);
    }
}

void graphicsengine::resources::Texture::FilterDx(unsigned char* row,int frameWidth)
{
	row[1] = row[0] + row[1];
	for(int x=2;x<frameWidth;x++)
	{
		row[x] += row[x-1] + (row[x-1] - row[x-2]);
	}
}

void graphicsengine::resources::Texture::FilterDy(unsigned char* prevrow2,unsigned char* prevrow,unsigned char* row,int frameWidth,int y)
{
	if(y == 0)
		return;
	else if(y == 1)
		FilterUp(prevrow,row,frameWidth);
	else
	{
		for(int x=0;x<frameWidth;x++)
		{
			row[x] += prevrow[x] + (prevrow[x] - prevrow2[x]);
		}
	}
}

unsigned char Texture::PaethPredictor(unsigned char a,unsigned char b,unsigned char c)
{
    // a = left, b = above, c = upper left
    int p = a + b - c;        // initial estimate
    int pa = abs(p - a);      // distances to a, b, c
    int pb = abs(p - b);
    int pc = abs(p - c);
   // return nearest of a,b,c,
    // breaking ties in order a,b,c.
    if((pa <= pb) && (pa <= pc)) return a;
    else if(pb <= pc) return b;
    else return c;
}

void graphicsengine::resources::Texture::CombineFrame(char* frame, char* textureBuffer, int frameWidth, int component,int pitch)
{
	for(int y = 0;y<height;y++)
	{
		for(int x=0;x<frameWidth;x++)
		{
			switch(component)
			{
			case 0:
				if(ncomponents == 3)
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(2)] = frame[y*(frameWidth+1)+x+1];
				else
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(0)] = frame[y*(frameWidth+1)+x+1];
				break;
			case 1:
				if(ncomponents == 3)
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(0)] = frame[y*(frameWidth+1)+x+1];
				else
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(1)] = frame[y*(frameWidth+1)+x+1];
				break;
			case 2:
				if(ncomponents == 3)
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(1)] = frame[y*(frameWidth+1)+x+1];
				else
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(2)] = frame[y*(frameWidth+1)+x+1];
				break;
			case 3:
				if(ncomponents == 3)
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(3)] = frame[y*(frameWidth+1)+x+1];
				else
					textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(3)] = frame[y*(frameWidth+1)+x+1];
				break;
			};
			//textureBuffer[(height-y)*pitch/*width*ncomponents*/+x*4+(ncomponents-1-component)] = frame[y*(frameWidth+1)+x+1];
		}
	}
}
