//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("smfe.res");
USEFORM("smfe1.cpp", Form1);
USEFORM("Unit2.cpp", SettingsFrm);
USEUNIT("..\..\Imports\PAINTXLib_TLB.cpp");
USEFORM("AboutForm.cpp", AboutFrm);
USEFORM("ExtractFrm.cpp", ExtractForm);
USEFORM("console.cpp", ConsoleFrm);
USEFORM("Unit3.cpp", MAMEOpts);
USEFORM("verfrm.cpp", VerForm);
USEFORM("Legend.cpp", LegendFrm);
USEFORM("HelpForm.cpp", HelpFrm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TForm1), &Form1);
     Application->CreateForm(__classid(TSettingsFrm), &SettingsFrm);
     Application->CreateForm(__classid(TAboutFrm), &AboutFrm);
     Application->CreateForm(__classid(TExtractForm), &ExtractForm);
     Application->CreateForm(__classid(TConsoleFrm), &ConsoleFrm);
     Application->CreateForm(__classid(TMAMEOpts), &MAMEOpts);
     Application->CreateForm(__classid(TVerForm), &VerForm);
     Application->CreateForm(__classid(TLegendFrm), &LegendFrm);
     Application->CreateForm(__classid(THelpFrm), &HelpFrm);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
