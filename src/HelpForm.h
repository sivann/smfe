//---------------------------------------------------------------------------

#ifndef HelpFormH
#define HelpFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class THelpFrm : public TForm
{
__published:	// IDE-managed Components
  TMemo *HelpMemo;
private:	// User declarations
public:		// User declarations
  __fastcall THelpFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THelpFrm *HelpFrm;
//---------------------------------------------------------------------------
#endif
