//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSettingsFrm : public TForm
{
__published:	// IDE-managed Components
  TGroupBox *GroupBox1;
  TEdit *MLocationEdit;
  TLabel *Label1;
  TBitBtn *SOkBtn;
  TGroupBox *GroupBox2;
  TEdit *ArtworkEdt;
  TEdit *CabinetEdt;
  TEdit *FlyerEdt;
  TEdit *SnapshotEdt;
  TBitBtn *SCancelBtn;
  TStaticText *StaticText1;
  TStaticText *StaticText2;
  TStaticText *StaticText3;
  TStaticText *StaticText4;
  TCheckBox *AutoExtract;
  TGroupBox *GroupBox3;
  TCheckBox *png;
  TCheckBox *jpg;
  TCheckBox *gif;
  TCheckBox *bmp;
  TCheckBox *tif;
  TCheckBox *ico;
  TGroupBox *GroupBox4;
  TEdit *HistEdt;
  TLabel *Label2;
  TBitBtn *AutoFillBtn;
  void __fastcall SOkBtnClick(TObject *Sender);
  void __fastcall HistEdtEnter(TObject *Sender);
  void __fastcall AutoFillBtnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TSettingsFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsFrm *SettingsFrm;
//---------------------------------------------------------------------------
#endif
