//---------------------------------------------------------------------------

#ifndef TelnetEditFrmH
#define TelnetEditFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmTelnetEdit : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TButton *Button1;
    TButton *Button2;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
    bool verify();
public:		// User declarations
    __fastcall TFrmTelnetEdit(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmTelnetEdit *FrmTelnetEdit;
//---------------------------------------------------------------------------
#endif

