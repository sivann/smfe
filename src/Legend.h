//---------------------------------------------------------------------------

#ifndef LegendH
#define LegendH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLegendFrm : public TForm
{
__published:	// IDE-managed Components
  TImage *Image0;
  TImage *Image1;
  TImage *Image2;
  TImage *Image3;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TLabel *Label4;
  TImage *Image4;
  TLabel *Label5;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
  __fastcall TLegendFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLegendFrm *LegendFrm;
//---------------------------------------------------------------------------
#endif
