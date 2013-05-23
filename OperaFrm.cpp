//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OperaFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TFrmOpera *FrmOpera;
//---------------------------------------------------------------------------
__fastcall TFrmOpera::TFrmOpera(TComponent* Owner)
        : TForm(Owner)
{}

void TFrmOpera::Clear()
{
    CSpinEdit1->Text="0";
    Memo1->Text="";
}

//---------------------------------------------------------------------------
void __fastcall TFrmOpera::BitBtn1Click(TObject *Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFrmOpera::BitBtn2Click(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

