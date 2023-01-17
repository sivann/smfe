//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include <sys\stat.h>
#include <errno.h>
#include <string.h>
#include "smfe1.h"
#include "unit3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsFrm *SettingsFrm;
//---------------------------------------------------------------------------
__fastcall TSettingsFrm::TSettingsFrm(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSettingsFrm::SOkBtnClick(TObject *Sender)
{
 struct stat statbuf;

  if (MLocationEdit->Text.Length()==0)
      SettingsFrm->Close();


  else if (stat(MLocationEdit->Text.c_str(),&statbuf)==-1){
    ShowMessage(strerror(errno));
  }
  else if (statbuf.st_mode & S_IFDIR)
    ShowMessage(MLocationEdit->Text + " is a directory");
  else {
    SettingsFrm->Close();
    Form1->SavePaths();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSettingsFrm::HistEdtEnter(TObject *Sender)
{
  if (!HistEdt->Text.Length() && MLocationEdit->Text.Length()) {
    HistEdt->Text=ExtractFilePath(SettingsFrm->MLocationEdit->Text) + "history.dat";
  }
}

//---------------------------------------------------------------------------

void __fastcall TSettingsFrm::AutoFillBtnClick(TObject *Sender)
{
  //AnsiString cmdline=GetCommandLine();
  AnsiString smfepath=ExtractFilePath(Application->ExeName);

  if ((MessageDlg("This will overwrite current paths. Continue ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
    return;

  //mame.exe
  if ((MLocationEdit->Text.Length()==0) || (!FileExists(SettingsFrm->MLocationEdit->Text))){
    if (FileExists(smfepath+"mamepp.exe")) SettingsFrm->MLocationEdit->Text=smfepath+"mamepp.exe";
    else if (FileExists(smfepath+"mameppro.exe")) SettingsFrm->MLocationEdit->Text=smfepath+"mameppro.exe";
    else if (FileExists(smfepath+"mame.exe")) SettingsFrm->MLocationEdit->Text=smfepath+"mame.exe";
    else {
      ShowMessage("Unable to guess a mame executable inside " +smfepath);
      return;
    }
  }

  AnsiString mamepath=ExtractFilePath(MLocationEdit->Text);

  //snapshots
  if ((SnapshotEdt->Text.Length()==0) || (!DirectoryExists(SettingsFrm->SnapshotEdt->Text))){
    if (DirectoryExists(mamepath+"snap")) SettingsFrm->SnapshotEdt->Text=mamepath+"snap";
    else if (DirectoryExists(smfepath+"snap")) SettingsFrm->SnapshotEdt->Text=smfepath+"snap";
    else if (DirectoryExists(smfepath+"snapshots")) SettingsFrm->SnapshotEdt->Text=smfepath+"snapshots";
  }

  //artwork
  if ((ArtworkEdt->Text.Length()==0) || (!DirectoryExists(SettingsFrm->ArtworkEdt->Text))){
    if (DirectoryExists(mamepath+"artwork")) SettingsFrm->ArtworkEdt->Text=mamepath+"artwork";
    else if (DirectoryExists(smfepath+"artwork")) SettingsFrm->ArtworkEdt->Text=smfepath+"artwork";
  }

  //cabinet
  if ((CabinetEdt->Text.Length()==0) || (!DirectoryExists(SettingsFrm->CabinetEdt->Text))){
    if (DirectoryExists(mamepath+"cab")) SettingsFrm->CabinetEdt->Text=mamepath+"cab";
    else if (DirectoryExists(smfepath+"cab")) SettingsFrm->CabinetEdt->Text=smfepath+"cab";
  }

  //flyers
  if ((FlyerEdt->Text.Length()==0) || (!DirectoryExists(SettingsFrm->FlyerEdt->Text))){
    if (DirectoryExists(mamepath+"flyers")) SettingsFrm->FlyerEdt->Text=mamepath+"flyers";
    else if (DirectoryExists(smfepath+"flyers")) SettingsFrm->FlyerEdt->Text=smfepath+"flyers";
  }


  //history.dat
  if ((HistEdt->Text.Length()==0) || (!DirectoryExists(SettingsFrm->HistEdt->Text))){
    if (FileExists(mamepath+"history.dat"))  SettingsFrm->HistEdt->Text=mamepath+"history.dat";
    else if (FileExists(smfepath+"history.dat"))  SettingsFrm->HistEdt->Text=smfepath+"history.dat";
  }
}
//---------------------------------------------------------------------------


