//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Legend.h"
#include "smfe1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLegendFrm *LegendFrm;
//---------------------------------------------------------------------------
__fastcall TLegendFrm::TLegendFrm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLegendFrm::FormShow(TObject *Sender)
{
  Form1->LegendBtn->Down=true;
  Form1->GridImlist->GetBitmap(0,Image0->Picture->Bitmap);
  Form1->GridImlist->GetBitmap(4,Image1->Picture->Bitmap);
  Form1->GridImlist->GetBitmap(1,Image2->Picture->Bitmap);
  Form1->GridImlist->GetBitmap(3,Image3->Picture->Bitmap);
  Form1->GridImlist->GetBitmap(6,Image4->Picture->Bitmap);  

}
//---------------------------------------------------------------------------
void __fastcall TLegendFrm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Form1->LegendBtn->Down=false;
}
//---------------------------------------------------------------------------
