#include "StdAfx.h"
#include "Semantics.h"

using namespace graphicsengine;
using namespace graphicsengine::implementation;
using namespace std;
using namespace stdext;

Semantics::Semantics(void)
{
	semanticLookup["world"] = World;
	semanticLookup["worldinverse"] = WorldInverse;
	semanticLookup["view"] = View;
	semanticLookup["viewinverse"] = ViewInverse;
	semanticLookup["worldview"] = WorldView;
	semanticLookup["worldviewinverse"] = WorldViewInverse;
	semanticLookup["worldviewprojection"] = WorldViewProjection;
	semanticLookup["worldviewparallel"] = WorldViewParallel;
	semanticLookup["color"] = Color;
	semanticLookup["texture0"] = Texture0;

	//sprite semantic setup
	semanticLookup["framewidth"] = FrameWidth;
	semanticLookup["framenumber"] = FrameNumber;

}

Semantics::~Semantics(void)
{
}
