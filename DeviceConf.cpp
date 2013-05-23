//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("mainFrm.cpp", frmMain);
USEFORM("DeviceInfoFrm.cpp", FrmDeviceInfo);
USEFORM("OperaFrm.cpp", FrmOpera);
USEFORM("AnayValueFrm.cpp", FrmAnayValue);
USEFORM("TaskSetFrm.cpp", FrmTaskSet);
USEFORM("AboutFrm.cpp", frmAbout);
USEFORM("TelnetEditFrm.cpp", FrmTelnetEdit);
USEFORM("CaseFrm.cpp", frmCase);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
     Application->Initialize();
     Application->CreateForm(__classid(TfrmMain), &frmMain);
     Application->Run();
  }
  catch (Exception &exception)
  {
     Application->ShowException(&exception);
  }
  catch (...)
  {
     try
     {
       throw Exception("");
     }
     catch (Exception &exception)
     {
       Application->ShowException(&exception);
     }
  }
  return 0;
}
//---------------------------------------------------------------------------
