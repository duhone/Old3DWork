#pragma once
#include"../../../graphics engine/IGraphicsEngine.h"
#include"../../../graphics engine/ITextBlock.h"
#include"../../../graphics engine/ISprite.h"

using namespace graphicsengine;


class Test
{
private:
	IGraphicsEngine* graphicsEngine;
	ITextBlock* fpsBlock;
	ITextBlock* memBlock;
	ITextBlock* rotxBlock;
	ISprite* rotxSprite;
	ISprite* rotySprite;
	ISprite* rotzSprite;

	LARGE_INTEGER starttime;
	LARGE_INTEGER endtime;
	double timerfreq;
	int fpscount;
public:
	Test(HWND hwnd);
public:
	virtual ~Test(void);
	void Iterate(void);
};
