//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdlib.h>

#pragma hdrstop

#include "LESSON6.h"
#include "LESSON6LIB.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
HDC	hDC=NULL;		// Private GDI Device Context
HGLRC	hRC=NULL;		// Permanent Rendering Context
HWND	hWnd=NULL;		// Holds Our Window Handle

bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
int     mouse=0;





TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
   KillGLWindow(hRC,hDC,hWnd);
  ShowCursor(true);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    ShowCursor(false);
 
 

  hWnd = Handle;

  

    Width = GetSystemMetrics(SM_CXSCREEN);
    Height = GetSystemMetrics(SM_CYSCREEN);
    Top = 0;
    Left = 0;
  if(!CreateGLWindow(hWnd,&hDC,&hRC,Width,Height,16,&fullscreen))
     {
      _exit(1);


   }


}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

 PostQuitMessage(1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormResize(TObject *Sender)
{
 	ReSizeGLScene(ClientWidth,ClientHeight);  // LoWord=Width, HiWord=Height

}
//---------------------------------------------------------------------------




void __fastcall TForm1::FormActivate(TObject *Sender)
{


 active = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
  if(mouse>2) PostQuitMessage(1);
   else mouse++;    
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  MSG	msg;						// Windows Message Structure
  
  		if(true)/* && !DrawGLScene())/* || keys[VK_ESCAPE])*/	// Updating View Only If Active
			{
                DrawGLScene();
                SwapBuffers(hDC);				// Swap Buffers (Double Buffering)

		   /*		done=TRUE;					// ESC or DrawGLScene Signalled A Quit
			}
			else							// Not Time To Quit, Update Screen
			{
             SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
			}
		*/}
 while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
   if((msg.message == WM_SYSCOMMAND) && (msg.wParam == SC_MONITORPOWER))
    {
     Timer1->Enabled = false;
     /*if(!alreadyopen) KillGLWindow(false,hRC,hDC,hWnd);*/
     DispatchMessage(&msg);
     /*_exit(1);*/

    }
  }
}
//---------------------------------------------------------------------------

