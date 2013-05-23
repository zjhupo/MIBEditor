//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CaseFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCase *frmCase;
//---------------------------------------------------------------------------
__fastcall TfrmCase::TfrmCase(TComponent* Owner)
        : TForm(Owner)
{
    Memo1->Clear();
    Edit1->Text = "";
    Edit2->Text = "";
    value = new TStringList();
    value->Delimiter='|';
    edtDef->Text = "0";
}
//---------------------------------------------------------------------------

AnsiString TfrmCase::getValue()
{
    return Memo1->Text;
}
void __fastcall TfrmCase::Button1Click(TObject *Sender)
{
    if(Edit1->Text=="" || Edit2->Text=="" || ComboBox1->ItemIndex==-1)
        return;
    if(Edit2->Text.Pos("\"")>0 || Edit2->Text.Pos("\'")>0)
        return;
    TStringList *M=new TStringList();
    M->Add(Edit1->Text);
    M->Add(Edit2->Text);
    M->Add(ComboBox2->Text);
    value->Add(M->CommaText);
    Memo1->Lines->Text = value->DelimitedText;
    delete M;
}
//---------------------------------------------------------------------------
void __fastcall TfrmCase::ComboBox1Change(TObject *Sender)
{
    ComboBox2->ItemIndex = ComboBox1->ItemIndex;

}
//---------------------------------------------------------------------------
void __fastcall TfrmCase::Button2Click(TObject *Sender)
{
    value->Text = "";
    Memo1->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TfrmCase::FormDestroy(TObject *Sender)
{
    delete value;
}
//---------------------------------------------------------------------------

void TfrmCase::AddValue(AnsiString vv)
{
    value->DelimitedText = vv;
    Memo1->Text = value->DelimitedText;
}

