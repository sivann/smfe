//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RXCtrls"
#pragma resource "*.dfm"
TMAMEOpts *MAMEOpts;
//---------------------------------------------------------------------------
__fastcall TMAMEOpts::TMAMEOpts(TComponent* Owner)
  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMAMEOpts::brbarChange(TObject *Sender)
{
  brightness->Caption=(float)(brbar->Position/10.0);
}
//---------------------------------------------------------------------------
void __fastcall TMAMEOpts::gbarChange(TObject *Sender)
{
   gamma->Caption=(float)(gbar->Position/10.0);
}
//---------------------------------------------------------------------------



void __fastcall TMAMEOpts::MOKBtnClick(TObject *Sender)
{
  writeMoptions();
}

void  TMAMEOpts::writeMoptions()
{
TIniFile *ini;

  ini = new TIniFile(ChangeFileExt( Application->ExeName, ".ini" ));

  ini->WriteBool("MAMEOPTS", "UseSettings",usethem->Checked);

  ini->WriteString("MAMEOPTS", "snpath",snapshot->Text);
  ini->WriteBool("MAMEOPTS", "SnapDirUse",snapuse->Checked);

  ini->WriteString("MAMEOPTS", "RomPath",rompath->Text);
  ini->WriteBool("MAMEOPTS", "RomPathUse",romuse->Checked);

  ini->WriteString("MAMEOPTS", "FrameSkip",frameskip->Text);
  ini->WriteBool("MAMEOPTS", "FrameSkipAuto",frameskipauto->Checked);

  ini->WriteBool("MAMEOPTS", "ScanLines",scanlines->Checked);
  ini->WriteBool("MAMEOPTS", "HWStretch",hwstretch->Checked);
  ini->WriteBool("MAMEOPTS", "switchres",switchres->Checked);
  ini->WriteBool("MAMEOPTS", "switchbpp",switchbpp->Checked);
  ini->WriteBool("MAMEOPTS", "window",window->Checked);

  //Artwork
  ini->WriteBool("MAMEOPTS", "artwork",artwork->Checked);
  ini->WriteBool("MAMEOPTS", "bezels",bezels->Checked);
  ini->WriteBool("MAMEOPTS", "overlays",overlays->Checked);
  ini->WriteBool("MAMEOPTS", "backdrops",backdrops->Checked);


  ini->WriteBool("MAMEOPTS", "norotate",norotate->Checked);
  ini->WriteBool("MAMEOPTS", "ror",ror->Checked);
  ini->WriteBool("MAMEOPTS", "rol",rol->Checked);
  ini->WriteBool("MAMEOPTS", "autoror",autoror->Checked);
  ini->WriteBool("MAMEOPTS", "autorol",autorol->Checked);
  ini->WriteBool("MAMEOPTS", "flipy",flipy->Checked);
  ini->WriteBool("MAMEOPTS", "flipx",flipx->Checked);

  ini->WriteInteger("MAMEOPTS", "Effects",Effects->ItemIndex);


  ini->WriteInteger("MAMEOPTS", "Brightness",brbar->Position);
  ini->WriteInteger("MAMEOPTS", "Gamma",gbar->Position);

  ini->WriteInteger("MAMEOPTS", "VolDB",volbar->Position);
  if (!SRate->Text.Length()) {
    SRate->Text="44100";
  }
  ini->WriteString("MAMEOPTS", "SampleRate",SRate->Text);


  ini->WriteBool("MAMEOPTS", "Mouse",mouse->Checked);
  ini->WriteBool("MAMEOPTS", "Joystick",joystick->Checked);
  ini->WriteBool("MAMEOPTS", "Steadykey",steadykey->Checked);
  ini->WriteBool("MAMEOPTS", "Lightgun",lightgun->Checked);
  ini->WriteBool("MAMEOPTS", "LEDEmul",ledemul->Checked);
  ini->WriteBool("MAMEOPTS", "UseController",wantctrlr->Checked);
  ini->WriteString("MAMEOPTS", "ControllerName",ctrlredt->Text);

  ini->WriteBool("MAMEOPTS", "Cheats",cheats->Checked);

  //D3D
  ini->WriteBool("MAMEOPTS", "Direct3D",direct3d->Checked);
  ini->WriteBool("MAMEOPTS", "D3Dtexmanage",d3dtexmanage->Checked);
  ini->WriteInteger("MAMEOPTS", "D3Dscanlines",d3dscanbar->Position);
  ini->WriteInteger("MAMEOPTS", "D3Dfilter",d3dfilter->ItemIndex);
  ini->WriteInteger("MAMEOPTS", "D3Deffect",d3deffect->ItemIndex);

  ini->WriteBool("MAMEOPTS", "SkipGameInfo",skipgameinfo->Checked);
  ini->WriteBool("MAMEOPTS", "SkipDisclaimer",skipdisclaimer->Checked);

  delete ini;
}

//---------------------------------------------------------------------------

void  TMAMEOpts::readMoptions()
{
TIniFile *ini;

  ini = new TIniFile(ChangeFileExt(Application->ExeName, ".ini" ));
  usethem->Checked=ini->ReadBool("MAMEOPTS", "UseSettings",false);

  snapshot->Text=ini->ReadString("MAMEOPTS", "snpath","c:\\");

  snapuse->Checked=ini->ReadBool("MAMEOPTS", "SnapDirUse",false);

  rompath->Text=ini->ReadString("MAMEOPTS", "RomPath","");
  romuse->Checked=ini->ReadBool("MAMEOPTS", "RomPathUse",false);


  frameskip->Text=ini->ReadString("MAMEOPTS", "FrameSkip","");
  frameskipauto->Checked=ini->ReadBool("MAMEOPTS", "FrameSkipAuto",true);

  scanlines->Checked=ini->ReadBool("MAMEOPTS", "ScanLines",false);
  hwstretch->Checked=ini->ReadBool("MAMEOPTS", "HWStretch",true);
  switchres->Checked=ini->ReadBool("MAMEOPTS", "switchres",true);
  switchbpp->Checked=ini->ReadBool("MAMEOPTS", "switchbpp",true);
  window->Checked=ini->ReadBool("MAMEOPTS", "window",false);

  //ArtWork
  artwork->Checked=ini->ReadBool("MAMEOPTS", "artwork",true);
  bezels->Checked=ini->ReadBool("MAMEOPTS", "bezels",true);
  overlays->Checked=ini->ReadBool("MAMEOPTS", "overlays",true);
  backdrops->Checked=ini->ReadBool("MAMEOPTS", "backdrops",true);

  norotate->Checked=ini->ReadBool("MAMEOPTS", "norotate",false);
  ror->Checked=ini->ReadBool("MAMEOPTS", "ror",false);
  rol->Checked=ini->ReadBool("MAMEOPTS", "rol",false);

  autoror->Checked=ini->ReadBool("MAMEOPTS", "autoror",false);
  autorol->Checked=ini->ReadBool("MAMEOPTS", "autorol",false);


  flipy->Checked=ini->ReadBool("MAMEOPTS", "flipy",false);
  flipx->Checked=ini->ReadBool("MAMEOPTS", "flipx",false);

  Effects->ItemIndex=ini->ReadInteger("MAMEOPTS", "Effects",0);


  brbar->Position=ini->ReadInteger("MAMEOPTS", "Brightness",10);
  gbar->Position=ini->ReadInteger("MAMEOPTS", "Gamma",10);

  volbar->Position=ini->ReadInteger("MAMEOPTS", "VolDB",32);
  SRate->Text=ini->ReadString("MAMEOPTS", "SampleRate",AnsiString(44100));

  mouse->Checked=ini->ReadBool("MAMEOPTS", "Mouse",false);
  joystick->Checked=ini->ReadBool("MAMEOPTS", "Joystick",false);
  steadykey->Checked=ini->ReadBool("MAMEOPTS", "Steadykey",false);
  lightgun->Checked=ini->ReadBool("MAMEOPTS", "Lightgun",false);
  ledemul->Checked=ini->ReadBool("MAMEOPTS", "LEDEmul",false);
  wantctrlr->Checked=ini->ReadBool("MAMEOPTS", "UseController",false);
  ctrlredt->Text=ini->ReadString("MAMEOPTS", "ControllerName","");

  cheats->Checked=ini->ReadBool("MAMEOPTS", "Cheats",true);

  //D3D
  direct3d->Checked=ini->ReadBool("MAMEOPTS", "Direct3D",false);
  d3dtexmanage->Checked=ini->ReadBool("MAMEOPTS", "D3Dtexmanage",true);
  d3dscanbar->Position=ini->ReadInteger("MAMEOPTS", "D3Dscanlines",100);
  d3dfilter->ItemIndex=ini->ReadInteger("MAMEOPTS", "D3Dfilter",0);
  d3deffect->ItemIndex=ini->ReadInteger("MAMEOPTS", "D3Deffect",0);

  skipgameinfo->Checked=ini->ReadBool("MAMEOPTS", "SkipGameInfo",false);
  skipdisclaimer->Checked=ini->ReadBool("MAMEOPTS", "SkipDisclaimer",false);

  delete ini;
}

//---------------------------------------------------------------------------
//parse mame options and create the moptions command line string
void  TMAMEOpts::ParseMoptions()
{

  moptions="";
  if  (!usethem->Checked) return;

  if (snapuse->Checked)
    moptions+=" -snapshot_directory " + snapshot->Text +" ";

  if (romuse->Checked)
    moptions+=" -rompath " + rompath->Text +" ";

  if (scanlines->Checked)
    moptions+=" -scanlines ";
  else
    moptions+=" -noscanlines ";


  if (hwstretch->Checked)
    moptions+=" -hwstretch ";
  else 
    moptions+=" -nohwstretch ";

  if (switchres->Checked)
    moptions+=" -switchres ";
  else
    moptions+=" -noswitchres ";

  if (switchbpp->Checked)
    moptions+=" -switchbpp ";
  else
    moptions+=" -noswitchbpp ";

  if (window->Checked)
    moptions+=" -window ";
  else
    moptions+=" -nowindow ";

  moptions+=" -full_screen_brightness "+AnsiString((float)(brbar->Position/10.0))+" ";
  moptions+=" -gamma "+AnsiString((float)(gbar->Position/10.0))+" ";

  //artwork
  if (artwork->Checked) {
    if (bezels->Checked)
      moptions+=" -use_bezels ";
    else
      moptions+=" -nouse_bezels ";

    if (overlays->Checked)
      moptions+=" -use_overlays ";
    else
      moptions+=" -nouse_overlays ";

    if (backdrops->Checked)
      moptions+=" -use_backdrops ";
    else
      moptions+=" -nouse_backdrops ";
  }
  else
    moptions+=" -noartwork ";


  //Rotation
  if (norotate->Checked)
    moptions+=" -norotate ";
  else
    moptions+=" -nonorotate ";

  if (ror->Checked)
    moptions+=" -ror ";
  else
    moptions+=" -noror ";

  if (rol->Checked)
    moptions+=" -rol ";
  else
    moptions+=" -norol ";


  if (autoror->Checked)
    moptions+=" -autoror ";
  else
    moptions+=" -noautoror ";

  if (autorol->Checked)
    moptions+=" -autorol ";
  else
    moptions+=" -noautorol ";


  if (flipy->Checked)
    moptions+=" -flipy ";
  else
    moptions+=" -noflipy ";

  if (flipx->Checked)
    moptions+=" -flipx ";
  else
    moptions+=" -noflipx ";

  switch (Effects->ItemIndex) {
    case 0: break;
    case 1: moptions+=" -effect scan25 ";break;
    case 2: moptions+=" -effect scan50 ";break;
    case 3: moptions+=" -effect scan75 ";break;
    case 4: moptions+=" -effect rgb3 ";break;
    case 5: moptions+=" -effect rgb4 ";break;
    case 6: moptions+=" -effect rgb6 ";break;
    case 7: moptions+=" -effect rgb16 ";break;
  }

 if (mouse->Checked)
    moptions+=" -mouse ";
  else
    moptions+=" -nomouse ";

  if (joystick->Checked)
    moptions+=" -joystick ";
  else
    moptions+=" -nojoystick ";

  if (lightgun->Checked)
    moptions+=" -lightgun ";
  else
    moptions+=" -nolightgun ";


  if (wantctrlr->Checked && (ctrlredt->Text.Length()>1))
    moptions+=" -ctrlr " + ctrlredt->Text;



  if (steadykey->Checked)
    moptions+=" -steadykey ";
  else
    moptions+=" -nosteadykey ";

  if (ledemul->Checked)
    moptions+=" -keyboard_leds ";
  else
    moptions+=" -nokeyboard_leds ";



  moptions+=" -samplerate " + SRate->Text + " ";
  moptions+=" -volume "+AnsiString((int(volbar->Position)-32))+" ";

  if (cheats->Checked)
    moptions+=" -cheat ";
  else
    moptions+=" -nocheat ";

  if (skipgameinfo->Checked)
    moptions+=" -skip_gameinfo ";

  if (skipdisclaimer->Checked)
    moptions+=" -skip_disclaimer ";

  if (direct3d->Checked) {
    moptions+=" -direct3d ";

    if (d3dtexmanage->Checked)
      moptions+=" -d3dtexmanage ";
    else
      moptions+=" -nod3dtexmanage ";    

    moptions+=" -d3dscan " + AnsiString(d3dscanbar->Position) + " ";


    switch (d3dfilter->ItemIndex) {
      case 0: moptions+=" -d3dfilter 0 ";break;
      case 1: moptions+=" -d3dfilter 1 ";break;
      case 2: moptions+=" -d3dfilter 2 ";break;
      case 3: moptions+=" -d3dfilter 3 ";break;
      case 4: moptions+=" -d3dfilter 4 ";break;
    }

    switch (d3deffect->ItemIndex) {
      case 0: break;
      case 1: moptions+=" -d3deffect sharp ";break;
      case 2: moptions+=" -d3deffect scan25 ";break;
      case 3: moptions+=" -d3deffect scan50 ";break;
      case 4: moptions+=" -d3deffect scan75 ";break;
      case 5: moptions+=" -d3deffect scan75v ";break;
      case 6: moptions+=" -d3deffect rgbmicro ";break;
      case 7: moptions+=" -d3deffect  rgbtiny ";break;
      case 8: moptions+=" -d3deffect  rgb3 ";break;
      case 9: moptions+=" -d3deffect  rgb4 ";break;
      case 10: moptions+=" -d3deffect  rgb4v ";break;
      case 11: moptions+=" -d3deffect  rgb6 ";break;
      case 12: moptions+=" -d3deffect  rgb16 ";break;
      case 13: moptions+=" -d3deffect  rgbminmask ";break;
      case 14: moptions+=" -d3deffect  dotmedmask ";break;
      case 15: moptions+=" -d3deffect  rgbmedmask ";break;
      case 16: moptions+=" -d3deffect  dotmedbright ";break;
      case 17: moptions+=" -d3deffect  rgbmaxbright ";break;
      case 18: moptions+=" -d3deffect  apperturegrille ";break;
      case 19: moptions+=" -d3deffect  auto ";break;
    }
  }//direct3d
}

//---------------------------------------------------------------------------
void __fastcall TMAMEOpts::frameskipautoClick(TObject *Sender)
{
  if (frameskipauto->Checked)
    frameskip->Enabled=false;
  else
    frameskip->Enabled=true;  
}
//---------------------------------------------------------------------------

void __fastcall TMAMEOpts::SRateKeyPress(TObject *Sender, char &Key)
{
  Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TMAMEOpts::volbarChange(TObject *Sender)
{
  Volume->Caption=AnsiString(int(volbar->Position)-32)+"dB";
}
//---------------------------------------------------------------------------

void __fastcall TMAMEOpts::d3dscanbarChange(TObject *Sender)
{
  scanlbl->Caption=AnsiString((float)(d3dscanbar->Position))+AnsiString("%");
  if (d3dscanbar->Position==100)
    scanlbl->Caption="Disabled";
}
//---------------------------------------------------------------------------

