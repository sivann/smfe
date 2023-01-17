//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ExtractFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExtractForm *ExtractForm;
//---------------------------------------------------------------------------
__fastcall TExtractForm::TExtractForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
