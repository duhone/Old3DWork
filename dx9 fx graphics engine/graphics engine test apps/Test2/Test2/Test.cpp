#include "StdAfx.h"
#include "Test.h"
#include<sstream>

using namespace std;

Test::Test(HWND hwnd)
{
	graphicsEngine = IGraphicsEngine::getInstance();
	WindowSettings* setting = new WindowSettings();
	setting->hwnd = hwnd;
	setting->renderingQuality = 1;
	graphicsEngine->Initialize(setting);
	graphicsEngine->setBackgroundColor(0,0,0);
	graphicsEngine->LoadData("data.edf");
	
	fpsBlock = graphicsEngine->CreateTextBlock("stdblock");
	fpsBlock->SetLocation(-0.45f,-0.45f);
	fpsBlock->SetColor(1.0f,1.0f,1.0f,1.0f);
	fpsBlock->SetText("Frame Rate = 0.0fps");
	memBlock = graphicsEngine->CreateTextBlock("stdblock");
	memBlock->SetLocation(-0.1f,-0.45f);
	memBlock->SetColor(1.0f,1.0f,1.0f,1.0f);
	memBlock->SetText("Used Memory = 0meg");
	rotxBlock = graphicsEngine->CreateTextBlock("stdblock");
	rotxBlock->SetLocation(-0.6f,-0.4f);
	rotxBlock->SetColor(1.0f,1.0f,1.0f,1.0f);
	rotxBlock->SetText("Rotation around axis x, y, and z");

	rotxSprite = graphicsEngine->CreateSprite("photo");
	rotxSprite->SetPosition(-5,2,8);
	rotySprite = graphicsEngine->CreateSprite("photo");
	rotySprite->SetPosition(-3.5,2,8);
	rotzSprite = graphicsEngine->CreateSprite("photo");
	rotzSprite->SetPosition(-2.0,2,8);
	LARGE_INTEGER temp;
	QueryPerformanceFrequency(&temp);
	timerfreq = 1.0/temp.QuadPart;
	QueryPerformanceCounter(&starttime);
	QueryPerformanceCounter(&endtime);
	fpscount = 0;
}

Test::~Test(void)
{
	fpsBlock->Release();
	memBlock->Release();
	rotxBlock->Release();
	rotxSprite->Release();
	rotySprite->Release();
	rotzSprite->Release();
	graphicsEngine->Shutdown();
}

void Test::Iterate(void)
{
	fpscount++;
	if(fpscount >= 100)
	{
		QueryPerformanceCounter(&endtime);
		double fps = fpscount / ((endtime.QuadPart-starttime.QuadPart)*timerfreq);
		ostringstream tempstring;
		tempstring << "Frame Rate = " << fps << " fps";
		fpsBlock->SetText(tempstring.str());
		starttime = endtime;
		fpscount = 0;

		MEMORYSTATUSEX memstatus;
		memstatus.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&memstatus);
		ostringstream memstring;
		memstring << "Used Memory = " << (memstatus.ullTotalVirtual - memstatus.ullAvailVirtual)/(1024.0*1024.0) << " Meg";
		memBlock->SetText(memstring.str());
	}
	graphicsEngine->Commit();
}