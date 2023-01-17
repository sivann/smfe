//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "verfrm.h"
#include <stdio.h>
#include <errno.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TVerForm *VerForm;
//---------------------------------------------------------------------------
__fastcall TVerForm::TVerForm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//update the progress bar by counting the lines of the mame output
void __fastcall TVerForm::updPbar()
{
  char fname[256],tmp[1000002];
  FILE *fp;
  int r,i,lines;


  GetTempPath(256,tmp);
  strcpy(fname,(AnsiString(tmp)+"smfe_romstatus.txt").c_str());

  if (0==(fp=fopen(fname,"r")) ) {
    VerForm->Caption=(strerror(errno));
    return;
  }

  r=fread(tmp, 1,1000000, fp);
  if (!r) {
    fclose(fp);
    return;
  }

  for (lines=0,i=0;i<r;i++)
    if (tmp[i]=='\n') lines ++;

  //ProgressBar->Position=lines/30;
  ProgressBar->Position=lines;
  VerForm->Update();

  fclose(fp);
}
//---------------------------------------------------------------------------

