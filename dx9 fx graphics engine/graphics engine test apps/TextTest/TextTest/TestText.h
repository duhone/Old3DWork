#pragma once

#include"../../../graphics engine/IGraphicsEngine.h"
#include"../../../graphics engine/IFont.h"
#include"../../../graphics engine/ITextBlock.h"

using namespace graphicsengine;

class TestText
{
private:
	IGraphicsEngine* graphicsEngine;
	ITextBlock* fpsBlock;
	ITextBlock* memBlock;
	ITextBlock* bigText;
	ITextBlock* anchorTLText;
	ITextBlock* anchorBRText;
	ITextBlock* transText;
	ITextBlock* paraText;
	ITextBlock* moveText;
	ITextBlock* moveText2;

	LARGE_INTEGER starttime;
	LARGE_INTEGER endtime;
	double timerfreq;
	int fpscount;
	float textx;
	float texty;
	float xv;
	float yv;
	float swidth;
	float textx2;
	float texty2;
	float xv2;
	float yv2;

public:
	TestText(HWND hwnd);
public:
	~TestText(void);
public:
	void Iterate(void);
};
