#include "StdAfx.h"
#include "TextBlockPrototype.h"
#include ".\graphicsengine.h"
#include "IGraphicsEngine.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace graphicsengine::implementation;
using namespace std;

TextBlockPrototype::TextBlockPrototype(IDirect3DDevice9* d3d_device) :
Resource(d3d_device)
{
}

TextBlockPrototype::~TextBlockPrototype(void)
{
	if(RefCount() > 0) FreeResource();
}

void TextBlockPrototype::BuildResource()
{
	ResetFile();
	fontName = GetString();
	text = GetString();
	anchor = GetInt();
}

void TextBlockPrototype::FreeResource()
{
	delete fontName;
	delete text;
}

void TextBlockPrototype::Release()
{
	this->SubRef();
}