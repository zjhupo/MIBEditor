//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DeviceInfoFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmDeviceInfo *FrmDeviceInfo;
//---------------------------------------------------------------------------
__fastcall TFrmDeviceInfo::TFrmDeviceInfo(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TFrmDeviceInfo::FormCreate(TObject *Sender)
{
    Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFrmDeviceInfo::BitBtn1Click(TObject *Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFrmDeviceInfo::BitBtn2Click(TObject *Sender)
{
    ModalResult = mrCancel;
}
//---------------------------------------------------------------------------

void TFrmDeviceInfo::Clear()
{
    Edit1->Text = "";
    Edit2->Text = "";
    Edit3->Text = "";
    Edit4->Text = "";
    Edit5->Text = "";
    Edit6->Text = "";
    CheckBox1->Checked = true;
}

