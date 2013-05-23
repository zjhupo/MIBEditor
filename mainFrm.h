//---------------------------------------------------------------------------

#ifndef mainFrmH
#define mainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TEdit *edtDBName;
    TSpeedButton *SpeedButton1;
    TBitBtn *btnOpen;
    TBitBtn *btnClose;
    TStatusBar *StatusBar1;
    TPageControl *pgcMain;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox2;
    TListView *ListView2;
    TPanel *Panel1;
    TListView *ListView1;
    TPanel *Panel2;
    TPanel *Panel3;
    TBitBtn *btnAddDev;
    TBitBtn *btnEditDev;
    TBitBtn *btnDelDev;
    TBitBtn *btnAddOp;
    TBitBtn *btnEditOp;
    TBitBtn *btnDelOp;
    TGroupBox *GroupBox3;
    TListView *ListView3;
    TPanel *Panel4;
    TListView *ListView4;
    TPanel *Panel5;
    TADOConnection *FADO;
    TBitBtn *BitBtn1;
    TBitBtn *BitBtn2;
    TADOQuery *ADOQuery1;
    TComboBox *cmbOPValue;
    TTabSheet *TabSheet3;
    TPanel *Panel6;
    TBitBtn *btnAddTask;
    TBitBtn *btnEditTask;
    TBitBtn *btnDelTask;
    TBitBtn *btnSaveTask;
    TListView *ListView5;
    TPanel *Panel7;
    TBitBtn *btnAdd;
    TBitBtn *btnEdit;
    TBitBtn *btnDel;
    TBitBtn *btnSave;
    TBitBtn *btnCancel;
    TStaticText *lblAdd;
    TTabSheet *TabSheet4;
    TMemo *mmLog;
    TGroupBox *GroupBox4;
    TMemo *Memo1;
    TPanel *Panel8;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label10;
    TLabel *Label9;
    TLabel *Label11;
    TComboBox *cmbOP;
    TEdit *edtStep;
    TEdit *edtOID;
    TCheckBox *chkLinkPort;
    TComboBox *cmbDataType;
    TEdit *edtValue;
    TComboBox *cmbUse;
    TEdit *edtSource;
    TEdit *edtDesc;
    TBitBtn *btnSetValue;
    TComboBox *cmbCallType;
    TComboBox *cmbTaskSet;
    TComboBox *cmbPortType;
    TEdit *edtPortDesc;
    TButton *btnPortDesc;
    TEdit *edtDLL;
    TComboBox *cmbLinkLast;
    TEdit *edtLinkValue;
    TCheckBox *chkIf;
    TEdit *edtCase;
    TComboBox *cmbDoOP;
    TComboBox *cmbCommandType;
    TButton *btnTelnet;
    TCheckBox *chkErrorEnd;
    TButton *btnCase;
    TSplitter *Splitter1;
  TSplitter *Splitter2;
    TComboBox *cmbRW;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnOpenClick(TObject *Sender);
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall pgcMainChange(TObject *Sender);
    void __fastcall ListView1CustomDrawItem(TCustomListView *Sender,
                                            TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
    void __fastcall btnAddDevClick(TObject *Sender);
    void __fastcall btnEditDevClick(TObject *Sender);
    void __fastcall btnDelDevClick(TObject *Sender);
    void __fastcall BitBtn1Click(TObject *Sender);
    void __fastcall btnAddOpClick(TObject *Sender);
    void __fastcall btnEditOpClick(TObject *Sender);
    void __fastcall btnDelOpClick(TObject *Sender);
    void __fastcall BitBtn2Click(TObject *Sender);
    void __fastcall btnAddClick(TObject *Sender);
    void __fastcall btnEditClick(TObject *Sender);
    void __fastcall btnCancelClick(TObject *Sender);
    void __fastcall btnSaveClick(TObject *Sender);
    void __fastcall ListView3SelectItem(TObject *Sender, TListItem *Item,
                                        bool Selected);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall btnDelClick(TObject *Sender);
    void __fastcall cmbOPChange(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall btnSetValueClick(TObject *Sender);
    void __fastcall btnAddTaskClick(TObject *Sender);
    void __fastcall btnEditTaskClick(TObject *Sender);
    void __fastcall btnDelTaskClick(TObject *Sender);
    void __fastcall btnSaveTaskClick(TObject *Sender);
    void __fastcall cmbPortTypeChange(TObject *Sender);
    void __fastcall StatusBar1DblClick(TObject *Sender);
    void __fastcall ListView4SelectItem(TObject *Sender, TListItem *Item,
                                        bool Selected);
    void __fastcall cmbCommandTypeChange(TObject *Sender);
    void __fastcall btnTelnetClick(TObject *Sender);
    void __fastcall btnCaseClick(TObject *Sender);
private:	// User declarations
    int iCaseVtoG,iCaseVID;
    AnsiString iCaseDef;
    bool FChange;
    void init();
    void Reload();//在具体配置的时候,读入初始设置
    void ClearSet();
    void setEdit(bool bEdit);
    int dwAdd;
    int OldItemIndex;
    void SaveSet();
    bool bShow;
    void ReloadTask();
    int FieldExists(TADOQuery*Query,AnsiString szFieldName);
public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif

