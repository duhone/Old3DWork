//---------------------------------------------------------------------------
#ifndef LESSON6H
#define LESSON6H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TTimer *Timer1;
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
    
    void __fastcall FormResize(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Timer1Timer(TObject *Sender);
private:	// User declarations
public:		// User declarations
  /*  void __fastcall loop();*/
void __fastcall AppMessage(tagMSG &Msg, bool &Handled);

    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
