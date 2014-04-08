//---------------------------------------------------------------------------
#ifndef selectpicsH
#define selectpicsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <registry.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
    TOpenDialog *OpenDialog1;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TStaticText *StaticText1;
    TStaticText *StaticText2;
    TStaticText *StaticText3;
    TStaticText *StaticText4;
    TStaticText *StaticText5;
    TStaticText *StaticText6;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit5;
    TEdit *Edit6;
    TImage *Image1;
    TImage *Image2;
    TImage *Image3;
    TImage *Image4;
    TImage *Image5;
    TImage *Image6;
    TStaticText *StaticText7;
    TButton *Button7;
    TButton *Button8;
    TButton *Button9;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TButton *Button10;
    TScrollBar *ScrollBar1;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
    void __fastcall Button5Click(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall Button8Click(TObject *Sender);
   // void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall Button9Click(TObject *Sender);
    
 //   void __fastcall ScrollBar1Change(TObject *Sender);
    void __fastcall ScrollBar1Scroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall CheckBox1Click(TObject *Sender);
    void __fastcall CheckBox2Click(TObject *Sender);
private:	// User declarations
    AnsiString  names[6];
    TPicture *   temppic[6];
    int speed;
    TRegistry *reg;
    bool stretch;
    bool hirestex;
public:		// User declarations
    __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
