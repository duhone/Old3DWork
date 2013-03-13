#include "graphics.h"
#include "GraphicsEngine.h"


HWND hwnd;
HINSTANCE hinstance;
extern GraphicsEngine *gengine;

GraphicsEngine* GetGraphicsEngine()
{
	if(gengine == NULL)
	{
		gengine = new GraphicsEngine();
	}
//	gengine->AddRef();
	return gengine;
}

// This is the constructor of a class that has been exported.
// see HPT Graphics.h for the class definition

void HPTSetWindow(HINSTANCE hins,HWND arg)
{
	hinstance = hins;
	hwnd = arg;
}