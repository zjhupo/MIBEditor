//---------------------------------------------------------------------------

#ifndef AboutFrmH
#define AboutFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmAbout : public TForm
{
__published:	// IDE-managed Components
    TStaticText *StaticText1;
    TStaticText *StaticText2;
    TMemo *Memo1;
    TSpeedButton *SpeedButton1;
    TImage *Image1;
    void __fastcall FormClick(TObject *Sender);
    void __fastcall SpeedButton1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TfrmAbout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAbout *frmAbout;
//---------------------------------------------------------------------------
#endif

