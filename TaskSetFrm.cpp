//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TaskSetFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmTaskSet *FrmTaskSet;
//---------------------------------------------------------------------------
__fastcall TFrmTaskSet::TFrmTaskSet(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TFrmTaskSet::FormCreate(TObject *Sender)
{
    Edit1->Text = "";
    Memo1->Text = "";
}
//---------------------------------------------------------------------------

