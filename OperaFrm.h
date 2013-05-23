//---------------------------------------------------------------------------

#ifndef OperaFrmH
#define OperaFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrmOpera : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TCSpinEdit *CSpinEdit1;
    TMemo *Memo1;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrmOpera(TComponent* Owner);
    void Clear();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmOpera *FrmOpera;
//---------------------------------------------------------------------------
#endif

