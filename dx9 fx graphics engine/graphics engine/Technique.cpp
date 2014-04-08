#include "StdAfx.h"
#include "Technique.h"

using namespace graphicsengine;
using namespace graphicsengine::resources;

Technique::Technique(D3DXHANDLE handle,int quality,int preference,bool valid,int numPasses)
{
	this->quality = quality;
	this->preference = preference;
	this->handle = handle;
	this->valid = valid;
	this->numPasses = numPasses;
}

Technique::~Technique(void)
{
}

bool Technique::operator<(const Technique& other)
{
	if(this->valid && !other.valid)
		return true;
	else if(!this->valid && other.valid)
		return false;
	return preference > other.preference;
}

Technique::Technique(const Technique &technique)
{
	(*this) = technique;
}

void Technique::operator=(const Technique& technique)
{
	this->handle = technique.handle;
	this->quality = technique.quality;
	this->preference = technique.preference;
	this->valid = technique.valid;
}
