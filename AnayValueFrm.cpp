//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AnayValueFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmAnayValue *FrmAnayValue;
//---------------------------------------------------------------------------
__fastcall TFrmAnayValue::TFrmAnayValue(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
int TFrmAnayValue::ShowValue(AnsiString s1,AnsiString s2)
{
    ListBox1->Items->CommaText = s1;
    ListBox2->Items->CommaText = s2;
    return ShowModal();
}

AnsiString TFrmAnayValue::getS1()
{
    return ListBox1->Items->CommaText;
}

AnsiString TFrmAnayValue::getS2()
{
    return ListBox2->Items->CommaText;
}

void __fastcall TFrmAnayValue::ListBox1Click(TObject *Sender)
{
    ListBox2->ItemIndex = ListBox1->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::ListBox2Click(TObject *Sender)
{
    ListBox1->ItemIndex = ListBox2->ItemIndex;

}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::FormCreate(TObject *Sender)
{
    Edit1->Text = "";
    Edit2->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::Button1Click(TObject *Sender)
{
    ListBox1->Items->Add(Edit1->Text);
    ListBox2->Items->Add(Edit2->Text);
}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::Button2Click(TObject *Sender)
{
    int i=ListBox1->ItemIndex;
    int k=ListBox2->ItemIndex;
    if(i!=-1 && k!=-1)
    {
        ListBox1->Items->Delete(i);
        ListBox2->Items->Delete(k);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::Button3Click(TObject *Sender)
{
    int i=ListBox1->ItemIndex;
    int k=ListBox2->ItemIndex;
    if(i!=-1 && k!=-1 &&i>0)
    {
        int m=i,n=i-1;
        AnsiString tmp=ListBox1->Items->Strings[m];
        ListBox1->Items->Strings[m] = ListBox1->Items->Strings[n];
        ListBox1->Items->Strings[n] = tmp;

        tmp=ListBox2->Items->Strings[m];
        ListBox2->Items->Strings[m] = ListBox2->Items->Strings[n];
        ListBox2->Items->Strings[n] = tmp;
        ListBox1->ItemIndex = n;
        ListBox2->ItemIndex = n;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFrmAnayValue::Button4Click(TObject *Sender)
{
    int i=ListBox1->ItemIndex;
    int k=ListBox2->ItemIndex;
    if(i!=-1 && k!=-1 && i<ListBox1->Items->Count-1)
    {
        int m=i,n=i+1;
        AnsiString tmp=ListBox1->Items->Strings[m];
        ListBox1->Items->Strings[m] = ListBox1->Items->Strings[n];
        ListBox1->Items->Strings[n] = tmp;

        tmp=ListBox2->Items->Strings[m];
        ListBox2->Items->Strings[m] = ListBox2->Items->Strings[n];
        ListBox2->Items->Strings[n] = tmp;
        ListBox1->ItemIndex = n;
        ListBox2->ItemIndex = n;
    }
}
//---------------------------------------------------------------------------

