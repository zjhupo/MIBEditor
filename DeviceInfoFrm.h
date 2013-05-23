//---------------------------------------------------------------------------

#ifndef DeviceInfoFrmH
#define DeviceInfoFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmDeviceInfo : public TForm
{
__published:	// IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit1;
    TEdit *Edit2;
    TCheckBox *CheckBox1;
    TEdit *Edit3;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *Edit4;
    TEdit *Edit5;
    TTabSheet *TabSheet2;
    TMemo *mmTelnet;
    TLabel *Label6;
    TEdit *Edit6;
    TLabel *Label7;
    TEdit *edtPort;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TFrmDeviceInfo(TComponent* Owner);
    void Clear();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDeviceInfo *FrmDeviceInfo;
//---------------------------------------------------------------------------
#endif

