//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AboutFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
__fastcall TfrmAbout::TfrmAbout(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TfrmAbout::FormClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmAbout::SpeedButton1Click(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------


