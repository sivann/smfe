//---------------------------------------------------------------------------

#ifndef AboutFormH
#define AboutFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TAboutFrm : public TForm
{
__published:	// IDE-managed Components
  TLabel *Label1;
  TLabel *Label2;
  TLabel *Label3;
  TBitBtn *BitBtn1;
private:	// User declarations
public:		// User declarations
  __fastcall TAboutFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutFrm *AboutFrm;
//---------------------------------------------------------------------------
#endif
