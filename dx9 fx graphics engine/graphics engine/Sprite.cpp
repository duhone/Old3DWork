#include "StdAfx.h"
#include "Sprite.h"
#include "Texture.h"
#include "Frameset.h"
#include "ResourceManager.h"
#include ".\graphicsengine.h"
#include "FrameSetPrototype.h"
#include "Effect.h"
#include "ObjectExecutionPlan.h"

using namespace std;
using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace graphicsengine::renderables;
using namespace graphicsengine::manager;
using namespace graphicsengine::implementation;
using namespace graphicsengine::renderers;
using namespace std;
using namespace stdext;

#include "SpriteExecutionPlans.h"

Sprite::Sprite(graphicsengine::resources::SpritePrototype *prototype) :
Renderable()
{
	visible = true;
	newVisible = true;
	this->prototype = prototype;
	prototype->AddRef();
	x = 0;
	y = 0;
	z = 1;
	newx = 0;
	newy = 0;
	newz = 0;
	scalex = 0;
	scaley = 0;
	alpha = prototype->GetAlpha();
	ResourceManager* manager = ((GraphicsEngine*)IGraphicsEngine::getInstance())->GetResourceManager();
	vector<FrameSetPrototype*>* frameProts = prototype->GetFrameSets();

	for(unsigned int i = 0; i <frameProts->size();i++)
	{
		FrameSetPrototype* fprot = (*frameProts)[i];
		Texture* texture = manager->GetTexture(*fprot->GetTexture());
		Effect* effect = manager->GetEffect(*fprot->GetEffect());
		FrameSet* frameSet = new FrameSet(fprot->GetName(),texture,effect,fprot->GetFrameWidth(),fprot->GetFPS());
		framesets[*(fprot->GetName())] = frameSet;
		if(i == 0)
		{
			frame = *fprot->GetName();
			newFrame = frame;
			currentframeSet = frameSet;
		}
	}

	D3DXMatrixTranslation(&translation,x,y,z);
	D3DXMatrixScaling(&scaling,1,1,1);
	D3DXMatrixIdentity(&newRotation);
	newUp.x = 0;
	newUp.y = 1;
	newUp.z = 0;
	newForward.x = 0;
	newForward.y = 0;
	newForward.z = 1;
	newSide.x = 1;
	newSide.y = 0;
	newSide.z = 0;

	newColor.x = 1;
	newColor.y = 1;
	newColor.z = 1;
	newColor.w = 1;
	animate = false;
	plan = NULL;
}

Sprite::~Sprite(void)
{
	if(this->plan != NULL)
		delete this->plan;
	prototype->SubRef();
	hash_map<std::string,FrameSet*>::iterator iterator = framesets.begin();
	while(iterator != framesets.end())
	{
		delete iterator->second;
		iterator++;
	}
	framesets.clear();
}

void graphicsengine::renderables::Sprite::SetPosition(float x, float y,float z)
{
	newx = x - this->x;
	newy = y - this->y;
	newz = z - this->z;
}

void Sprite::CopyNewValues()
{
	visible = newVisible;
	rotation = newRotation;
	up = newUp;
	forward = newForward;
	side = newSide;
	if(newx != 0 || newy != 0 || newz != 0)
	{
		x += newx;
		y += newy;
		z += newz;
		newx = 0;
		newy = 0;
		newz = 0;
		D3DXMatrixTranslation(&translation,x,y,z);
	}
	if(scalex != 0 || scaley != 0)
	{
		D3DXMatrixScaling(&scaling,scalex,scaley,1);
		scalex = 0;
		scaley = 0;
	}

	D3DXMatrixMultiply(&world,&rotation,&scaling);
	D3DXMatrixMultiply(&world,&world,&translation);

	color = newColor;
	if(frame != newFrame)
	{
		renderManager->MoveRenderable(this);
		moveFrame = newFrame;
	}
	if(animate)
		currentframeSet->Animate(((GraphicsEngine*)IGraphicsEngine::getInstance())->Time());
	vector<pair<string,D3DXVECTOR4> >::iterator customSemIterator = newCustomSemantics.begin();
	while(customSemIterator != newCustomSemantics.end())
	{
		hash_map<string,D3DXVECTOR4>::iterator semIter = customSemantics.find(customSemIterator->first);
		if(semIter != customSemantics.end())
		{
			semIter->second = customSemIterator->second;
		}
		customSemIterator++;
	}
	newCustomSemantics.clear();
}


void Sprite::ReadyToMove()
{
	currentframeSet = framesets[moveFrame];
	frame = moveFrame;
	currentframeSet->InitAnimation();
}

void Sprite::AssignToRenderManager(void)
{
	renderManager->AddRenderable(this);
}

Texture* Sprite::GetCurrentTexture()
{
	return currentframeSet->texture;
}

void Sprite::SetFrameSet(std::string set)
{
	newFrame = set;
}

string Sprite::GetCurrentFrameSet()
{
	return currentframeSet->name;
}

void graphicsengine::renderables::Sprite::Move(float x, float y, float z)
{
	newx += x;
	newy += y;
	newz += z;
}

void graphicsengine::renderables::Sprite::SetScale(float x, float y)
{
	scalex = x;
	scaley = y;
}

void Sprite::SetCustomParameter(const string& parameter,float x,float y,float z,float w)
{
	newCustomSemantics.push_back(pair<string,D3DXVECTOR4>(parameter,D3DXVECTOR4(x,y,z,w)));
}

void graphicsengine::renderables::Sprite::ResetRotation(void)
{
	D3DXMatrixIdentity(&newRotation);
	newUp.x = 0;
	newUp.y = 1;
	newUp.z = 0;
	newForward.x = 0;
	newForward.y = 0;
	newForward.z = 1;
	newSide.x = 1;
	newSide.y = 0;
	newSide.z = 0;
}

void graphicsengine::renderables::Sprite::RotateX(float angle)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationAxis(&temp,&newSide,angle);
	D3DXMatrixMultiply(&newRotation,&newRotation,&temp);
	D3DXVec3TransformCoord(&newForward,&newForward,&temp);
	D3DXVec3TransformCoord(&newUp,&newUp,&temp);
}

void graphicsengine::renderables::Sprite::RotateY(float angle)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationAxis(&temp,&newUp,angle);
	D3DXMatrixMultiply(&newRotation,&newRotation,&temp);
	D3DXVec3TransformCoord(&newForward,&newForward,&temp);
	D3DXVec3TransformCoord(&newSide,&newSide,&temp);
}

void graphicsengine::renderables::Sprite::RotateZ(float angle)
{
	D3DXMATRIX temp;
	D3DXMatrixRotationAxis(&temp,&newForward,angle);
	D3DXMatrixMultiply(&newRotation,&newRotation,&temp);
	D3DXVec3TransformCoord(&newSide,&newSide,&temp);
	D3DXVec3TransformCoord(&newUp,&newUp,&temp);
}
void graphicsengine::renderables::Sprite::SetColor(float red, float green, float blue, float alpha)
{
	newColor.x = red;
	newColor.y = green;
	newColor.z = blue;
	newColor.w = alpha;
}

void graphicsengine::renderables::Sprite::Animate(bool animate)
{
	this->animate = animate;
}

IRenderer::RendererType Sprite::GetRenderer()
{
	return IRenderer::SPRITE;
}

Effect* graphicsengine::renderables::Sprite::GetEffect(void)
{
	return currentframeSet->GetEffect();;
}


void Sprite::Render()
{
	if(!visible)
		return;
	plan->Execute();
	((GraphicsEngine*)IGraphicsEngine::getInstance())->getD3DDevice()->DrawPrimitive(D3DPT_TRIANGLEFAN,0,2);
}

void Sprite::BuildExecutionPlan(graphicsengine::renderables::ObjectExecutionPlan* plan,graphicsengine::resources::Effect* effect)
{
	if(this->plan != NULL)
		delete this->plan;
	this->plan = plan;
	
	const std::vector<graphicsengine::implementation::Semantics::SEMANTICS> availSemantics = effect->GetAvailableSemantics();
	for_each(availSemantics.begin(),availSemantics.end(),ExecutionPlanBuilder(plan,effect,this));

	customSemantics.clear();
	const hash_map<string,D3DXHANDLE>& availCustomSemantics = effect->GetCustomSemantics();
	hash_map<string,D3DXHANDLE>::const_iterator iterator = availCustomSemantics.begin();
	while(iterator != availCustomSemantics.end())
	{
		customSemantics[iterator->first] = D3DXVECTOR4(0,0,0,0);
		plan->AddExecute(new CustomExecutePlan(effect,iterator->second,&customSemantics[iterator->first]));
		iterator++;
	}

	plan->AddExecute(new CommitExecutePlan(effect));
	
}

const Resource* const Sprite::GetResource(void) const
{
	return currentframeSet->texture;
}
