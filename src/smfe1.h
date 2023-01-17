//---------------------------------------------------------------------------

#ifndef smfe1H
#define smfe1H
#include "AdvGrid.hpp"
#include "ImageEn.hpp"
#include "ImageEnView.hpp"
#include "RXCtrls.hpp"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>

#include "AdvGrid.hpp"
#include "ImageEn.hpp"
#include "ImageEnView.hpp"
#include "RXCtrls.hpp"
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <StdCtrls.hpp>
#include <ToolWin.hpp>


#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvGrid.hpp"
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "PAINTXLib_OCX.h"
#include <OleServer.hpp>
#include "ImageEn.hpp"
#include "ImageEnProc.hpp"
#include "ImageEnView.hpp"
#include "ImageEnIO.hpp"
#include <Buttons.hpp>
#include "RXCtrls.hpp"
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>

#include <set.h>
#include "BaseGrid.hpp"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
  TAdvStringGrid *Grid;
  TStatusBar *StatusBar;
  TMainMenu *MainMenu1;
  TMenuItem *Menu1;
  TMenuItem *DefineSettings1;
  TMenuItem *Actions1;
  TMenuItem *Readgames1;
  TMenuItem *Editmameini1;
  TMenuItem *Createmameini1;
  TMenuItem *Help1;
  TMenuItem *About1;
  TPanel *Panel1;
  TTabControl *TabControl1;
  TImageEn *ImageEn1;
  TRxLabel *ImgLbl;
  TSplitter *Splitter1;
  TCoolBar *CoolBar1;
  TToolBar *ToolBar1;
  TToolButton *ToolButton1;
  TEdit *FindBox;
  TToolButton *ToolButton2;
  TTimer *GridTimer;
  TTimer *proctimer;
  TMenuItem *ShowConsole;
  TToolButton *ToolButton3;
  TMenuItem *ExportGamelist1;
  TMenuItem *SaveColumnSizes1;
  TSaveDialog *ExportDlg;
  TMenuItem *Readhistorydat1;
  TMenuItem *N3;
  TSplitter *Splitter2;
  TImageList *ImageList1;
  TToolButton *KillBtn;
  TToolButton *ConsoleTbtn;
  TToolButton *FindBtn;
  TToolButton *FindNextBtn;
  TToolButton *FindPrevBtn;
  TToolButton *PlayBtn;
  TMenuItem *Actions2;
  TMenuItem *EditOptions1;
  TMenuItem *N1;
  TMenuItem *ROMs1;
  TMenuItem *Checkexistance1;
  TMenuItem *Verify1;
  TImageList *GridImlist;
  TToolButton *LegendBtn;
  TToolButton *ToolButton7;
  TMenuItem *GettingStarted1;
  TToolButton *StatsBtn;
  TToolButton *ToolButton8;
  TMenuItem *DisplayGameStatistics1;
  TMenuItem *SaveTableDataNow1;
  TMenuItem *N2;
  TMenuItem *autosaveplayedfield1;
  TRichEdit *BioBox;
  TMenuItem *Readnplayersini1;
  void __fastcall DefineSettings1Click(TObject *Sender);
  void __fastcall Readgames1Click(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
  void __fastcall GridSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
  void __fastcall Createmameini1Click(TObject *Sender);
  void __fastcall Editmameini1Click(TObject *Sender);
  void __fastcall About1Click(TObject *Sender);
  void __fastcall showImage(int col,int row);
  void __fastcall TabControl1Change(TObject *Sender);
  void __fastcall GridTimerTimer(TObject *Sender);
  void __fastcall FindBoxKeyPress(TObject *Sender, char &Key);
  void __fastcall proctimerTimer(TObject *Sender);
  void __fastcall ShowConsoleClick(TObject *Sender);
  void __fastcall GridDblClick(TObject *Sender);
  void __fastcall GridCanSort(TObject *Sender, int ACol, bool &DoSort);
  void __fastcall GridClickSort(TObject *Sender, int ACol);
  void __fastcall SaveColumnSizes1Click(TObject *Sender);
  void __fastcall ExportGamelist1Click(TObject *Sender);
  void __fastcall Readhistorydat1Click(TObject *Sender);
  void __fastcall GridKeyPress(TObject *Sender, char &Key);
  void __fastcall KillBtnClick(TObject *Sender);
  void __fastcall FindBtnClick(TObject *Sender);
  void __fastcall FindNextBtnClick(TObject *Sender);
  void __fastcall FindPrevBtnClick(TObject *Sender);
  void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall PlayBtnClick(TObject *Sender);
  void __fastcall EditOptions1Click(TObject *Sender);
  void __fastcall Checkexistance1Click(TObject *Sender);
  void __fastcall Verify1Click(TObject *Sender);
  void __fastcall GridColumnMove(TObject *Sender, int ACol, bool &Allow);
  void __fastcall GridColumnSize(TObject *Sender, int ACol, bool &Allow);
  void __fastcall LegendBtnClick(TObject *Sender);
  void __fastcall GettingStarted1Click(TObject *Sender);
  void __fastcall StatsBtnClick(TObject *Sender);
  void __fastcall DisplayGameStatistics1Click(TObject *Sender);
  void __fastcall SaveTableDataNow1Click(TObject *Sender);
  void __fastcall autosaveplayedfield1Click(TObject *Sender);
  void __fastcall Readnplayersini1Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
  __fastcall TForm1(TComponent* Owner);
  void __fastcall   SavePaths();
  void __fastcall   SaveData();
  typedef struct  {
    int s_total,s_good,s_notfound,s_notworking,s_bestavailable,s_unknown;
  } stats_s; //statistics
  void __fastcall   SaveStats(stats_s stats);
  void __fastcall   PlayGame();
  int __fastcall    ColOf(AnsiString colname );
  void __fastcall    updateIcons();
  void __fastcall    hideCols(bool hide);
  void __fastcall    parseNplayers();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
