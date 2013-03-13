// Stars v4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "graphics.h"
#include <list>
#include<stdlib.h>
#include<math.h>
#include"GraphicsEngine.h"
#include "Object.h"

using namespace std;

GraphicsEngine *gengine = NULL;
HWND hwndm;
int width;
int height;
bool done;
Object *tempobject;

LARGE_INTEGER timerfreq;
LARGE_INTEGER starttime;
LARGE_INTEGER currenttime;	
float speed = 20000.0f;
float full_speed = 20000.0f;

float speedx = 20000.0f;
float full_speedx = 20000.0f;
float speedy = 20000.0f;
float full_speedy = 20000.0f;

char path[255];
   
int nframes = 0;
float time_elapsed = 0;
float frame_rate = 0;
int framecounteryn;
bool mouse_first = true;
unsigned int mousexi;
unsigned int mouseyi;
float noisep;
int mode = 1;
float rotation_angle = 0;

bool check_input = false;
bool ldown = false;
bool rdown = false;

int temperature = 5800;
bool increase_temp = false;
bool decrease_temp = false;

char *hptstrcat(char *x,char *y)
{
	static char *temp_string = NULL;
	if(temp_string != NULL) delete[] temp_string;
	temp_string = new TCHAR[300];
	strcpy(temp_string,x);
	strcat(temp_string,y);
	return temp_string;
}


void SetBrightness()
{
	float red,green,blue;
	red = (33.59695)/(exp((20.55384e3)/temperature)-1);
	green = (92.99935)/(exp((26.35107e3)/temperature)-1);
	blue = (298.64856)/(exp((33.07514e3)/temperature)-1);
	float magnitude = sqrt(red*red+green*green+blue*blue);
	float range = temperature-2000;
	range /= 8000;
	range *= 2.5f;
	range -= 1.25f;
	range += 1.7f;
	red = range/magnitude;
	green = range/magnitude;
	blue = range/magnitude;
	tempobject->SetBrightness(red,green,blue);
}

LRESULT CALLBACK WndProcsaver(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	  case WM_SYSCOMMAND:
	case WM_DESTROY:
			PostQuitMessage(0);
			done = true;
			return false;
	case WM_KEYDOWN:
		if(wParam == VK_UP) 
		{
			mode++;
			if(mode > 1) mode = 0;
		}
		else if(wParam == VK_DOWN)
		{
			mode--;
			if(mode < 0) mode = 1;
		}
		else if(wParam == VK_LEFT)
		{
			ldown = true;	
		}
		else if(wParam == VK_RIGHT)
		{
			rdown = true;
		}
		else if(wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			done = true;
		}
		else if(wParam == 'Q')
		{
			increase_temp = true;		
		}
		else if(wParam == 'A')
		{
			decrease_temp = true;
		}
		else if(wParam == 'U')
		{
			tempobject->SetUV(!tempobject->GetUV());;
		}
		return false;

	case WM_KEYUP:
			if(wParam == VK_LEFT)
			{
				ldown = false;	
			}
			else if(wParam == VK_RIGHT)
			{
				rdown = false;
			}
			else if(wParam == 'Q')
			{
				increase_temp = false;		
			}
			else if(wParam == 'A')
			{
				decrease_temp = false;
			}

	};
	return DefWindowProc(hwnd,message,wParam,lParam);
}


void Iterate()
{
	float timepassed;
	QueryPerformanceCounter(&currenttime);
	timepassed = (currenttime.QuadPart - starttime.QuadPart)/(float)timerfreq.QuadPart;
	starttime.QuadPart = currenttime.QuadPart;
	noisep += timepassed*.01f;
	if(ldown) rotation_angle -= timepassed*0.2f;
	if(rdown) rotation_angle += timepassed*0.2f;
	if(increase_temp)
	{
		temperature += 200*timepassed;
		if(temperature > 10000) temperature = 10000;
	}
	if(decrease_temp)
	{
		temperature -= 200*timepassed;
		if(temperature < 2000) temperature = 2000;
	}
	SetBrightness();
	
	tempobject->SetTemperature(temperature);
	tempobject->Position(20,0,150);
	tempobject->Rotate(rotation_angle,0);
	gengine->SetTime(timepassed);
	tempobject->AnimateTemperatureMap();
	gengine->BeginFrame();
	switch(mode)
	{
	case 0:
		tempobject->RenderHeat();
		break;
	case 1:
		tempobject->Render();
		break;
	};

	nframes++;
	time_elapsed += timepassed;
	if(nframes > 100)
	{
		if(time_elapsed <= 0) time_elapsed = 0.000001f;
		frame_rate = nframes/time_elapsed;
		nframes = 0;
		time_elapsed = 0;

	}
	char tempstring[30];
	sprintf(tempstring,"Frame rate is %f",frame_rate);

	gengine->Position(0,0) << tempstring;

	switch(mode)
	{
	case 0:
		sprintf(tempstring,"Temperature Map");
		break;
	case 1:
		sprintf(tempstring,"Plank Star");
		break;
	};
	
	gengine->Position(0,30);
	(*gengine) << tempstring;

	sprintf(tempstring,"Temperature is %dK",temperature);
	gengine->Position(0,50) << tempstring;
	if(tempobject->GetUV()) gengine->Position(0,70) << "UV Spectrum(100nm) mapped to green";
	else gengine->Position(0,70) << "Visible spectrum";	
	gengine->Position(0,100) << "  Q- increase temperature";
	gengine->Position(0,120) << "  A- Decrease temperature";
	gengine->Position(0,140) << "  U- Toggle Visible/UV spectrum";
	gengine->Position(0,160) << "  Up Arrow Next Effect";
	gengine->Position(0,180) << "  Down Arrow Previous Effect";
	gengine->Position(0,200) << "  Left Arrow, Rotate Star Left";
	gengine->Position(0,220) << "  Right Arrow, Rotate Star Right";
	gengine->EndFrame();

}


			
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	OutputDebugString("start stars");

	
	GetModuleFileName(NULL,path,256);
	path[_tcslen(path) - 12] = 0;
		done = false;
	srand(GetTickCount());
	MSG msg;


	check_input = true;
	SystemParametersInfo(SPI_SETSCREENSAVERRUNNING,TRUE,0,0);
	width = GetSystemMetrics(SM_CXSCREEN); 
	height = GetSystemMetrics(SM_CYSCREEN);

 	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProcsaver;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,NULL);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("STAR EXE");
	RegisterClass(&wc);

	hwndm = CreateWindowEx(0,_T("STAR EXE"),NULL,WS_POPUP,0,0,width,height,NULL,NULL,hInstance,NULL);
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	ShowWindow(hwndm,SW_SHOW);
	SetFocus(hwndm);
		
	ShowCursor(false);

	HPTSetWindow(hInstance,hwndm);

  	gengine = GetGraphicsEngine();
	gengine->BeginFrame();
	gengine->Position(0.4f*width,0.4f*height);
	(*gengine) << "Loading Star Shader";
	gengine->EndFrame();

	OutputDebugString("init window");



	noisep = 0;
	tempobject = gengine->CreateObject();
	tempobject->Scale(50);
	tempobject->Position(1000,-50,2000);
	tempobject->Rotate(1.5f,0.5f);
	tempobject->SetTemperature(5800);



	QueryPerformanceFrequency(&timerfreq);
	QueryPerformanceCounter(&starttime);

	OutputDebugString("begin loop");
		while(!done)
		{
			Iterate();
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	gengine->Release();

	ShowCursor(true);

	return 0;
}



