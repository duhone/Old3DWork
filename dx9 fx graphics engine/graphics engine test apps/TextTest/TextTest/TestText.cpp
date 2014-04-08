#include "TestText.h"
#include<sstream>

using namespace std;

TestText::TestText(HWND hwnd)
{
	graphicsEngine = IGraphicsEngine::getInstance();
	WindowSettings* setting = new WindowSettings();
	setting->hwnd = hwnd;
	setting->renderingQuality = 1;
	graphicsEngine->Initialize(setting);
	graphicsEngine->setBackgroundColor(0,0.2f,0);
	graphicsEngine->LoadData("data.edf");
	fpsBlock = graphicsEngine->CreateTextBlock("statblock");
	fpsBlock->SetLocation(-0.45f,-0.45f);
	fpsBlock->SetColor(1.0f,1.0f,1.0f,1.0f);
	fpsBlock->SetText("Frame Rate = 0.0fps");
	memBlock = graphicsEngine->CreateTextBlock("statblock");
	memBlock->SetLocation(-0.1f,-0.45f);
	memBlock->SetColor(1.0f,1.0f,1.0f,1.0f);
	memBlock->SetText("Used Memory = 0meg");
	IFont* bigfont = graphicsEngine->GetFont("bigfont");
	bigText = graphicsEngine->CreateTextBlock("statblock");
	bigText->SetFont(bigfont);
	bigText->SetLocation(0,0);
	bigText->SetColor(1.0f,1.0f,0.0f,1.0f);
	bigText->SetText("Large Font");
	anchorTLText = graphicsEngine->CreateTextBlock("anchorblock");
	anchorTLText->SetLocation(0.01f,0.01f);
	anchorTLText->SetColor(1.0f,0.0f,1.0f,1.0f);
	//anchorTLText->SetText("Used Memory = 0meg");
	anchorBRText = graphicsEngine->CreateTextBlock("anchorblock");
	anchorBRText->SetColor(0.0f,1.0f,1.0f,1.0f);
	anchorBRText->SetText("Anchored bottom right");
	anchorBRText->SetAnchor(ITextBlock::ANCHOR_BOTTOM | ITextBlock::ANCHOR_RIGHT);
	anchorBRText->SetLocation(-0.25f,-0.05f);
	transText = graphicsEngine->CreateTextBlock("statblock");
	transText->SetLocation(-0.2f,-0.01f);
	transText->SetColor(1.0f,0.0f,0.0f,0.5f);
	transText->SetText("Alpha Blended text");
	transText->SetFont(bigfont);
	bigfont->Release();
	paraText = graphicsEngine->CreateTextBlock("statblock");
	paraText->SetLocation(-0.2f,-0.31f);
	paraText->SetColor(0.0f,0.0f,1.0f,1.0f);
	paraText->SetText("text\nwith\nline\nbreaks");
	moveText = graphicsEngine->CreateTextBlock("statblock");
	moveText->SetLocation(-0.5f,-0.5f);
	moveText->SetColor(0.0f,1.0f,0.0f,1.0f);
	moveText->SetText("Moving Text");
	moveText2 = graphicsEngine->CreateTextBlock("statblock");
	moveText2->SetLocation(0.5f,-0.5f);
	moveText2->SetColor(1.0f,0.0f,0.0f,1.0f);
	moveText2->SetText("Slow Moving Text\nwith line breaks\nA paragraph");

	LARGE_INTEGER temp;
	QueryPerformanceFrequency(&temp);
	timerfreq = 1.0/temp.QuadPart;
	QueryPerformanceCounter(&starttime);
	QueryPerformanceCounter(&endtime);
	fpscount = 0;

	textx = graphicsEngine->GetAspectRatio()/-2.0f;
	texty = -0.5f;
	swidth = graphicsEngine->GetAspectRatio()/2.0f;
	xv = 0.002f;
	yv = 0.002f;

	textx2 = graphicsEngine->GetAspectRatio()/2.0f - 0.2f;
	texty2 = 0.4f;
	xv2 = 0.0005f;
	yv2 = 0.0005f;

}

TestText::~TestText(void)
{
	graphicsEngine = IGraphicsEngine::getInstance();
	fpsBlock->Release();
	memBlock->Release();
	bigText->Release();
	anchorTLText->Release();
	anchorBRText->Release();
	transText->Release();
	paraText->Release();
	moveText->Release();
	moveText2->Release();

	graphicsEngine->Shutdown();
}

void TestText::Iterate(void)
{
	textx += xv;
	texty += yv;
	
	if(xv > 0 && textx>swidth)
		xv = -xv;
	else if(xv < 0 && textx<-swidth)
		xv = -xv;
	if(yv > 0 && texty>0.5f)
		yv = -yv;
	else if(yv < 0 && texty<-0.5f)
		yv = -yv;

	moveText->SetLocation(textx,texty);

	textx2 += xv2;
	texty2 += yv2;
	
	if(xv2 > 0 && textx2>swidth)
		xv2 = -xv2;
	else if(xv2 < 0 && textx2<-swidth)
		xv2 = -xv2;
	if(yv2 > 0 && texty2>0.5f)
		yv2 = -yv2;
	else if(yv2 < 0 && texty2<-0.5f)
		yv2 = -yv2;

	moveText2->SetLocation(textx2,texty2);


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
