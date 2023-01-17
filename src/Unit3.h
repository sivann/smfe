//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "RXCtrls.hpp"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMAMEOpts : public TForm
{
__published:	// IDE-managed Components
  TPageControl *PageControl1;
  TTabSheet *TabSheet1;
  TTabSheet *TabSheet2;
  TEdit *Edit2;
  TCheckBox *CheckBox2;
  TGroupBox *GroupBox1;
  TLabel *Label1;
  TEdit *frameskip;
  TLabel *Label2;
  TCheckBox *frameskipauto;
  TGroupBox *GroupBox2;
  TCheckBox *scanlines;
  TCheckBox *switchres;
  TCheckBox *switchbpp;
  TGroupBox *GroupBox3;
  TTrackBar *brbar;
  TLabel *brightness;
  TGroupBox *GroupBox4;
  TTrackBar *gbar;
  TLabel *gamma;
  TRadioGroup *Effects;
  TTabSheet *TabSheet3;
  TGroupBox *GroupBox5;
  TComboBox *SRate;
  TGroupBox *GroupBox6;
  TCheckBox *joystick;
  TCheckBox *mouse;
  TGroupBox *GroupBox7;
  TTrackBar *volbar;
  TLabel *Volume;
  TTabSheet *TabSheet4;
  TCheckBox *cheats;
  TCheckBox *hwstretch;
  TBitBtn *MOKBtn;
  TCheckBox *usethem;
  TCheckBox *window;
  TGroupBox *GroupBox8;
  TCheckBox *norotate;
  TCheckBox *ror;
  TCheckBox *rol;
  TCheckBox *flipx;
  TCheckBox *flipy;
  TCheckBox *steadykey;
  TGroupBox *GroupBox9;
  TCheckBox *snapuse;
  TLabel *Label3;
  TEdit *snapshot;
  TGroupBox *GroupBox10;
  TEdit *rompath;
  TCheckBox *romuse;
  TLabel *Label5;
  TCheckBox *lightgun;
  TCheckBox *ledemul;
  TPanel *Panel1;
  TCheckBox *wantctrlr;
  TEdit *ctrlredt;
  TCheckBox *autoror;
  TCheckBox *autorol;
  TTabSheet *TabSheet5;
  TGroupBox *GroupBox11;
  TCheckBox *d3dtexmanage;
  TRadioGroup *d3dfilter;
  TCheckBox *direct3d;
  TLabel *Label4;
  TRadioGroup *d3deffect;
  TGroupBox *GroupBox12;
  TTrackBar *d3dscanbar;
  TLabel *scanlbl;
  TRadioGroup *RadioGroup1;
  TCheckBox *artwork;
  TCheckBox *bezels;
  TCheckBox *skipgameinfo;
  TCheckBox *overlays;
  TCheckBox *backdrops;
  TCheckBox *skipdisclaimer;
  void __fastcall brbarChange(TObject *Sender);
  void __fastcall gbarChange(TObject *Sender);
  void __fastcall MOKBtnClick(TObject *Sender);
  void __fastcall frameskipautoClick(TObject *Sender);
  void __fastcall SRateKeyPress(TObject *Sender, char &Key);
  void __fastcall volbarChange(TObject *Sender);
  void __fastcall d3dscanbarChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TMAMEOpts(TComponent* Owner);
  void    ParseMoptions();
  void    writeMoptions();
  void    readMoptions();  
  AnsiString moptions;  
};
//---------------------------------------------------------------------------
extern PACKAGE TMAMEOpts *MAMEOpts;
//---------------------------------------------------------------------------
#endif
