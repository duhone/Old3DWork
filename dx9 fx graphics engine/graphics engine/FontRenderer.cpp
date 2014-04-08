#include "StdAfx.h"
#include "FontRenderer.h"
#include "Font.h"
#include "TextBlock.h"

using namespace graphicsengine;
using namespace graphicsengine::renderables;
using namespace graphicsengine::renderers;
using namespace graphicsengine::resources;

FontRenderer::FontRenderer(Font* font)
{
	this->font = font;
}

FontRenderer::~FontRenderer(void)
{
}

void FontRenderer::AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
{
	renderList.AddRenderable(renderable,plan,effect);
}

void FontRenderer::RemoveRenderable(graphicsengine::renderables::Renderable* renderable)
{
	renderList.RemoveRenderable(renderable);
}

void FontRenderer::Render()
{
	renderList.Render();
}

bool FontRenderer::Empty()
{
	return renderList.Empty();
}

void FontRenderer::CopyNewValues()
{
	renderList.CopyNewValues();
}