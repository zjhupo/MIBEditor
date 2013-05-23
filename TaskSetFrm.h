//---------------------------------------------------------------------------

#ifndef TaskSetFrmH
#define TaskSetFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrmTaskSet : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TEdit *Edit1;
    TLabel *Label2;
    TMemo *Memo1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrmTaskSet(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmTaskSet *FrmTaskSet;
//---------------------------------------------------------------------------
#endif


