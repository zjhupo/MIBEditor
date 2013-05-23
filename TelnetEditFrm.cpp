//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TelnetEditFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmTelnetEdit *FrmTelnetEdit;
//---------------------------------------------------------------------------
__fastcall TFrmTelnetEdit::TFrmTelnetEdit(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TFrmTelnetEdit::Button1Click(TObject *Sender)
{
    if(verify())
        ModalResult = mrOk;
    else
        ShowMessage("ÃüÁî¸ñÊ½´íÎó!");
}
//---------------------------------------------------------------------------
void __fastcall TFrmTelnetEdit::Button2Click(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

bool TFrmTelnetEdit::verify()
{
    bool ret=true;
    if(Memo1->Lines->Count==0)
        ret = false;
    else if(Memo1->Lines->Strings[Memo1->Lines->Count-1].Pos("!end!")==0)
        ret = false;
    return ret;
}

