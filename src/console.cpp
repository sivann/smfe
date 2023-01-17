//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "console.h"
#include "smfe1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConsoleFrm *ConsoleFrm;
//---------------------------------------------------------------------------
__fastcall TConsoleFrm::TConsoleFrm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TConsoleFrm::FormShow(TObject *Sender)
{
  Form1->ShowConsole->Checked=true;
  Form1->ConsoleTbtn->Down=true;
}
//---------------------------------------------------------------------------
void __fastcall TConsoleFrm::FormHide(TObject *Sender)
{
  Form1->ShowConsole->Checked=false;
  Form1->ConsoleTbtn->Down=false;  
}
//---------------------------------------------------------------------------
void __fastcall TConsoleFrm::Clear1Click(TObject *Sender)
{
  Console->Clear();    
}
//---------------------------------------------------------------------------


void __fastcall TConsoleFrm::SelectAllClick(TObject *Sender)
{
  Console->SelectAll();  
}
//---------------------------------------------------------------------------

void __fastcall TConsoleFrm::Copy1Click(TObject *Sender)
{
  Console->CopyToClipboard();  
}
//---------------------------------------------------------------------------

