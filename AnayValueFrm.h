//---------------------------------------------------------------------------

#ifndef AnayValueFrmH
#define AnayValueFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrmAnayValue : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TListBox *ListBox1;
    TListBox *ListBox2;
    TEdit *Edit1;
    TEdit *Edit2;
    TButton *Button1;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall ListBox2Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrmAnayValue(TComponent* Owner);
    int ShowValue(AnsiString s1,AnsiString s2);
    AnsiString getS1();
    AnsiString getS2();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmAnayValue *FrmAnayValue;
//---------------------------------------------------------------------------
#endif

