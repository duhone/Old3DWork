//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "selectpics.h"
#include "jpeg.hpp"
#include "registry.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
    reg = new TRegistry;
    temppic[0] = new TPicture;
    temppic[1] = new TPicture;
    temppic[2] = new TPicture;
    temppic[3] = new TPicture;
    temppic[4] = new TPicture;
    temppic[5] = new TPicture;
  reg->OpenKey("software",true);
  reg->OpenKey("picube",true);
  //reg->OpenKey("pic1",true);

  names[0] = reg->ReadString("pic1");
  if((names[0] == NULL) || (names[0] == ""))
   {
    names[0] == "";
   }
  else
   {
     Edit1->Text = names[0];
   temppic[0]->LoadFromFile(names[0]);
   dynamic_cast<TJPEGImage *>(temppic[0]->Graphic);
   Image1->Picture = temppic[0];
   }

  names[1] = reg->ReadString("pic2");
  if((names[1] == NULL) || (names[1] == ""))
   {
    names[1] == "";
   }
  else
   {
     Edit2->Text = names[1];
   temppic[1]->LoadFromFile(names[1]);
   dynamic_cast<TJPEGImage *>(temppic[1]->Graphic);
   Image2->Picture = temppic[1];
   }

  names[2] = reg->ReadString("pic3");
  if((names[2] == NULL) || (names[2] == ""))
   {
    names[2] == "";
   }
  else
   {
     Edit3->Text = names[2];
   temppic[2]->LoadFromFile(names[2]);
   dynamic_cast<TJPEGImage *>(temppic[2]->Graphic);
   Image3->Picture = temppic[2];
   }

  names[3] = reg->ReadString("pic4");
  if((names[3] == NULL) || (names[3] == ""))
   {
    names[3] == "";
   }
  else
   {
     Edit4->Text = names[3];
   temppic[3]->LoadFromFile(names[3]);
   dynamic_cast<TJPEGImage *>(temppic[3]->Graphic);
   Image4->Picture = temppic[3];
   }

  names[4] = reg->ReadString("pic5");
  if((names[4] == NULL) || (names[4] == ""))
   {
    names[4] == "";
   }
  else
   {
     Edit5->Text = names[4];
   temppic[4]->LoadFromFile(names[4]);
   dynamic_cast<TJPEGImage *>(temppic[4]->Graphic);
   Image5->Picture = temppic[4];
   }

  names[5] = reg->ReadString("pic6");
  if((names[5] == NULL) || (names[5] == ""))
   {
    names[5] == "";
   }
  else
   {
     Edit6->Text = names[5];
   temppic[5]->LoadFromFile(names[5]);
   dynamic_cast<TJPEGImage *>(temppic[5]->Graphic);
   Image6->Picture = temppic[5];
   }
 // speed = TrackBar1->Position;
  if(reg->ValueExists("speed")) speed = reg->ReadInteger("speed");
  else speed = 0;
  if(reg->ValueExists("stretch")) stretch = reg->ReadInteger("stretch");
  else stretch = false;
  if(reg->ValueExists("hirestex")) hirestex = reg->ReadInteger("hirestex");
  else hirestex = 0;


  //TrackBar1->SelStart = 1;
  //TrackBar1->SelEnd = 10;
  ScrollBar1->Position = speed;
  if(stretch) CheckBox1->State =cbChecked;
   else CheckBox1->State = cbUnchecked;
  if(hirestex) CheckBox2->State =cbChecked;
   else CheckBox2->State = cbUnchecked;

  delete reg;
  }
//---------------------------------------------------------------------------
void __fastcall TForm2::Button1Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[0] = OpenDialog1->FileName;
   Edit1->Text = names[0];
   temppic[0]->LoadFromFile(names[0]);
   dynamic_cast<TJPEGImage *>(temppic[0]->Graphic);
   Image1->Picture = temppic[0];
    Button9->Enabled = true;
}
 }
//---------------------------------------------------------------------------

void __fastcall TForm2::Button2Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[1] = OpenDialog1->FileName;
   Edit2->Text = names[1];
   temppic[1]->LoadFromFile(names[1]);
   dynamic_cast<TJPEGImage *>(temppic[1]->Graphic);
   Image2->Picture = temppic[1];
    Button9->Enabled = true;
}
 }
//---------------------------------------------------------------------------

void __fastcall TForm2::Button3Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[2] = OpenDialog1->FileName;
   Edit3->Text = names[2];
   temppic[2]->LoadFromFile(names[2]);
   dynamic_cast<TJPEGImage *>(temppic[2]->Graphic);
   Image3->Picture = temppic[2];
   Button9->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button4Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[3] = OpenDialog1->FileName;
   Edit4->Text = names[3];
   temppic[3]->LoadFromFile(names[3]);
   dynamic_cast<TJPEGImage *>(temppic[3]->Graphic);
   Image4->Picture = temppic[3];
    Button9->Enabled = true;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button5Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[4] = OpenDialog1->FileName;
   Edit5->Text = names[4];
   temppic[4]->LoadFromFile(names[4]);
   dynamic_cast<TJPEGImage *>(temppic[4]->Graphic);
   Image5->Picture = temppic[4];
   Button9->Enabled = true;
 }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button6Click(TObject *Sender)
{
 if(OpenDialog1->Execute())
  {
   names[5] = OpenDialog1->FileName;
   Edit6->Text = names[5];
   temppic[5]->LoadFromFile(names[5]);
   dynamic_cast<TJPEGImage *>(temppic[5]->Graphic);
   Image6->Picture = temppic[5];
   Button9->Enabled = true;

  }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button7Click(TObject *Sender)
{
  reg = new TRegistry;
  reg->OpenKey("software",true);
  reg->OpenKey("picube",true);

  reg->WriteString("pic1",names[0]);
  reg->WriteString("pic2",names[1]);
  reg->WriteString("pic3",names[2]);
  reg->WriteString("pic4",names[3]);
 reg->WriteString("pic5",names[4]);
 reg->WriteString("pic6",names[5]);
 reg->WriteInteger("speed",speed);
 reg->WriteInteger("stretch",stretch);
 reg->WriteInteger("hirestex",hirestex);
  delete reg;

 PostQuitMessage(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button8Click(TObject *Sender)
{
PostQuitMessage(1);
}
//---------------------------------------------------------------------------

/*void __fastcall TForm2::TrackBar1Change(TObject *Sender)
{
  //TrackBar1->SelStart = TrackBar1->Position;
  //TrackBar1->SelEnd = TrackBar1->Position;
  speed = TForm2::TrackBar1->Position;
  Button9->Enabled = true;
  //TrackBar1->Position = speed;
  }
//---------------------------------------------------------------------------
*/
void __fastcall TForm2::Button9Click(TObject *Sender)
{
  reg = new TRegistry;
  reg->OpenKey("software",true);
  reg->OpenKey("picube",true);

  reg->WriteString("pic1",names[0]);
  reg->WriteString("pic2",names[1]);
  reg->WriteString("pic3",names[2]);
  reg->WriteString("pic4",names[3]);
 reg->WriteString("pic5",names[4]);
 reg->WriteString("pic6",names[5]);
 reg->WriteInteger("speed",speed);
 reg->WriteInteger("stretch",stretch);
 reg->WriteInteger("hirestex",hirestex);

   delete reg;

  Button9->Enabled = false;
}
//---------------------------------------------------------------------------


/*void __fastcall TForm2::ScrollBar1Change(TObject *Sender)
{
  speed = ScrollBar1->Position;
  Button9->Enabled = true;

}
//---------------------------------------------------------------------------
*/
void __fastcall TForm2::ScrollBar1Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
  speed = (ScrollBar1->Position);
  Button9->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox1Click(TObject *Sender)
{
 if(CheckBox1->State == cbUnchecked) stretch = false;
  else stretch = true;
 Button9->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::CheckBox2Click(TObject *Sender)
{
  if(CheckBox2->State == cbUnchecked) hirestex = false;
   else hirestex = true;
  Button9->Enabled = true;

}
//---------------------------------------------------------------------------

