#include "StdAfx.h"
#include "TextBlockRenderer.h"
#include "Font.h"
#include "Textblock.h"
#include "IGraphicsEngine.h"
#include "GraphicsEngine.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;
using namespace graphicsengine::renderables;
using namespace graphicsengine::resources;
using namespace graphicsengine::renderers;
using namespace stdext;

TextBlockRenderer::TextBlockRenderer(void) : IRenderer(IRenderer::TEXT_BLOCK)
{
}

TextBlockRenderer::~TextBlockRenderer(void)
{
}
	
void TextBlockRenderer::AddRenderable(graphicsengine::renderables::Renderable* renderable,
				graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
{
	TextBlock* text = dynamic_cast<TextBlock*>(renderable);
	renderList.AddRenderable((Font*)text->GetFont(),text,plan,effect);
}

void TextBlockRenderer::RemoveRenderable(graphicsengine::renderables::Renderable* renderable)
{
	TextBlock* text = dynamic_cast<TextBlock*>(renderable);
	renderList.RemoveRenderable((Font*)text->GetFont(),text);
}

void TextBlockRenderer::Render()
{
	renderList.Render();
}

bool TextBlockRenderer::Empty()
{
	return renderList.Empty();
}


void TextBlockRenderer::CopyNewValues()
{	
	renderList.CopyNewValues();
}	