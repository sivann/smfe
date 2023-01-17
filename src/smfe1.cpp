//todo: mame settings
//todo: record game music (mp3?)
//todo: improve layout
//todo: to -createconfig swzei se ".ini" anti "mame.ini", allagh me -showconfig > arxeio


//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "smfe1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "AboutForm.h"
#include "ExtractFrm.h"
#include "console.h"
#include "verfrm.h"
#include "Legend.h"
#include "HelpForm.h"

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>


#include <errno.h>
#include <string.h>
#include <windows.h>


#include <dirent.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGrid"
#pragma link "PAINTXLib_OCX"
#pragma link "ImageEn"
#pragma link "ImageEnProc"
#pragma link "ImageEnView"
#pragma link "ImageEnIO"
#pragma link "RXCtrls"
#pragma link "AdvGrid"
#pragma link "ImageEn"
#pragma link "ImageEnView"
#pragma link "RXCtrls"
#pragma link "AdvGrid"
#pragma link "ImageEn"
#pragma link "ImageEnView"
#pragma link "RXCtrls"
#pragma link "BaseGrid"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

bool imageshow=false;
HANDLE mamehdl;


set<AnsiString> files;

void showLastError();
void updateConsole();
void presetColWidths();
void parseHistory();
void checkAvailable();
void verifyRoms();

//---------------------------------------------------------------------------


__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TForm1::DefineSettings1Click(TObject *Sender)
{
  SettingsFrm->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Readgames1Click(TObject *Sender)
{
if ((MessageDlg("Clear all table data and refresh the list of the emulated games from the mame executalbe (5-15 seconds) ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
  return;

char tmp[256];
char buff[30000],*p,buf[256];
int count;
char fname[256];

HANDLE child_file;
HANDLE ff;
DWORD wret;
STARTUPINFO si;
PROCESS_INFORMATION pi;

  if (!FileExists(SettingsFrm->MLocationEdit->Text)){
    StatusBar->Panels->Items[0]->Text="Please select the mame executable (Settings Menu)";
    return;
  }

  imageshow=false;

  ExtractForm->Visible=true;Form1->Enabled=false;
  ExtractForm->ParLbl->Font->Style = TFontStyles();
  ExtractForm->ExLbl->Font->Style =TFontStyles()<< fsBold;

  ExtractForm->Update();

  GetTempPath(256,tmp);

  strcpy(fname,(AnsiString(tmp)+"smfe_gamelist.txt").c_str());
  ff=CreateFile(fname, GENERIC_READ | GENERIC_WRITE,	FILE_SHARE_WRITE | FILE_SHARE_READ,
                0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	//Redirect stdout to a file
  SetStdHandle(STD_OUTPUT_HANDLE, ff);

	//Redirect the c runtime library stdout to use that file too
  //int crt_handle=_open_osfhandle((long) ff, _O_TEXT); *stdout=*_fdopen(crt_handle, "w");

	DuplicateHandle(GetCurrentProcess(), ff, GetCurrentProcess(), &child_file, 0, TRUE,DUPLICATE_SAME_ACCESS);

  memset(&si, 0, sizeof(si));

  si.cb=sizeof(si);
  si.lpTitle="MAME";
  si.dwFlags=STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;;
	si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput=child_file;
	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);
  si.wShowWindow=SW_HIDE;

  SetCurrentDirectory (ExtractFilePath(SettingsFrm->MLocationEdit->Text).c_str());

  Screen->Cursor=crHourGlass;
  ConsoleFrm->Console->Lines->Add(AnsiString("Calling " + SettingsFrm->MLocationEdit->Text+" -sortname -listinfo"));
	CreateProcess(SettingsFrm->MLocationEdit->Text.c_str()," -sortname -listinfo",0,0,TRUE,0,0,0,&si,&pi);
  CloseHandle(ff);
  CloseHandle(child_file);
	//wret=WaitForSingleObject(pi.hProcess, 55000);

  for (count=0;(count<55) && ((wret=WaitForSingleObject(pi.hProcess, 1000))!=0) ;count++) {
    Application->ProcessMessages();
    //update the progress bar?
  }

  Screen->Cursor=crDefault;
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);

  if (wret == WAIT_TIMEOUT) {
    StatusBar->Panels->Items[0]->Text="55 seconds timeout occured while executing \""+
                          SettingsFrm->MLocationEdit->Text+" -listinfo\"";
    ConsoleFrm->Console->Lines->Add("55 seconds timeout occured");
    ConsoleFrm->Console->Lines->Add("--------------------------");
    int code=0;
    TerminateProcess(pi.hProcess,code);
    ExtractForm->Visible=false;Form1->Enabled=true;
    return;
  }

  if (!FileExists(fname)) {
    ShowMessage(AnsiString(fname)+" doesn't exist - operation failed.");
    ExtractForm->Visible=false;Form1->Enabled=true;
    return;
  }


//--------------- start parsing --------------------
  ConsoleFrm->Console->Lines->Add("Parsing Game Info");

  ExtractForm->ExLbl->Font->Style = TFontStyles();
  ExtractForm->ParLbl->Font->Style =TFontStyles()<< fsBold;
  ExtractForm->ProgressBar->Max=5000;  //count games
  ExtractForm->ProgressBar->Visible=true;
  ExtractForm->Update();

  FILE *fp;

  if (0==(fp=fopen(fname,"r")) ) {
    ShowMessage(strerror(errno));
    ExtractForm->Visible=false;Form1->Enabled=true;
    return;
  }

  char rom[64],desc[128],year[64],mfct[64],cloneof[64],romof[64],
       chip[128],cpu[128],res[64],vidtype[64],sound[64],rec[30240],category[64];
  char *p2;
  int ingame,games,i;
  float freq;

  rom[0]=desc[0]=year[0]=mfct[0]=cloneof[0]=romof[0]=chip[0]=cpu[0]=res[0]=category[0]=0;
  vidtype[0]=sound[0]=rec[0]=0;

  count=ingame=games=freq=0;

  Grid->RowCount=1;
  Form1->Update();
  Grid->BeginUpdate();

  while (fgets(buff,30000,fp)) {
    if (games%10) {
      ExtractForm->ProgressBar->Position=games;
      ExtractForm->Update();
    }
    if (!strncmp(buff,"\tname",5)) {
      sscanf(buff+5,"%s",rom);
      games++;
      ingame=1;
    }
    else if (ingame && !strncmp(buff,"\tdescription",4)) {
      sscanf(buff,"%*s \"%[^\"]",desc);
    }
    else if (ingame && !strncmp(buff,"\tyear",3)) {
      sscanf(buff+5,"%s",year);
    }
    else if (!strncmp(buff,"\tmanufacturer",4)) {
      sscanf(buff,"%*s \"%[^\"]",mfct);
    }
    else if (!strncmp(buff,"\tcloneof",3)) {
      sscanf(buff+8,"%s",cloneof);
    }
    else if (!strncmp(buff,"\tromof",5)) {
      sscanf(buff+6,"%s",romof);
    }
    else if (!strncmp(buff,"\tsound",5)) {
      sscanf(buff+6,"%d",&i);
      if (i>1) strcpy(sound,"stereo");
      else strcpy(sound,"mono");
    }
    else if (!strncmp(buff,"\tchip",3)) {
      p=strstr(buff,"cpu name");
      if (p) {
        sscanf(p+8,"%s",chip);
        p=strstr(buff," clock ");
        if (p) {
          sscanf(p+7,"%f",&freq);
          freq/=1000000.0;
          sprintf(tmp," %2.2f Mhz",freq);
          strcat(chip,tmp);
        }
      }
    }
    else if (!strncmp(buff,"\thistory",4)) {
      p=strstr(buff,"Recommended Games"); //MAMEINFO.dat must be present
      if (p) {
        if (0!=(p2=strstr(p,"\\n\\n"))) *p2=0;
        //convert '\' 'n' to \n
        p2=p;
        while (*p && *(p+1)) {

          if (*p=='\\' && *(p+1)=='n') {
            *p=' ';
            *(p+1)='\n';
          }
          p++;
        }//while
        strcpy(rec,p2);
      } //if recommended games
      if ((p=strstr(buff,"Category: "))!=0) {
        sscanf(p+10,"%s",category);
      }
    }
    else if (!strncmp(buff,"\tvideo",3)) {
      //res
      p=strstr(buff," x ");
      if (p) {
        sscanf(p,"%*s %s",tmp);
        strcpy(res,tmp);
        strcat(res,"x");
        p=strstr(buff," y ");
      }
      if (p) {
        sscanf(p,"%*s %s",tmp);
        strcat(res,tmp);
      }

      //screen type
      p=strstr(buff," screen ");
      if (p) {
        sscanf(p,"%*s %s",vidtype);
      }

    }
    else if (buff[0]==')') {
      ingame=0;
      Grid->RowCount++;
      count++;

      Grid->Cells[ColOf("ROM")][count]=rom;
      Grid->Cells[ColOf("Description")][count]=desc;
      Grid->Cells[ColOf("Year")][count]=year;
      Grid->Cells[ColOf("Manufacturer")][count]=mfct;
      Grid->Cells[ColOf("Clone Of")][count]=cloneof;
      Grid->Cells[ColOf("Category")][count]=category;
      Grid->Cells[ColOf("Resolution")][count]=res;
      Grid->Cells[ColOf("Type")][count]=vidtype;
      Grid->Cells[ColOf("CPU")][count]=chip;
      Grid->Cells[ColOf("Rom Of")][count]=romof;
      Grid->Cells[ColOf("Info")][count]=rec;
      Grid->Cells[ColOf("Played")][count]=0;

      rom[0]=desc[0]=year[0]=mfct[0]=cloneof[0]=romof[0]=chip[0]=cpu[0]=0;
      res[0]=vidtype[0]=sound[0]=rec[0]=freq=0;
    }
  }//while fgets

  Grid->EndUpdate();
  presetColWidths();

  fclose(fp);
  DeleteFile(fname);
  imageshow=true;

  ExtractForm->Visible=false;Form1->Enabled=true;
  StatusBar->Panels->Items[0]->Text="";

  //Save results
  SaveData();
  ConsoleFrm->Console->Lines->Add("Parsing Completed");
  ConsoleFrm->Console->Lines->Add("-----------------");
  //For the "Trial version Message:"
  Grid->RowCount++;

}//Readgames1Click


//------- Save table data ----------
void __fastcall TForm1::SaveData() {
struct stat statbuf;
AnsiString datname=ExtractFilePath(Application->ExeName)+"smfe_data.dat";

  if ((stat(datname.c_str(),&statbuf)!=-1)  && !(statbuf.st_mode & S_IWRITE)) {
    StatusBar->Panels->Items[0]->Text=datname + " not saved: read only";
    ConsoleFrm->Console->Lines->Add(datname + " not saved: read only");
    return;
  }

  hideCols(false);
  Grid->SaveToFile(datname);
  hideCols(true);
  StatusBar->Panels->Items[0]->Text="Data saved to "+datname;
  ConsoleFrm->Console->Lines->Add("Data saved to "+datname);
}  


void __fastcall TForm1::SavePaths() {
TIniFile *ini;
  ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ));
  ini->WriteString("SMFE", "EXECUTABLE",SettingsFrm->MLocationEdit->Text);
  ini->WriteString("SMFE", "ARTWORK",SettingsFrm->ArtworkEdt->Text);
  ini->WriteString("SMFE", "CABINET",SettingsFrm->CabinetEdt->Text);
  ini->WriteString("SMFE", "FLYERS",SettingsFrm->FlyerEdt->Text);
  ini->WriteString("SMFE", "SNAPSHOT",SettingsFrm->SnapshotEdt->Text);
  ini->WriteString("SMFE", "HISTORY.DAT",SettingsFrm->HistEdt->Text);

  ini->WriteBool("SMFE", "AUTOEXTRACT",SettingsFrm->AutoExtract->Checked);
  ini->WriteBool("SMFE", "PNG",SettingsFrm->png->Checked);
  ini->WriteBool("SMFE", "JPG",SettingsFrm->jpg->Checked);
  ini->WriteBool("SMFE", "TIF",SettingsFrm->tif->Checked);
  ini->WriteBool("SMFE", "GIF",SettingsFrm->gif->Checked);
  ini->WriteBool("SMFE", "BMP",SettingsFrm->bmp->Checked);
  ini->WriteBool("SMFE", "ICO",SettingsFrm->ico->Checked);
  ini->UpdateFile();
  delete ini;
  StatusBar->Panels->Items[0]->Text="Settings saved to "+ExtractFilePath(Application->ExeName)+"smfe.ini";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveStats(stats_s stats) {
TIniFile *ini;
  ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ));
  ini->WriteInteger("STATS", "s_total",stats.s_total);
  ini->WriteInteger("STATS", "s_good",stats.s_good);
  ini->WriteInteger("STATS", "s_notfound",stats.s_notfound);
  ini->WriteInteger("STATS", "s_notworking",stats.s_notworking);
  ini->WriteInteger("STATS", "s_bestavailable",stats.s_bestavailable);
  ini->WriteInteger("STATS", "s_unknown",stats.s_unknown);
  ini->UpdateFile();
  delete ini;
}


void __fastcall TForm1::FormShow(TObject *Sender)
{
  TIniFile *ini;
  struct stat statbuf;
  AnsiString datname=ExtractFilePath(Application->ExeName)+"smfe_data.dat";

  ini = new TIniFile(ChangeFileExt(Application->ExeName, ".ini" ));
  SettingsFrm->MLocationEdit->Text=ini->ReadString("SMFE", "EXECUTABLE","");
  SettingsFrm->ArtworkEdt->Text=ini->ReadString("SMFE", "ARTWORK","");
  SettingsFrm->CabinetEdt->Text=ini->ReadString("SMFE", "CABINET","");
  SettingsFrm->FlyerEdt->Text=ini->ReadString("SMFE", "FLYERS","");
  SettingsFrm->SnapshotEdt->Text=ini->ReadString("SMFE", "SNAPSHOT","");
  SettingsFrm->HistEdt->Text=ini->ReadString("SMFE", "HISTORY.DAT","");
    
  SettingsFrm->AutoExtract->Checked=ini->ReadBool("SMFE", "AUTOEXTRACT",false);
  SettingsFrm->png->Checked=ini->ReadBool("SMFE", "PNG",true);
  SettingsFrm->jpg->Checked=ini->ReadBool("SMFE", "JPG",true);
  SettingsFrm->tif->Checked=ini->ReadBool("SMFE", "TIF",false);
  SettingsFrm->gif->Checked=ini->ReadBool("SMFE", "GIF",false);
  SettingsFrm->bmp->Checked=ini->ReadBool("SMFE", "BMP",false);
  SettingsFrm->ico->Checked=ini->ReadBool("SMFE", "ICO",false);

  delete ini;

  MAMEOpts->readMoptions();

  Grid->AutoSizeColumns(true,2);

  if (SettingsFrm->AutoExtract->Checked &&
    (SettingsFrm->MLocationEdit->Text.Length()!=0)
      && (stat(SettingsFrm->MLocationEdit->Text.c_str(),&statbuf)!=-1)
      && !(statbuf.st_mode & S_IFDIR) ) Form1->Readgames1Click(this);

  else if (FileExists(datname)) {
    Grid->LoadFromFile(datname);
    StatusBar->Panels->Items[0]->Text="Gamelist loaded";
    presetColWidths();
    updateIcons();
    imageshow=true;
  }
  else {
    StatusBar->Panels->Items[0]->Text="Please refresh the gamelist (Game Data menu)";
    presetColWidths();
  }

  Grid->ColumnSize->Key=ExtractFilePath(Application->ExeName)+"smfe.ini";
  if (FileExists(Grid->ColumnSize->Key))
    Grid->LoadColSizes();
  Form1->Grid->ColWidths[Form1->ColOf("Status")]=18;
  hideCols(true);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::hideCols(bool hide)
{
  if (hide) {
    Form1->Grid->HideColumn(Form1->ColOf("Bio")); //History.dat
    Form1->Grid->HideColumn(Form1->ColOf("Info"));//mame -listinfo
  }
  else {
    Grid->UnHideColumnsAll();
  }
}


void __fastcall TForm1::GridSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
  StatusBar->Panels->Items[2]->Text=AnsiString("Line " + AnsiString(ARow));
  if (!GridTimer->Enabled) {
    GridTimer->Enabled=true;
  }
  else {
    GridTimer->Enabled=false;
    GridTimer->Enabled=true;
  }
}



void __fastcall TForm1::showImage(int ACol, int ARow)
{

  static int col=0,row=0;

  if (ACol>=0 && ARow>=0) {
    col=ACol;
    row=ARow;
  }

  if (!imageshow)
  return;
  // Load a JPEG, PNG, BMP, PCX, TIFF, WMF, EMF, ICO, CUR or Gif file.

  AnsiString imagebasename,imagebn;
  AnsiString imgext;
  int skipchar;

  switch (TabControl1->TabIndex) {
    case 0:  imagebn=SettingsFrm->SnapshotEdt->Text;break;
    case 1:  imagebn=SettingsFrm->ArtworkEdt->Text;break;
    case 2:  imagebn=SettingsFrm->CabinetEdt->Text;break;
    case 3:  imagebn=SettingsFrm->FlyerEdt->Text;break;
  }

  if ((Grid->Cells[ColOf("ROM")][row]).Length())
    imagebasename=imagebn+"\\"+AnsiString(Grid->Cells[ColOf("ROM")][row]);

  imgext="";

  if (SettingsFrm->jpg->Checked && FileExists(imagebasename+".jpg"))
    imgext=".jpg";
  else if (SettingsFrm->png->Checked && FileExists(imagebasename+".png"))
    imgext=".png";
  else if (SettingsFrm->gif->Checked && FileExists(imagebasename+".gif"))
    imgext=".gif";
  else if (SettingsFrm->bmp->Checked && FileExists(imagebasename+".bmp"))
    imgext=".bmp";
  else if (SettingsFrm->ico->Checked && FileExists(imagebasename+".ico"))
    imgext=".ico";


  if (imgext=="") {
    imagebasename=imagebn+"\\"+AnsiString(Grid->Cells[ColOf("Clone Of")][row]);

    if (SettingsFrm->jpg->Checked && FileExists(imagebasename+".jpg"))
      imgext=".jpg";
    else if (SettingsFrm->png->Checked && FileExists(imagebasename+".png"))
      imgext=".png";
    else if (SettingsFrm->gif->Checked && FileExists(imagebasename+".gif"))
      imgext=".gif";
    else if (SettingsFrm->bmp->Checked && FileExists(imagebasename+".bmp"))
      imgext=".bmp";
    else if (SettingsFrm->ico->Checked && FileExists(imagebasename+".ico"))
      imgext=".ico";
  }



  if (imgext!="") {
    ImageEn1->LoadFromFile(imagebasename+imgext);
    ImgLbl->Caption=ExtractFileName(imagebasename+imgext);
    ImgLbl->Hint=ImgLbl->Caption;
  }
  else {
    ImageEn1->Background=Form1->Color;
    ImageEn1->Clear();
    ImgLbl->Caption="";
    ImgLbl->Hint=ImgLbl->Caption;
  }

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Createmameini1Click(TObject *Sender)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  si.cb=sizeof(STARTUPINFO);
  si.lpReserved=0;
  si.lpDesktop=0;
  si.lpTitle="MAME";
  //si.dwFlags=0;
  si.dwFlags=STARTF_USESHOWWINDOW;;
  si.cbReserved2=0;
  si.lpReserved2=0;
  si.wShowWindow=SW_HIDE;

  SetCurrentDirectory(ExtractFilePath(SettingsFrm->MLocationEdit->Text).c_str());


  Screen->Cursor=crHourGlass;
  ConsoleFrm->Console->Lines->Add("-------------------");
  ConsoleFrm->Console->Lines->Add(AnsiString("Calling \"" + SettingsFrm->MLocationEdit->Text + " -createconfig"+"\""));
	CreateProcess(SettingsFrm->MLocationEdit->Text.c_str(), " -createconfig", 0, 0, TRUE, 0, 0, 0, &si, &pi);
	WaitForSingleObject(pi.hProcess, 15000);
  Screen->Cursor=crDefault;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Editmameini1Click(TObject *Sender)
{
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  si.cb=sizeof(STARTUPINFO);
  si.lpReserved=0;
  si.lpDesktop=0;
  si.lpTitle="";
  si.dwFlags=0;
  si.cbReserved2=0;
  si.lpReserved2=0;
  si.wShowWindow=0;

  SetCurrentDirectory(ExtractFilePath(SettingsFrm->MLocationEdit->Text).c_str());

  Screen->Cursor=crHourGlass;
	CreateProcess(0,(AnsiString("notepad ") + ChangeFileExt(SettingsFrm->MLocationEdit->Text,".ini")).c_str(), 0, 0, TRUE, 0, 0, 0, &si, &pi);
	WaitForSingleObject(pi.hProcess, 10);
  Screen->Cursor=crDefault;

}
//---------------------------------------------------------------------------





void __fastcall TForm1::About1Click(TObject *Sender)
{
  AboutFrm->ShowModal();

}
//---------------------------------------------------------------------------



void __fastcall TForm1::TabControl1Change(TObject *Sender)
{
  showImage(-1,-1);  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GridTimerTimer(TObject *Sender)
{
  GridTimer->Enabled=false;
  showImage(Grid->Col,Grid->Row);

  BioBox->Lines->Clear();
  BioBox->Lines->Append(Grid->Cells[ColOf("Info")][Grid->Row]);//mame -listinfo
  BioBox->Lines->Append(Grid->Cells[ColOf("Bio")][Grid->Row]); //history.dat
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindBoxKeyPress(TObject *Sender, char &Key)
{
  if (Key==13) {
    FindBtnClick(this);
  }
}
//---------------------------------------------------------------------------

void showLastError()
{
  LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR) &lpMsgBuf,
        0,
        NULL
    );
    AnsiString msg=AnsiString((char *)lpMsgBuf) + "("+SettingsFrm->MLocationEdit->Text +")";
    //ShowMessage(msg);
    Form1->StatusBar->Panels->Items[0]->Text=msg;
    // Free the buffer.
    LocalFree( lpMsgBuf );
}

void __fastcall TForm1::proctimerTimer(TObject *Sender)
{
  DWORD rrr=WaitForSingleObject(mamehdl, 100);
  static last=1;

  if (rrr==WAIT_TIMEOUT)  {
    StatusBar->Panels->Items[1]->Text="M.A.M.E. is running";
    StatusBar->Panels->Items[0]->Text="";
    Screen->Cursor=crAppStart;
    KillBtn->Enabled=true;
    last=1;
  }
  else {
    StatusBar->Panels->Items[1]->Text="M.A.M.E. not running";
    Screen->Cursor=crDefault;
    KillBtn->Enabled=false;
    proctimer->Enabled=false;
    //update console
    updateConsole();
    if (last)
      CloseHandle(mamehdl);
    last=0;
  }
}
//---------------------------------------------------------------------------

void updateConsole()
{
char tmp[256],fname[256],buff[1024];
TStringList* MyList;
FILE *fp;

  GetTempPath(256,tmp);
  strcpy(fname,(AnsiString(tmp)+"smfe_msglog.txt").c_str());

//  if (!FileExists(fname))
//    return;

  fp=fopen(fname,"r");
  if (!fp) {
    ShowMessage(AnsiString(fname) + strerror(errno));
    fclose(fp);
    return;
  }

  MyList = new TStringList();
  MyList->LoadFromFile(fname);
  ConsoleFrm->Console->Lines->AddStrings(MyList);
  ConsoleFrm->Console->Lines->Add("-----------------------");
  delete MyList;

  DeleteFile(fname);
}

void __fastcall TForm1::ShowConsoleClick(TObject *Sender)
{
  ConsoleFrm->Visible=!ConsoleFrm->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GridDblClick(TObject *Sender)
{
  PlayBtnClick(this);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::GridCanSort(TObject *Sender, int ACol,
      bool &DoSort)
{
  Grid->Cursor = crHourGlass;
  DoSort=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::GridClickSort(TObject *Sender, int ACol)
{
  Grid->Cursor = crDefault;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Readhistorydat1Click(TObject *Sender)
{
if ((MessageDlg("Parse HISTORY.DAT file data into table (15-60 seconds)?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
  return;

  Screen->Cursor=crHourGlass;
  parseHistory();
  SaveData();
  Screen->Cursor=crDefault;
}
//---------------------------------------------------------------------------


//parse HISTORY.DAT
void parseHistory()
{
  FILE *fp;
  char buff[2048],tmp[1024];
  char *p;
  char info[20][64],icon[64],manufacturer[64];
  char year[32],format[64],bio[30010];
  int infocount,j;
  unsigned int i,nofentries=0;

  TPoint res;
  int romcol=Form1->ColOf("ROM");
  int biocol=Form1->ColOf("Bio");
  
  if (0==(fp=fopen(SettingsFrm->HistEdt->Text.c_str(),"r")) ) {
    ShowMessage(SettingsFrm->HistEdt->Text+" "+strerror(errno));
    return;
  }
  infocount=0;
  bio[0]=0;
  for (j=0;j<20;j++) info[j][0]=0;

  Form1->Grid->BeginUpdate();
  Form1->Grid->Options >> goRowSelect;
  Form1->Grid->Col=romcol;


  while (fgets(buff,2040,fp)) {
    if (!(nofentries%50)) {
      Form1->StatusBar->Panels->Items[0]->Text="Entries in history.dat: " + AnsiString(nofentries);
      Application->ProcessMessages();
    }
    if (!strncmp(buff,"$info=",5)){ //an brei info=
      nofentries++;
      infocount=0;

      strcpy(tmp,buff+6);
      p=strtok(tmp,",");
      if (p && p[strlen(p)-1]=='\n') p[strlen(p)-1]=0;
      if (p) strcpy(info[infocount++],p);

      while (0!=(p=strtok(0,","))) {
        if (p[strlen(p)-1]=='\n') p[strlen(p)-1]=0;
        strncpy(info[infocount++],p,19);
        strncpy(tmp,buff+6,1023);
      }
    } //$info
    else if (strstr(buff,"$bio")) {
      sprintf(bio,"\n\n*************************************\n\nhistory.dat info for rom [%s]:\n\n",info[0]);
      do {
        fgets(buff,2040,fp);
        strcat (bio,buff);
      } while (buff[0]!='$' && !strstr(buff,"$end"));
      bio[strlen(bio)-6]=0;
      fseek(fp,-(int)strlen(buff)-1,SEEK_CUR);//unfgets

      for (i=1;i<strlen(bio)-1;i++) {
        if (bio[i]=='\n' && bio[i+1] !='\n') bio[i-1]=' ';
      }

    }//$bio
    else if (strstr(buff,"$end")) {
      //Add info to Grid
      TFindParams findparams;


      findparams << fnFindInCurrentCol << fnMatchStart	<< fnMatchFull << fnMatchCase	;

      for (int i=0;i<infocount;i++) {
        res=Form1->Grid->FindFirst(info[i], findparams);
        if (res.y>0) {
          Form1->Grid->Cells[biocol][res.y]=bio;
        }
      }

      infocount=0;
      bio[0]=0;
      for (j=0;j<20;j++) info[j][0]=0;
    }//$end

   buff[0]=0;
  }//while fgets

  Form1->Grid->Options << goRowSelect;
  Form1->Grid->EndUpdate();


  fclose(fp);
}

//------------------------------------------------------------------------

//parse MAMEINFO.DAT
//to kanei mono tou to mame kai to dinei sto -listinfo
/*
void parseMameinfo()
{
  FILE *fp;
  char buff[1024],tmp[1024];
  char *p;
  char info[10][64],rec[10240],mamever[128];
  int infocount,j;

  TPoint res;

  if (0==(fp=fopen(SettingsFrm->MinfoEdt->Text.c_str(),"r")) ) {
    ShowMessage(SettingsFrm->MinfoEdt->Text+" "+strerror(errno));
    return;
  }
  infocount=0;

  for (j=0;j<10;j++) info[j][0]=0;
  int minfocol=Form1->ColOf("Minfo");

  Form1->Grid->BeginUpdate();

  while (fgets(buff,1024,fp)) {
    if (!strncmp(buff,"$info=",5)){
      infocount=0;

      strcpy(tmp,buff+6);
      p=strtok(tmp,",");
      if (p && p[strlen(p)-1]=='\n') p[strlen(p)-1]=0;
      if (p) strcpy(info[infocount++],p);

      while (0!=(p=strtok(0,","))) {
        if (p[strlen(p)-1]=='\n') p[strlen(p)-1]=0;
        strcpy(info[infocount++],p);
        strcpy(tmp,buff+6);
      }
    } //$info
    else if (!strncmp(buff,"$mame",4)) {
      fgets(mamever,128,fp);
    }
    else if (!strncmp(buff,"Recommended Games:",17)) {
      sprintf(rec,
      "%s data From ** MAMEINFO.DAT ** \n\nAdded in version: %s\n\n\nRecommended games:\n\n",
        info[0],mamever);
      do {
        fgets(buff,1024,fp);
        if (strlen(buff)>2) strcat (rec,buff);
      } while (buff[0]!='$' && strncmp(buff,"$end",4) && strncmp(buff,"Romset:",7) );
      rec[strlen(rec)-5]=0;
      fseek(fp,-(int)strlen(buff)-1,SEEK_CUR);//unfgets
    }//$bio
    else if (!strncmp(buff,"$end",4)) {
      //Add info to Grid
      TFindParams findparams;

      Form1->Grid->Options >> goRowSelect;
      Form1->Grid->Col=Form1->ColOf("ROM");
      findparams << fnFindInCurrentCol << fnMatchStart	<< fnMatchFull;

      for (int i=0;i<infocount;i++) {
        res=Form1->Grid->FindFirst(info[i], findparams);
        if (res.y>0) {
          Form1->Grid->Cells[minfocol][res.y]=rec;
        }
      }
      Form1->Grid->Options << goRowSelect;
      infocount=0;
      rec[0]=mamever[0]=0;
      for (j=0;j<10;j++) info[j][0]=0;
    }//$end

   buff[0]=0;
  }//while fgets

  Form1->Grid->EndUpdate();

  fclose(fp);
}
*/
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveColumnSizes1Click(TObject *Sender)
{
  Grid->ColumnSize->Key=ExtractFilePath(Application->ExeName)+"smfe.ini";
  Grid->SaveColSizes();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ExportGamelist1Click(TObject *Sender)
{
  if (ExportDlg->Execute())
  {             //(
    switch (ExportDlg->FilterIndex) {
      case 1: Grid->SaveToHTML(ExportDlg->FileName+".html");break;
      case 2: Grid->SaveToXLS(ExportDlg->FileName+".xls");break;
      case 3: Grid->SaveToASCII(ExportDlg->FileName+".txt");break;
    }
  }
}
//---------------------------------------------------------------------
void presetColWidths()
{
  Form1->Grid->BeginUpdate();
  Form1->Grid->AutoSizeColumns(true,2);
  Form1->Grid->ColWidths[Form1->ColOf("Status")]=18;
  Form1->Grid->ColWidths[Form1->ColOf("Description")]=100;
  Form1->Grid->ColWidths[Form1->ColOf("Played")]=40;
  Form1->Grid->ColWidths[Form1->ColOf("Players")]=40;
  Form1->Grid->ColWidths[Form1->ColOf("Manufacturer")]=70;
  Form1->Grid->ColWidths[Form1->ColOf("Resolution")]=50;
  Form1->Grid->ColWidths[Form1->ColOf("CPU")]=100;
  Form1->Grid->EndUpdate();
}

void __fastcall TForm1::updateIcons()
{
  int statcol=Form1->ColOf("Status");
  for (int i=1;i<Grid->RowCount;i++) {
    int idx=(Grid->Cells[statcol][i].c_str())[0]-'0';

    Grid->AddImageIdx(0,i,idx,haBeforeText,Advgrid::vaCenter);
  }
}

void __fastcall TForm1::GridKeyPress(TObject *Sender, char &Key)
{
  if (Key==13) {
    PlayBtnClick(this);
  }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::KillBtnClick(TObject *Sender)
{
 int code=0,retval;
 retval=TerminateProcess(mamehdl,code);
 if (!retval) showLastError();
 StatusBar->Panels->Items[0]->Text="";
 Screen->Cursor=crDefault;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindBtnClick(TObject *Sender)
{
 TFindParams findparams;
 TPoint res;


 Grid->Options >> goRowSelect;
 Grid->Col=ColOf("ROM");

 findparams << fnFindInCurrentCol;
 findparams >> fnMatchCase;


 res=Grid->FindFirst(FindBox->Text, findparams);

 if (res.x<0) {
  Grid->Col=ColOf("Description");
  res=Grid->FindFirst(FindBox->Text, findparams);
 }

 if (res.x>=0) {
   Grid->Col=res.x;
   Grid->Row=res.y;
   StatusBar->Panels->Items[0]->Text="Text found on row " + AnsiString(res.y);
 }
 else
   StatusBar->Panels->Items[0]->Text="Text not found";

  Grid->Options << goRowSelect;
  Grid->SelectRows(Grid->Row,1);
  Grid->HilightInRow(false, false, Grid->Row, FindBox->Text);

}
//---------------------------------------------------------------------------


void __fastcall TForm1::FindNextBtnClick(TObject *Sender)
{
  TFindParams findparams;
  TPoint res,start;

  start.x=1;
  start.y=Grid->Row;

  Grid->Options >> goRowSelect;
  Grid->Col=ColOf("ROM");

  findparams << fnFindInCurrentCol;

  res=Grid->Find(start,FindBox->Text, findparams);

  if (res.x<0) {
    Grid->Col=ColOf("Description");
    res=Grid->Find(start,FindBox->Text, findparams);
  }

  if (res.x>=0) {
    Grid->Col=res.x;
    Grid->Row=res.y;
    StatusBar->Panels->Items[0]->Text="Text found on row " + AnsiString(res.y);
  }
  else
    StatusBar->Panels->Items[0]->Text="Text not found";
  Grid->Options << goRowSelect;
  Grid->SelectRows(Grid->Row,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FindPrevBtnClick(TObject *Sender)
{
 TFindParams findparams;
 TPoint res,start;

 start.x=1;
 start.y=Grid->Row;

 Grid->Options >> goRowSelect;
 Grid->Col=ColOf("ROM");


 findparams << fnBackward	<< fnFindInCurrentCol	;

 res=Grid->Find(start,FindBox->Text, findparams);

 if (res.x<0) {
  Grid->Col=ColOf("Description");
  res=Grid->Find(start,FindBox->Text, findparams);
 }


 if (res.x>=0) {
   Grid->Col=res.x;
   Grid->Row=res.y;
   StatusBar->Panels->Items[0]->Text="Text found on row " + AnsiString(res.y);
 }
 else
   StatusBar->Panels->Items[0]->Text="Text not found";
  Grid->Options << goRowSelect;
  Grid->SelectRows(Grid->Row,1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if   (Key==VK_F3)
  {
    FindNextBtnClick(Sender);
  }

  if (Key==75 && Shift.Contains(ssCtrl)) {    //ctrl+k
    //kill mame
    KillBtnClick(this);
    //restore resolution
    ChangeDisplaySettings(NULL, 0);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::PlayBtnClick(TObject *Sender)
{
  PlayGame();
}

void __fastcall TForm1::PlayGame()
{
  // Play selected game
  AnsiString rom=Grid->Cells[ColOf("ROM")][Grid->Row];
  char tmp[256],buf[256],fname[256];
  int retval;
  HANDLE child_file;
  HANDLE ff;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  AnsiString cmdline;
  if (KillBtn->Enabled) {
    ConsoleFrm->Console->Lines->Add("Attempt to start MAME while MAME is running");
    return;
  }

  //Change played times
  if (Grid->Cells[ColOf("Played")][Grid->Row].Length()) {
    int times;
    sscanf((Grid->Cells[ColOf("Played")][Grid->Row].c_str()),"%d",&times);
    times++;
    Grid->Cells[ColOf("Played")][Grid->Row]=times;
  }
  else {
    Grid->Cells[ColOf("Played")][Grid->Row]=1;
  }
  if (autosaveplayedfield1->Checked)
    Form1->SaveData();


  //Start mame
  GetTempPath(256,tmp);

  strcpy(fname,(AnsiString(tmp)+"smfe_msglog.txt").c_str());
  ff=CreateFile(fname, GENERIC_READ | GENERIC_WRITE,	FILE_SHARE_WRITE | FILE_SHARE_READ,
                0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

	// Redirect stdout to a file
  // SetStdHandle(STD_OUTPUT_HANDLE, ff);
  // SetStdHandle(STD_ERROR_HANDLE, ff);   //den xreiazetai
 	DuplicateHandle(GetCurrentProcess(), ff, GetCurrentProcess(), &child_file, 0, TRUE,DUPLICATE_SAME_ACCESS);

  memset(&si, 0, sizeof(si));
  si.cb=sizeof(si);
  si.lpTitle="MAME";
  si.dwFlags=STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
  si.wShowWindow=SW_HIDE;
	si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput=child_file;
	si.hStdError=child_file;
//	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);

  SetCurrentDirectory(ExtractFilePath(SettingsFrm->MLocationEdit->Text).c_str());
  Screen->Cursor=crHourGlass;
  MAMEOpts->ParseMoptions();
  cmdline=SettingsFrm->MLocationEdit->Text + " "+rom + " -v " + MAMEOpts->moptions ;
  ConsoleFrm->Console->Lines->Add("Calling \""+cmdline+"\"");

  retval=CreateProcess(
      0, //lpApplicationName
      cmdline.c_str(), //lpCommandLine
      0, //lpProcessAttributes
      0, //lpThreadAttributes
      true, //bInheritHandles
      0, //dwCreationFlags
      0, //enviroment
      0, //lpCurrentDirectory
      &si, //lpstartupinfo
      &pi //procinfo
  );

  if (!retval) {
    showLastError();
    Screen->Cursor=crDefault;
    return;
  }
  CloseHandle(ff);
  CloseHandle(child_file);
  
  mamehdl=pi.hProcess;
  proctimer->Enabled=true;
  StatusBar->Panels->Items[0]->Text="Please Wait, game starting...";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::EditOptions1Click(TObject *Sender)
{
  MAMEOpts->ShowModal();
}
//---------------------------------------------------------------------------


int __fastcall TForm1::ColOf(AnsiString colname)
{
//  return Grid->ColumnHeaders->IndexOf(colname);
//    for (int i=0;i<Grid->ColCount;i++)
  int i;
  
  for (i=0;i<Grid->ColumnHeaders->Count;i++) {
      //if (Grid->Cells[i][0]==colname) return i;
      if (Grid->ColumnHeaders->Strings[i]==colname) return i;
  }
  return -1;
}




void __fastcall TForm1::Checkexistance1Click(TObject *Sender)
{
if ((MessageDlg("This will overwrite any prior ROM validation results. Check ROM availability (0-2 seconds) ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
  return;

  Screen->Cursor=crHourGlass;
  checkAvailable();
  files.clear();
  Screen->Cursor=crDefault;
}
//---------------------------------------------------------------------------
//kaleitai kai apo thn verifyroms
void checkAvailable()
{

  DIR *dir;
  struct dirent *ent;
  struct stat statbuf;
  int sizecol=Form1->ColOf("RomSize");
  AnsiString filen;
  char size[32];

  char dirname[128];

  strcpy(dirname,(ExtractFilePath(SettingsFrm->MLocationEdit->Text)+"\\roms").c_str());

  if ((dir = opendir(dirname)) == NULL) {
    ShowMessage(strerror(errno));
    return;
  }

  while ((ent = readdir(dir)) != NULL) {
    files.insert(ent->d_name);
  }

  if (closedir(dir) != 0) {
    ShowMessage(strerror(errno));
    return;
  }

  int romcol=Form1->ColOf("ROM");
  int statcol=Form1->ColOf("Status");

  ConsoleFrm->Console->Lines->Add("--------------------");
  ConsoleFrm->Console->Lines->Add("The following romfiles were not found:");

  for (int i=1;i< Form1->Grid->RowCount;i++) {
    if (files.find(Form1->Grid->Cells[romcol][i]+".zip")!=files.end()) {
      //rom exists
      Form1->Grid->Cells[0][i]="";
      Form1->Grid->AddImageIdx(0,i,0,haBeforeText,Advgrid::vaCenter);
      Form1->Grid->Cells[statcol][i]=0;
      Form1->Grid->Cells[0][i]=0;
      //check file size
      filen=AnsiString(dirname)+"\\"+(Form1->Grid->Cells[romcol][i])+AnsiString(".zip");
      if (stat(filen.c_str(),&statbuf)!=-1) {
        sprintf(size,"%.2fKb",(statbuf.st_size)/1000.0);
        Form1->Grid->Cells[sizecol][i]=size;
      }

    }
    else {
      //rom not found
      Form1->Grid->Cells[0][i]="";
      Form1->Grid->AddImageIdx(0,i,4,haBeforeText,Advgrid::vaCenter);
      Form1->Grid->Cells[statcol][i]=4;
      Form1->Grid->Cells[0][i]=4;
      ConsoleFrm->Console->Lines->Add(Form1->Grid->Cells[romcol][i]+".zip");
    }
  }
  ConsoleFrm->Console->Lines->Add("Some of theese games may still reside in other zips, you should run a full verify to get more info.");
  ConsoleFrm->Console->Lines->Add("--------------------");
  Form1->SaveData();
}



//---------------------------------------------------------------------------

void __fastcall TForm1::Verify1Click(TObject *Sender)
{
if ((MessageDlg("Check validity of all ROMs ? (10-1000 seconds depending on rom count and disk/cpu speed)", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
  return;
  verifyRoms();
  files.clear();
}

//---------------------------------------------------------------------------
//verify if roms are ok.
void verifyRoms()
{
char tmp[256];
char buff[1024],*p,buf[256];
int count;
char fname[256];

HANDLE child_file;
HANDLE ff;
DWORD wret;
STARTUPINFO si;
PROCESS_INFORMATION pi;

  if (!FileExists(SettingsFrm->MLocationEdit->Text)){
    Form1->StatusBar->Panels->Items[0]->Text="Please select the mame executable (Settings->SMFE Paths)";
    return ;
  }

  Form1->StatusBar->Panels->Items[0]->Text="Please wait";
  Screen->Cursor=crHourGlass;
  VerForm->Visible=true;
  Form1->Enabled=false;
  VerForm->ProgressBar->Visible=true;
  VerForm->Label1->Font->Style = TFontStyles()<< fsBold;
  VerForm->Label2->Font->Style = TFontStyles();
  VerForm->Label3->Font->Style = TFontStyles();
  VerForm->Update();

  checkAvailable();

  VerForm->Label1->Font->Style = TFontStyles();
  VerForm->Label2->Font->Style =TFontStyles()<< fsBold;
  VerForm->Update();

  GetTempPath(256,tmp);

  strcpy(fname,(AnsiString(tmp)+"smfe_romstatus.txt").c_str());
  ConsoleFrm->Console->Lines->Add("Preparing for rom verification");
  ff=CreateFile(fname, GENERIC_READ|GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

	// Redirect stdout to a file, mallon axristo
  SetStdHandle(STD_OUTPUT_HANDLE, ff);
	DuplicateHandle(GetCurrentProcess(), ff, GetCurrentProcess(), &child_file, 0, TRUE,DUPLICATE_SAME_ACCESS);
  memset(&si, 0, sizeof(si));

  si.cb=sizeof(si);
  si.lpTitle="";
  si.dwFlags=STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW;;
	si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput=child_file;
	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);//child_erfile;//
  si.wShowWindow=SW_HIDE;

  SetCurrentDirectory (ExtractFilePath(SettingsFrm->MLocationEdit->Text).c_str());

  Screen->Cursor=crHourGlass;
  ConsoleFrm->Console->Lines->Add("Calling "+SettingsFrm->MLocationEdit->Text+" * -verifysets");
	CreateProcess(SettingsFrm->MLocationEdit->Text.c_str()," * -verifysets",0,0,TRUE,0,0,0,&si,&pi);

  CloseHandle(ff);
  CloseHandle(child_file);

  //VerForm->ProgressBar->Max=files.size()+10;
  VerForm->ProgressBar->Max=5000;
  for(count=0; (count<(1000)) && ((wret=WaitForSingleObject(pi.hProcess, 1000))!=0);count++) {
    VerForm->updPbar();
    Application->ProcessMessages();
  }

  Screen->Cursor=crDefault;

  if (wret == WAIT_TIMEOUT) {
    Form1->StatusBar->Panels->Items[0]->Text="1000 seconds timeout occured while executing \""+
                          SettingsFrm->MLocationEdit->Text+" * -verifysets\"";
    int code=0;
    ConsoleFrm->Console->Lines->Add("Timeout Occured");
    TerminateProcess(pi.hProcess,code);
    //return ;
  }
  CloseHandle( pi.hProcess );
  CloseHandle( pi.hThread );

  if (!FileExists(fname)) {
    ShowMessage(AnsiString(fname)+" doesn't exist - operation failed.");
    VerForm->Visible=false;Form1->Enabled=true;
    ConsoleFrm->Console->Lines->Add("Something went wrong, no disk space in temp dir?");
    return;
  }

//--------------- start parsing verification data --------------------
  ConsoleFrm->Console->Lines->Add("Starting Verification Information parsing");
  VerForm->Label2->Font->Style = TFontStyles();
  VerForm->Label3->Font->Style =TFontStyles()<< fsBold;
  VerForm->ProgressBar->Position=0;
  VerForm->Update();

  int statcol=Form1->ColOf("Status");
  TForm1::stats_s stats;
  FILE *fp;

  if (0==(fp=fopen(fname,"r")) ) {
    ShowMessage(strerror(errno));
    VerForm->Visible=false;Form1->Enabled=true;
    return;
  }

  TFindParams findparams;
  char rom[64],msg[128];

  Form1->Update();
  Form1->Grid->BeginUpdate();
  int romcol=Form1->ColOf("ROM");
  TPoint res;
  int row,games=0;

  Form1->Grid->Options >> goRowSelect;
  Form1->Grid->Col=romcol;
  ConsoleFrm->Console->Lines->Add("VERIFY ROMS:");
  memset(&stats, 0, sizeof(stats));
  
  while (fgets(buff,1024,fp)) {
    ConsoleFrm->Console->Lines->Add(buff);
    if (games%10) {
      VerForm->ProgressBar->Position=games;
      VerForm->Update();
    }
    if (!strncmp(buff,"romset",5)) {
      sscanf(buff+6,"%s",rom);
      games++;
      stats.s_total++;
      findparams << fnFindInCurrentCol << fnMatchStart	<< fnMatchFull << fnMatchCase	;

      res=Form1->Grid->FindFirst(rom, findparams);
      row=res.y;

      if (row<0) continue;

      if (strstr(buff,"is good")) {
        Form1->Grid->AddImageIdx(0,row,0,haBeforeText,Advgrid::vaCenter);
        Form1->Grid->Cells[statcol][row]=0;
        stats.s_good++;
      }
      else if (strstr(buff,"is bad") && (files.find(AnsiString(rom)+".zip")==files.end())) {
        //Does not exist
        Form1->Grid->AddImageIdx(0,row,4,haBeforeText,Advgrid::vaCenter);
        Form1->Grid->Cells[statcol][row]=4;
        stats.s_notfound++;
      }
      else if (strstr(buff,"is bad") && (files.find(AnsiString(rom)+".zip")!=files.end())) {
        //Exists but is bad
        Form1->Grid->AddImageIdx(0,row,1,haBeforeText,Advgrid::vaCenter);
        Form1->Grid->Cells[statcol][row]=1;
        stats.s_notworking++;
      }
      else if (strstr(buff,"best available")) {
        Form1->Grid->AddImageIdx(0,row,3,haBeforeText,Advgrid::vaCenter);
        Form1->Grid->Cells[statcol][row]=3;
        stats.s_bestavailable++;
      }

      else {
        //exists but is of unknown condition
        Form1->Grid->AddImageIdx(0,row,6,haBeforeText,Advgrid::vaCenter);
        Form1->Grid->Cells[statcol][row]=6;
        stats.s_unknown++;
      }
    }//if romset
    
  }//while fgets
  Form1->Grid->Options << goRowSelect;

  Form1->Grid->EndUpdate();

  fclose(fp);
  DeleteFile(fname);
  ConsoleFrm->Console->Lines->Add("Parsing of Verification data Completed");
  ConsoleFrm->Console->Lines->Add("Saving statistics information");

  //save statistics
  Form1->SaveStats(stats);

  VerForm->Visible=false;Form1->Enabled=true;
  Form1->StatusBar->Panels->Items[0]->Text="";
  ConsoleFrm->Console->Lines->Add("------------------");
  Form1->SaveData();
  Screen->Cursor=crDefault;
}


//---------------------------------------------------------------------------

void __fastcall TForm1::GridColumnMove(TObject *Sender, int ACol,
      bool &Allow)
{
  if (ACol==ColOf("Status"))
    Allow=false;
  else
    Allow=true;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::GridColumnSize(TObject *Sender, int ACol,
      bool &Allow)
{
  if (ACol==ColOf("Status"))
    Allow=false;
  else
    Allow=true;
}
//---------------------------------------------------------------------------


//view legend
void __fastcall TForm1::LegendBtnClick(TObject *Sender)
{
  LegendFrm->Visible=!LegendFrm->Visible;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::GettingStarted1Click(TObject *Sender)
{
  HelpFrm->Visible=!HelpFrm->Visible;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StatsBtnClick(TObject *Sender)
{
  TIniFile *ini;
  TForm1::stats_s stats;
  ini = new TIniFile(ChangeFileExt(Application->ExeName, ".ini" ));

  //stats
  stats.s_total=ini->ReadInteger("STATS", "s_total",0);
  stats.s_good=ini->ReadInteger("STATS", "s_good",0);
  stats.s_notfound=ini->ReadInteger("STATS", "s_notfound",0);
  stats.s_notworking=ini->ReadInteger("STATS", "s_notworking",0);
  stats.s_bestavailable=ini->ReadInteger("STATS", "s_bestavailable",0);
  stats.s_unknown=ini->ReadInteger("STATS", "s_unknown",0);

  BioBox->Lines->Clear();
  BioBox->Lines->Append("Total Sets Supported in this version:" + AnsiString(Grid->RowCount-1));
  BioBox->Lines->Append("Total Sets Found:" +AnsiString(stats.s_total));
  BioBox->Lines->Append("Good Sets:" +AnsiString(stats.s_good));
  BioBox->Lines->Append("Missing Sets:" +AnsiString(stats.s_notfound));
  BioBox->Lines->Append("Not Working Sets:" +AnsiString(stats.s_notworking));
  BioBox->Lines->Append("Best Available:" +AnsiString(stats.s_bestavailable));
  BioBox->Lines->Append("Unknown Condition:" +AnsiString(stats.s_unknown));

  delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DisplayGameStatistics1Click(TObject *Sender)
{
  StatsBtnClick(Sender);  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveTableDataNow1Click(TObject *Sender)
{
  SaveData();  
}
//---------------------------------------------------------------------------

void __fastcall TForm1::autosaveplayedfield1Click(TObject *Sender)
{
  if (autosaveplayedfield1->Checked==false) {
    if ((MessageDlg("This will save table data before starting each game. Loading times will increase especially for network drives. Continue ?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
      return;
    autosaveplayedfield1->Checked=true;
  }
  else {
    autosaveplayedfield1->Checked=false;
  }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Readnplayersini1Click(TObject *Sender)
{
if ((MessageDlg("Parse nplayers.ini file data into table (1-10 seconds)?", mtConfirmation, TMsgDlgButtons() << mbYes << mbNo, 0) == mrNo))
  return;

  Screen->Cursor=crHourGlass;
  parseNplayers();
  SaveData();
  Screen->Cursor=crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::parseNplayers()
{
  TIniFile *ini;
  AnsiString ininame=ExtractFilePath(Application->ExeName)+"nplayers.ini";
  AnsiString romname;
  int romcol=Form1->ColOf("ROM");
  int playerscol=Form1->ColOf("Players");

   if (!FileExists(ininame))
   {
     MessageDlg("nplayers.ini not found in current path", mtError , TMsgDlgButtons()<< mbOK ,0);
     return;
   }

  ini = new TIniFile(ininame);
  Grid->BeginUpdate();
  for (int i=1;i< Form1->Grid->RowCount;i++) {
      romname=AnsiString(Form1->Grid->Cells[romcol][i]);
      if (!romname.Length()) continue;
      Grid->Cells[playerscol][i]=ini->ReadString("NPlayers", romname,"");
  }
  delete ini;
  Grid->EndUpdate();
}

