//---------------------------------------------------------------------------

#ifndef ExtractFrmH
#define ExtractFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TExtractForm : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TLabel *ExLbl;
  TLabel *ParLbl;
  TProgressBar *ProgressBar;
private:	// User declarations
public:		// User declarations
  __fastcall TExtractForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExtractForm *ExtractForm;
//---------------------------------------------------------------------------
#endif
