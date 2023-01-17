//---------------------------------------------------------------------------

#ifndef verfrmH
#define verfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TVerForm : public TForm
{
__published:	// IDE-managed Components
  TProgressBar *ProgressBar;
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Labeltit;
  TLabel *Label3;
private:	// User declarations
public:		// User declarations
  __fastcall TVerForm(TComponent* Owner);
  void __fastcall TVerForm::updPbar();  
};
//---------------------------------------------------------------------------
extern PACKAGE TVerForm *VerForm;
//---------------------------------------------------------------------------
#endif
