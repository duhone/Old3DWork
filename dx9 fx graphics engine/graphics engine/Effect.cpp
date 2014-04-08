#include "StdAfx.h"
#include "Effect.h"
#include "Technique.h"
#include "GraphicsEngine.h"
#include "Renderable.h"
#include <sstream>

using namespace graphicsengine;
using namespace graphicsengine::resources;
using namespace std;
using namespace stdext;
using namespace graphicsengine::renderables;
using namespace graphicsengine::implementation;

Effect::Effect(IDirect3DDevice9* d3d_device) :
Resource(d3d_device)
{
	effect = NULL;
}

Effect::~Effect(void)
{
	if(RefCount() > 0) FreeResource();
}

void graphicsengine::resources::Effect::BuildResource(void)
{
	ResetFile();
	int compressedSize = this->GetInt();
	int decompressedSize = this->GetInt();
    LPD3DXBUFFER errors;
	char* data = this->GetCompressedData(compressedSize,decompressedSize);
	D3DXCreateEffect(this->d3d_device, data,decompressedSize,NULL,NULL,0,NULL,&effect,&errors);

	if(errors != NULL && errors->GetBufferSize() > 0)
		MessageBox(NULL,(char*)errors->GetBufferPointer(),"Could not build effect",MB_OK);
	if(errors != NULL)
		errors->Release();
	D3DXEFFECT_DESC desc;
	effect->GetDesc(&desc);
	int highestQuality = 0;
	hash_map<int,vector<Technique> > buildTable;
	for(unsigned int i=0;i < desc.Techniques;i++)
	{
		D3DXHANDLE tech = effect->GetTechnique(i);
		D3DXTECHNIQUE_DESC techDesc;
		effect->GetTechniqueDesc(tech,&techDesc);
		int numPasses = techDesc.Passes;
		if(techDesc.Name[0] != 'q')
			return;
		int j = 1;
		int quality = 0;
		while(techDesc.Name[j] != '_')
		{
			quality = 10*quality + techDesc.Name[j]-'0';
			j++;
		}
		j++;
		int preference = 0;
		while(techDesc.Name[j] != '_')
		{
			preference = 10*preference + techDesc.Name[j]-'0';
			j++;
		}
		if(quality > highestQuality)
			highestQuality = quality;
		hash_map<int,vector<Technique> >::iterator foundList = buildTable.find(quality);
		if(foundList == buildTable.end())
		{
			buildTable[quality];
			foundList = buildTable.find(quality);
		}
		bool valid = effect->ValidateTechnique(tech) == D3D_OK;
		foundList->second.push_back(Technique(tech,quality,preference,valid,numPasses));
	}
	hash_map<int,vector<Technique> >::iterator iterator = buildTable.begin();
	while(iterator != buildTable.end())
	{
		sort(iterator->second.begin(),iterator->second.end());
		iterator++;
	}

	GENGINE->RegisterQualityChangeObserver(this);
	Technique* last = NULL;
	for(int i=0;i < highestQuality;i++)
	{
		hash_map<int,vector<Technique> >::iterator foundList = buildTable.find(i);
		if(foundList != buildTable.end())
		{
			if(!foundList->second[0].Valid())
			{
				GENGINE->MarkQualityAsInvalid(i);
				break;
			}
			unsigned int j = 0;
			while(j < foundList->second.size() && foundList->second[j].Valid())
				j++;
			j--;//move to last valid;
			techniques.push_back(new Technique(foundList->second[j]));
			last = techniques[i];
		}
		else
			techniques.push_back(last);
	}
	BuildParameters(desc);
}

void graphicsengine::resources::Effect::FreeResource(void)
{
	if(effect != NULL)
		effect->Release();
	effect = NULL;
}

void graphicsengine::resources::Effect::Release(void)
{
	this->SubRef();
}

void graphicsengine::resources::Effect::QualityChanged(int newQuality)
{
	current = techniques[newQuality];
}

void graphicsengine::resources::Effect::BuildParameters(D3DXEFFECT_DESC desc)
{
	for(int i = 0;i < desc.Parameters;i++)
	{
		D3DXHANDLE handle = effect->GetParameter(NULL,i);
		D3DXPARAMETER_DESC paramDesc;
		effect->GetParameterDesc(handle,&paramDesc);
		if(paramDesc.Semantic == NULL)
			continue;
		string paramSemantic = paramDesc.Semantic;
		DWORD flags = paramDesc.Flags;
		if(flags && D3DX_PARAMETER_ANNOTATION || flags && D3DX_PARAMETER_LITERAL)
			continue;
		if(flags && D3DX_PARAMETER_SHARED)
		{
			stringstream error;
			error << "Shared effect parameters not supported. Effect name: " << this->name 
				<< " Parameter Name: " << paramDesc.Name;
			MessageBox(NULL,error.str().c_str(),"Error",MB_OK);
		}

		D3DXPARAMETER_CLASS paramClass = paramDesc.Class;
		Semantics::SEMANTICS semanticEnum = Semantics::Instance()->LookupSemantic(paramSemantic);
		if(semanticEnum != Semantics::Custom)
		{
			semantics.push_back(semanticEnum);
			semanticLookup[semanticEnum] = handle;
		}
		else
			customSemanticLookup[paramSemantic] = handle;
	}
}

D3DXHANDLE Effect::GetHandleForSemantic(Semantics::SEMANTICS semantic)
{
	hash_map<Semantics::SEMANTICS,D3DXHANDLE>::iterator iterator = semanticLookup.find(semantic);
	if(iterator == semanticLookup.end())
		return NULL;
	return (*iterator).second;
}

void Effect::SetTexture(D3DXHANDLE handle,Texture* texture)
{
	effect->SetTexture(handle,texture->GetTexture());
}

void Effect::SetMatrix(D3DXHANDLE handle,const D3DXMATRIX* matrix)
{
	effect->SetMatrix(handle,matrix);
}

void Effect::SetInt(D3DXHANDLE handle,int arg)
{
	effect->SetInt(handle,arg);
}

void Effect::SetFloat(D3DXHANDLE handle,float arg)
{
	effect->SetFloat(handle,arg);
}

void Effect::SetVector(D3DXHANDLE handle,const D3DXVECTOR4 *arg)
{
	effect->SetVector(handle,arg);
}

void Effect::CommitChanges()
{
	effect->CommitChanges();
}

int Effect::NumPasses() const
{
	return current->NumPasses();
}