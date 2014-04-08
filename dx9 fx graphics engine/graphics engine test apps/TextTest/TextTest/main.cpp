#include<windows.h>
#include<stdlib.h>
#include<TCHAR.h>
#include "testtext.h"

bool done;
bool mouse_first = true;
unsigned int mousexi;
unsigned int mouseyi;
HWND hwndm;

LRESULT CALLBACK WndProcsaver(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
	  case WM_SYSCOMMAND:
		 if (wParam==SC_SCREENSAVE)
        {
          return FALSE;
        }
		 break;
		case WM_DESTROY:
			PostQuitMessage(0);
			done = true;
			return false;
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN: 
		case WM_RBUTTONDOWN: 
			case WM_KEYDOWN:

				PostQuitMessage(0);
				done = true;
				return false;
			case WM_MOUSEMOVE:
				if(mouse_first)
				{
					mouse_first = false;
					mousexi = LOWORD(lParam);
					mouseyi = HIWORD(lParam);
				}
				else
				{
					if(abs((long)((LOWORD(lParam) - mousexi) > 150) || (abs((long)(HIWORD(lParam) - mouseyi)) > 150)))			
					{
						PostQuitMessage(0);
						done = true;
					}
				}

	};
	return DefWindowProc(hwnd,message,wParam,lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{

	done = false;
	srand(GetTickCount());
	MSG msg;

	int width = GetSystemMetrics(SM_CXSCREEN); 
	int height = GetSystemMetrics(SM_CYSCREEN);

 	WNDCLASS wc;
	wc.style = 0;
	wc.lpfnWndProc = WndProcsaver;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance,NULL/*MAKEINTRESOURCE(IDI_ICON1)*/);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("STARS V4EXE");
	RegisterClass(&wc);

	hwndm = CreateWindowEx(0/*WS_EX_TOPMOST*/,_T("STARS V4EXE"),NULL,WS_POPUP,0,0,width,height,NULL,NULL,hInstance,NULL);
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	ShowWindow(hwndm,SW_SHOW);
	SetFocus(hwndm);
	
	ShowCursor(false);
	
	TestText *test = new TestText(hwndm);

	
	while(!done)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		test->Iterate();
	}
	delete test;
	ShowCursor(true);
	return 0;
}
