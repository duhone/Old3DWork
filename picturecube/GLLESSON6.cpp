//---------------------------------------------------------------------------
#include <vcl.h>
//#include "selectpics.h"
#pragma hdrstop
USERES("GLLESSON6.res");
USEFORM("LESSON6.cpp", Form1);
USEUNIT("LESSON6LIB.cpp");
USEUNIT("Image.c");
USEUNIT("Tk.c");
USEUNIT("Tkimage.c");
USEUNIT("Tkdib.c");
USEFORM("selectpics.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
 HANDLE mutex;
 char name[12] = "picturecube";
 name[11] = 0;
 mutex = CreateMutex(NULL,TRUE,name);
 if(GetLastError() != ERROR_ALREADY_EXISTS)
  {
    try
    {
  /*      Application->Initialize();
   */      Application->Title = "SCRNSAVE:INEZ.SCR";
    if((LowerCase(ParamStr(1)) == "/s"))
 {
   Application->Initialize();
   //   Application->CreateForm(__classid(TForm2), &Form2);
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();
  }
  else{
   if((LowerCase(ParamStr(1)) == "/p"))
    {
    }
    else
    {
      if((LowerCase(ParamStr(1)) == "/c"))
    {
    }
    else
    {
        Application->Initialize();
      Application->CreateForm(__classid(TForm2), &Form2);
   //     Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();

    }

    }
  }

    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
 }
    return 0;
}
//---------------------------------------------------------------------------
