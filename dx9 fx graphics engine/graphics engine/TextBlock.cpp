#include "StdAfx.h"
#include "TextBlock.h"
#include ".\graphicsengine.h"
#include "IGraphicsEngine.h"
#include "TextBlockPrototype.h"
#include "Effect.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace graphicsengine::renderables;
using namespace graphicsengine::implementation;
using namespace graphicsengine::manager;
using namespace graphicsengine::renderers;
using namespace std;



TextBlock::TextBlock(TextBlockPrototype *textBlockPrototype):
Renderable()
{
	prototype = textBlockPrototype;
	textBlockPrototype->AddRef();
	this->color = 0;
	this->text = textBlockPrototype->GetText();
	this->anchor = textBlockPrototype->GetAnchor();
	font = (Font*)((GraphicsEngine*)IGraphicsEngine::getInstance())->GetResourceManager()->GetFont(textBlockPrototype->GetFontName());
	((Font*)font)->AddRef();
	effect = ((GraphicsEngine*)IGraphicsEngine::getInstance())->GetResourceManager()->GetEffect("null");
	newcolor = this->color;
	newtext = text;
	xlocation = 0;
	ylocation = 0;
	newfont = font;
	newanchor = anchor;
}

TextBlock::~TextBlock(void)
{
	renderManager->RemoveRenderable(this);
	((Font*)font)->SubRef();
	prototype->SubRef();
}

void TextBlock::SetFont(Font* font)
{
	newfont = font;
}

Font* TextBlock::GetFont()
{
	return font;
}

void TextBlock::SetText(const std::string& text)
{
	this->newtext = text;
}

void TextBlock::SetLocation(const float& x,const float& y)
{
	
	xlocation = x;
	ylocation = y;
}

void TextBlock::SetColor(const float& r,const float& g,const float& b,const float& a)
{
	
	newcolor = (int)(a*255) << 24;
	newcolor += (int)(r*255) << 16;
	newcolor += (int)(g*255) << 8;
	newcolor += (int)(b*255);
	
}

void TextBlock::CopyNewValues()
{
	
	text = newtext;
	anchor = newanchor;
	BuildBoundsRect();
	
	color = newcolor;
	SwitchFont();
}

void TextBlock::BuildBoundsRect()
{
	int height = ((GraphicsEngine*)IGraphicsEngine::getInstance())->GetScreenHeight();
	float aspectRatio = ((GraphicsEngine*)IGraphicsEngine::getInstance())->GetAspectRatio();
	float xl,yl;
	if(anchor & ANCHOR_LEFT)
		xl = aspectRatio*-0.5f + xlocation;
	else if(anchor & ANCHOR_RIGHT)
		xl = aspectRatio*0.5f + xlocation;
	else
		xl = xlocation;
	if(anchor & ANCHOR_TOP)
		yl = -0.5f + ylocation;
	else if(anchor & ANCHOR_BOTTOM)
		yl = 0.5f + ylocation;
	else
		yl = ylocation;

	xl = (xl + aspectRatio*0.5f)*height;
	yl = (yl + 0.5f)*height;

	bounds.left = (long)xl;
	bounds.right = bounds.left + 1;
	bounds.top = (long)yl;
	bounds.bottom = bounds.top + 1;
}

void TextBlock::SwitchFont()
{
	if(newfont == font) return;
	if(this->font != NULL)
	{
		((Font*)(font))->SubRef();
	}
	renderManager->RemoveRenderable(this);

	font = newfont;
	((Font*)(font))->AddRef();
	renderManager->AddRenderable(this);
}
void graphicsengine::renderables::TextBlock::AssignToRenderManager(void)
{
	renderManager->AddRenderable(this);
}

RECT* graphicsengine::renderables::TextBlock::GetBounds(void)
{
	return &bounds;
}

void TextBlock::SetAnchor(int anchor)
{
	this->newanchor = anchor;
}

IRenderer::RendererType TextBlock::GetRenderer()
{
	return IRenderer::TEXT_BLOCK;
}

Effect* TextBlock::GetEffect(void)
{
	return effect;
}


const Resource* const TextBlock::GetResource(void) const
{
	return font;
}


void TextBlock::Render()
{
	font->GetD3dFont()->DrawTextA(NULL,text.c_str(),-1,&bounds,DT_LEFT | DT_NOCLIP,color);
}