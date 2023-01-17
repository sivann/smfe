//---------------------------------------------------------------------------

#ifndef consoleH
#define consoleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TConsoleFrm : public TForm
{
__published:	// IDE-managed Components
  TMemo *Console;
  TPopupMenu *PopupMenu1;
  TMenuItem *Clear1;
  TMenuItem *SelectAll;
  TMenuItem *Copy1;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall FormHide(TObject *Sender);
  void __fastcall Clear1Click(TObject *Sender);
  void __fastcall SelectAllClick(TObject *Sender);
  void __fastcall Copy1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall TConsoleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConsoleFrm *ConsoleFrm;
//---------------------------------------------------------------------------
#endif
