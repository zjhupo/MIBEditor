//---------------------------------------------------------------------------

#ifndef CaseFrmH
#define CaseFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmCase : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *Edit2;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ComboBox1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TMemo *Memo1;
    TButton *Button1;
    TComboBox *ComboBox2;
    TButton *Button2;
    TComboBox *Edit1;
    TGroupBox *GroupBox1;
    TCheckBox *chkValueFrmSW;
    TLabel *Label4;
    TComboBox *cmbGetValueID;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *edtDef;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall ComboBox1Change(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
    TStringList *value;
public:		// User declarations
    __fastcall TfrmCase(TComponent* Owner);
    void AddValue(AnsiString vv);
    AnsiString getValue();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCase *frmCase;
//---------------------------------------------------------------------------
#endif

