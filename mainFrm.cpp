//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "mainFrm.h"
#include "DeviceInfoFrm.h"
#include "OperaFrm.h"
#include "AnayValueFrm.h"
#include "TaskSetFrm.h"
#include "AboutFrm.h"
#include "TelnetEditFrm.h"
#include "CaseFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
    bShow = false;
    Application->Title = Caption;
    edtDBName->Text = ExtractFilePath(Application->ExeName)+"config.mdb";
    edtOID->Text = "";
    edtValue->Text = "";
    edtSource->Text = "";
    edtDesc->Text = "";
    pgcMain->ActivePageIndex = 0;
    FChange = false;
    init();
    FrmDeviceInfo = new TFrmDeviceInfo(this);
    FrmOpera = new TFrmOpera(this);
    FrmAnayValue = new TFrmAnayValue(this);
    FrmTaskSet = new TFrmTaskSet(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnOpenClick(TObject *Sender)
{
    FADO->Close();
    FADO->ConnectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Persist Security "\
                             "Info=True;Jet OLEDB:Database Password=junctionautotask;Password=;Data Source="+edtDBName->Text;
    FADO->Open();
    if(FADO->Connected)
    {
        AnsiString bkFile=edtDBName->Text+".bak";
        ::CopyFile(edtDBName->Text.c_str(),bkFile.c_str(),false);
        btnOpen->Enabled = false;
        btnClose->Enabled = true;
        FChange = false;
        pgcMain->Enabled = true;
        init();
    }

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::btnCloseClick(TObject *Sender)
{
    if(FChange)
    {
        switch(Application->MessageBoxA("配置已经改变，是否保存？","提示",MB_YESNOCANCEL+MB_ICONINFORMATION))
        {
        case IDYES:
            SaveSet();
            break;
        case IDCANCEL:
            return;
        }
    }
    FChange = false;
    btnOpen->Enabled = true;
    btnClose->Enabled = false;
    pgcMain->Enabled = false;
}
//---------------------------------------------------------------------------

void TfrmMain::ClearSet()
{
    bShow = false;
    cmbOP->ItemIndex = -1;
    edtStep->Text="1";
    chkLinkPort->Checked = true;
    edtOID->Text = "";
    edtValue->Text = "";
    cmbUse->ItemIndex = 0;
    edtSource->Text="";
    edtDesc->Text="";
    edtDLL->Text = "";
    cmbCallType->ItemIndex=0;
    cmbLinkLast->ItemIndex = 0;
    cmbUse->ItemIndex = 0;
    cmbCallType->ItemIndex = 0;
    bShow = true;
}

int TfrmMain::FieldExists(TADOQuery*Query,AnsiString szFieldName)
{
    int iRet = -1;
    AnsiString tmp=szFieldName.UpperCase();
    if(Query->Active)
        for(int i=0;i<Query->Fields->Count;i++)
        {
            if(Query->Fields->Fields[i]->FieldName.UpperCase()==tmp)
            {
                iRet = i;
                break;
            }
        }
    return iRet;
}

void TfrmMain::init()
{
    ListView1->Clear();
    ListView2->Clear();
    ListView3->Clear();
    ListView4->Clear();
    ClearSet();
    Reload();
    if(FADO->Connected)
    {
        ADOQuery1->SQL->Text="select * from Devices order by DevID";
        ADOQuery1->Open();
        AnsiString szSwitchName="";
        int fldidx=-1;
        while(!ADOQuery1->Eof)
        {
            TListItem *Item=ListView1->Items->Add();
            szSwitchName = ADOQuery1->FieldByName("DevName")->AsString;
            fldidx = FieldExists(ADOQuery1,"switchname");
            if(fldidx>-1)
                szSwitchName = ADOQuery1->Fields->Fields[fldidx]->AsString;
            Item->Caption= ADOQuery1->FieldByName("DevName")->AsString;//厂商
            Item->SubItems->Add(szSwitchName);                         //型号
            Item->SubItems->Add(ADOQuery1->FieldByName("Name")->AsString);//原来的名称改为识别符号
            Item->SubItems->Add(ADOQuery1->FieldByName("supportSNMP")->AsInteger==1?"支持":"不支持");
            Item->SubItems->Add(ADOQuery1->FieldByName("typOID")->AsString);
            Item->SubItems->Add(ADOQuery1->FieldByName("saveOID")->AsString);
            Item->SubItems->Add(ADOQuery1->FieldByName("saveValue")->AsString);
            Item->SubItems->Add(ADOQuery1->FieldByName("Telnet")->AsString);
            Item->SubItems->Add(ADOQuery1->FieldByName("maxportnum")->AsString);


            Item->SubItems->Add(ADOQuery1->FieldByName("DevID")->AsString);//DevID
            ADOQuery1->Next();
        }
        //OperaMode
        ADOQuery1->SQL->Text="select * from OperaMode order by ModeID";
        ADOQuery1->Open();
        while(!ADOQuery1->Eof)
        {
            TListItem *Item=ListView2->Items->Add();
            Item->Caption=ADOQuery1->FieldByName("ModeID")->AsString;
            Item->SubItems->Add(ADOQuery1->FieldByName("remark")->AsString);
            ADOQuery1->Next();
        }
    }
}

void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
    delete FrmDeviceInfo;
    delete FrmOpera;
    delete FrmAnayValue;
    delete FrmTaskSet;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
    if(dwAdd!=0)
    {
        Application->MessageBoxA("您当前正在编辑配置,请保存或取消后再关闭程序!","提示",MB_ICONWARNING);
        Action = caNone;
    }
}
//---------------------------------------------------------------------------

void TfrmMain::Reload()
{
    if(!FADO->Connected)
        return;
    ListView3->Clear();
    ADOQuery1->SQL->Text ="select * from Devices Order by DevID";
    ADOQuery1->Open();
    while(!ADOQuery1->Eof)
    {
        TListItem *Item = ListView3->Items->Add();
        Item->Caption=ADOQuery1->FieldByName("DevName")->AsString;
        Item->SubItems->Add(ADOQuery1->FieldByName("switchName")->AsString);
        Item->SubItems->Add(ADOQuery1->FieldByName("DevID")->AsString);
        ADOQuery1->Next();
    }
    OldItemIndex=-1;
    ADOQuery1->SQL->Text ="select * from OperaMode Order by ModeID";
    ADOQuery1->Open();
    cmbOP->Clear();
    cmbOPValue->Clear();
    while(!ADOQuery1->Eof)
    {
        cmbOP->Items->Add(ADOQuery1->FieldByName("remark")->AsString);
        cmbOPValue->Items->Add(ADOQuery1->FieldByName("ModeID")->AsString);
        ADOQuery1->Next();
    }
    cmbDoOP->Items->Assign(cmbOP->Items);
    cmbTaskSet->Clear();
    ADOQuery1->SQL->Text = "select * from TaskSets order by SetName";
    ADOQuery1->Open();
    while(!ADOQuery1->Eof)
    {
        cmbTaskSet->Items->Add(ADOQuery1->FieldByName("SetName")->AsString);
        ADOQuery1->Next();
    }
}

void __fastcall TfrmMain::pgcMainChange(TObject *Sender)
{
    switch(pgcMain->ActivePageIndex)
    {
    case 1:
        Reload();
        break;
    case 2:
        ReloadTask();
        break;
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::ListView1CustomDrawItem(TCustomListView *Sender,
        TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
    /*  DefaultDraw = false;
      TCanvas *vs=ListView1->Canvas;
      TRect rc=Item->DisplayRect(drBounds);
      TColor cl=clWhite;
      if(Item->SubItems->Strings[5]=="0")
        cl=clGradientActiveCaption;
      vs->Brush->Color = cl;
      vs->FillRect(rc);
      vs->Brush->Style = bsClear;
      vs->TextOutA(rc.left+2,rc.top+2,Item->Caption);*/

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnAddDevClick(TObject *Sender)
{
    FrmDeviceInfo->Clear();
    if(FrmDeviceInfo->ShowModal()==mrOk)
    {
        TListItem *Item = ListView1->Items->Add();
        Item->Caption = FrmDeviceInfo->Edit1->Text;//厂商
        Item->SubItems->Add(FrmDeviceInfo->Edit2->Text);//型号
        Item->SubItems->Add(FrmDeviceInfo->Edit6->Text);//原来的型号改为识别符号
        AnsiString ss=FrmDeviceInfo->CheckBox1->Checked==true?"支持":"不支持";
        Item->SubItems->Add(ss);
        Item->SubItems->Add(FrmDeviceInfo->Edit3->Text);
        Item->SubItems->Add(FrmDeviceInfo->Edit4->Text);
        Item->SubItems->Add(FrmDeviceInfo->Edit5->Text);
        Item->SubItems->Add(FrmDeviceInfo->mmTelnet->Text);
        Item->SubItems->Add(FrmDeviceInfo->edtPort->Text);
        Item->SubItems->Add("0");
    }

    /*      DevName    === Caption
            switchname === edit2==Item[0]
            name       === edit6==Item[1]
        ADOQuery1->SQL->Text ="Insert into Devices(DevID,DevName,Name,switchname,supportSNMP,typOID,saveOID,Telnet,saveValue)values("\
          "'"+IntToStr(i+1)+"',"\
          "'"+Item->Caption+"',"\
          "'"+Item->SubItems->Strings[1]+"',"\
          "'"+Item->SubItems->Strings[0]+"',"\
    */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEditDevClick(TObject *Sender)
{
    if(ListView1->Selected!=NULL)
    {
        FrmDeviceInfo->Edit1->Text=ListView1->Selected->Caption;
        FrmDeviceInfo->Edit2->Text=ListView1->Selected->SubItems->Strings[0];
        FrmDeviceInfo->Edit6->Text = ListView1->Selected->SubItems->Strings[1];
        bool bl=false;
        if(ListView1->Selected->SubItems->Strings[1+1]=="支持")
            bl=true;
        FrmDeviceInfo->CheckBox1->Checked =bl;
        FrmDeviceInfo->Edit3->Text=ListView1->Selected->SubItems->Strings[2+1];
        FrmDeviceInfo->Edit4->Text=ListView1->Selected->SubItems->Strings[3+1];
        FrmDeviceInfo->Edit5->Text=ListView1->Selected->SubItems->Strings[4+1];
        FrmDeviceInfo->mmTelnet->Text = ListView1->Selected->SubItems->Strings[5+1];
        FrmDeviceInfo->edtPort->Text = ListView1->Selected->SubItems->Strings[6+1];
        if(FrmDeviceInfo->ShowModal()==mrOk)
        {
            ListView1->Selected->Caption = FrmDeviceInfo->Edit1->Text;
            ListView1->Selected->SubItems->Strings[0] = (FrmDeviceInfo->Edit2->Text);
            ListView1->Selected->SubItems->Strings[1] = FrmDeviceInfo->Edit6->Text;
            AnsiString ss=FrmDeviceInfo->CheckBox1->Checked==true?"支持":"不支持";
            ListView1->Selected->SubItems->Strings[1+1]= (ss);
            ListView1->Selected->SubItems->Strings[2+1]= (FrmDeviceInfo->Edit3->Text);
            ListView1->Selected->SubItems->Strings[3+1]= (FrmDeviceInfo->Edit4->Text);
            ListView1->Selected->SubItems->Strings[4+1]= (FrmDeviceInfo->Edit5->Text);
            ListView1->Selected->SubItems->Strings[5+1]= (FrmDeviceInfo->mmTelnet->Text);
            ListView1->Selected->SubItems->Strings[6+1]=FrmDeviceInfo->edtPort->Text;
        }
    }
    else
        Application->MessageBoxA("请选择一个设备项!","提示",MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnDelDevClick(TObject *Sender)
{
    if(ListView1->Selected!=NULL)
    {
        ListView1->Selected->Delete();
    }
    else
        Application->MessageBoxA("请选择一个设备项!","提示",MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BitBtn1Click(TObject *Sender)
{
    ADOQuery1->SQL->Text="delete from Devices";
    ADOQuery1->ExecSQL();
    for(int i=0;i<ListView1->Items->Count;i++)
    {
        TListItem*Item=ListView1->Items->Item[i];
        int isnmp=1;
        if(Item->SubItems->Strings[1+1]=="不支持")
            isnmp=2;
        ADOQuery1->SQL->Text ="Insert into Devices(DevID,DevName,Name,switchname,supportSNMP,typOID,saveOID,Telnet,maxportnum,saveValue)values("\
                              "'"+IntToStr(i+1)+"',"\
                              "'"+Item->Caption+"',"\
                              "'"+Item->SubItems->Strings[1]+"',"\
                              "'"+Item->SubItems->Strings[0]+"',"\
                              "'"+IntToStr(isnmp)+"',"\
                              "'"+Item->SubItems->Strings[2+1]+"',"\
                              "'"+Item->SubItems->Strings[3+1]+"',"\
                              "'"+Item->SubItems->Strings[5+1]+"',"\
                              "'"+Item->SubItems->Strings[6+1]+"',"\
                              "'"+Item->SubItems->Strings[4+1]+"')";
        ADOQuery1->ExecSQL();
        Item->SubItems->Strings[Item->SubItems->Count-1] = IntToStr(i+1);
    }
    ShowMessage("保存成功");
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnAddOpClick(TObject *Sender)
{
    FrmOpera->Clear();
    if(FrmOpera->ShowModal()==mrOk)
    {
        TListItem *Item=ListView2->Items->Add();
        Item->Caption = FrmOpera->CSpinEdit1->Text;
        Item->SubItems->Add(FrmOpera->Memo1->Text);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEditOpClick(TObject *Sender)
{
    if(ListView2->Selected!=NULL)
    {
        FrmOpera->CSpinEdit1->Text = ListView2->Selected->Caption;
        FrmOpera->Memo1->Text = ListView2->Selected->SubItems->Strings[0];
    }
    else
    {
        Application->MessageBoxA("请选择一个操作号!","提示",MB_ICONINFORMATION);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnDelOpClick(TObject *Sender)
{
    if(ListView2->Selected==NULL)
    {
        ListView2->Selected->Delete();
    }
    else
    {
        Application->MessageBoxA("请选择一个操作号!","提示",MB_ICONINFORMATION);
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::BitBtn2Click(TObject *Sender)
{

    ADOQuery1->SQL->Text="delete from OperaMode";
    ADOQuery1->ExecSQL();
    for(int i=0;i<ListView2->Items->Count;i++)
    {
        TListItem*Item=ListView2->Items->Item[i];
        ADOQuery1->SQL->Text ="Insert into OperaMode(ModeID,remark)values("\
                              "'"+Item->Caption+"',"\
                              "'"+Item->SubItems->Strings[0]+"')";
        ADOQuery1->ExecSQL();
    }
    ShowMessage("保存成功");
}
//---------------------------------------------------------------------------



void TfrmMain::setEdit(bool bEdit)
{
    btnAdd->Enabled = !bEdit;
    btnEdit->Enabled = btnAdd->Enabled;
    btnDel->Enabled = btnAdd->Enabled;
    btnSave->Enabled = bEdit;
    btnCancel->Enabled = bEdit;
    ListView4->Enabled = !bEdit;
    ListView3->Enabled = ListView4->Enabled;
    if(!bEdit)
        dwAdd=0;
    lblAdd->Caption = "";
}

void __fastcall TfrmMain::btnAddClick(TObject *Sender)
{
    if(ListView3->Selected==NULL)
    {
        Application->MessageBoxA("请选择一个设备!","提示",MB_ICONINFORMATION);
        return;
    }
    dwAdd = 1;
    iCaseVtoG = 0;
    iCaseVID = -1;
    iCaseDef = "";
    setEdit(true);
    ClearSet();
    lblAdd->Caption ="正在添加";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEditClick(TObject *Sender)
{
    if(ListView3->Selected==NULL)
    {
        Application->MessageBoxA("请选择一个设备!","提示",MB_ICONINFORMATION);
        return;
    }
    setEdit(true);
    dwAdd = 2;
    lblAdd->Caption = "正在编辑";
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnCancelClick(TObject *Sender)
{
    setEdit(false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSaveClick(TObject *Sender)
{
    TListItem*Item;
    if(chkIf->Checked && cmbDoOP->ItemIndex==-1)
    {
        Application->MessageBoxA("请选择下一个要做的命令!","提示",MB_ICONINFORMATION);
        return;
    }
    if(dwAdd==1)
    {
        Item = ListView4->Items->Add();
        Item->Caption = cmbOP->Text;
        Item->SubItems->Add(edtStep->Text);
        Item->SubItems->Add(edtOID->Text);

        Item->SubItems->Add(cmbCallType->Text);

        Item->SubItems->Add((chkLinkPort->Checked==true)?"连接":"不连接");

        Item->SubItems->Add(cmbDataType->Text);
        Item->SubItems->Add(edtValue->Text);

        Item->SubItems->Add(cmbUse->Text);
        Item->SubItems->Add(edtSource->Text);
        Item->SubItems->Add(edtDesc->Text);
        Item->SubItems->Add(edtDLL->Text); //10
        Item->SubItems->Add(cmbTaskSet->Text);
        Item->SubItems->Add(cmbPortType->Text);
        Item->SubItems->Add(edtPortDesc->Text);
        Item->SubItems->Add(cmbLinkLast->Text);
        Item->SubItems->Add(edtLinkValue->Text);

        Item->SubItems->Add(chkIf->Checked==true?"IF":"");
        Item->SubItems->Add(edtCase->Text);

        Item->SubItems->Add(cmbDoOP->Text);
        Item->SubItems->Add(cmbCommandType->Text);
        Item->SubItems->Add(btnTelnet->Hint);
        Item->SubItems->Add(chkErrorEnd->Checked==true?"1":"0");//21
        Item->SubItems->Add(Memo1->Text);
        Item->SubItems->Add(btnCase->Hint);
            Item->SubItems->Add(IntToStr(iCaseVtoG));//case的值是动态获取
            Item->SubItems->Add(IntToStr(iCaseVID));
            Item->SubItems->Add(iCaseDef);
        int irw=1;
        if(cmbRW->ItemIndex==1)
            irw=2;
        Item->SubItems->Add(IntToStr(irw));

    }
    else
    {
        Item = ListView4->Selected;
        Item->Caption = cmbOP->Text;
        Item->SubItems->Strings[0]=(edtStep->Text);
        Item->SubItems->Strings[1]=(edtOID->Text);

        Item->SubItems->Strings[2]=(cmbCallType->Text);

        Item->SubItems->Strings[3]=((chkLinkPort->Checked==true)?"连接":"不连接");

        Item->SubItems->Strings[4]=(cmbDataType->Text);
        Item->SubItems->Strings[5]=(edtValue->Text);

        Item->SubItems->Strings[6]=(cmbUse->Text);
        Item->SubItems->Strings[7]=(edtSource->Text);
        Item->SubItems->Strings[8]=(edtDesc->Text);
        Item->SubItems->Strings[9]=(edtDLL->Text);
        Item->SubItems->Strings[10] = cmbTaskSet->Text;
        Item->SubItems->Strings[11] = cmbPortType->Text;
        Item->SubItems->Strings[12] = edtPortDesc->Text;
        Item->SubItems->Strings[13] = cmbLinkLast->Text;
        Item->SubItems->Strings[14] = edtLinkValue->Text;

        Item->SubItems->Strings[15] =(chkIf->Checked==true?"IF":"");
        Item->SubItems->Strings[16] =(edtCase->Text);

        Item->SubItems->Strings[17] =(cmbDoOP->Text);
        Item->SubItems->Strings[18] = cmbCommandType->Text;
        Item->SubItems->Strings[19] = btnTelnet->Hint;
        Item->SubItems->Strings[20] = chkErrorEnd->Checked==true?"1":"0";
        Item->SubItems->Strings[21] = Memo1->Text;
        Item->SubItems->Strings[22] = btnCase->Hint;
        Item->SubItems->Strings[23] = IntToStr(iCaseVtoG);
        Item->SubItems->Strings[24] = IntToStr(iCaseVID);
        Item->SubItems->Strings[25] = iCaseDef;
        int irw=1;
        if(cmbRW->ItemIndex==1)
            irw=2;
        Item->SubItems->Strings[26] = IntToStr(irw);
    }
    FChange = true;
    setEdit(false);
}
//---------------------------------------------------------------------------
void TfrmMain::SaveSet()
{
    if(!FChange)
        return;

    int DevID=StrToInt(ListView3->Items->Item[OldItemIndex]->SubItems->Strings[1]);
    ADOQuery1->SQL->Text ="delete from Sets where DevID="+IntToStr(DevID);
    ADOQuery1->ExecSQL();
    for(int i=0;i<ListView4->Items->Count;i++)
    {
        TListItem*Item = ListView4->Items->Item[i];
        int DoIpID=cmbDoOP->Items->IndexOf(Item->SubItems->Strings[17]);
        if(DoIpID>-1)
            DoIpID = StrToInt(cmbOPValue->Items->Strings[DoIpID]);
        int iSnmp=1;
        if(Item->SubItems->Strings[18]=="TELNET")
            iSnmp = 2;
        else if(Item->SubItems->Strings[18]=="SNMP")
            iSnmp = 1;
        else
            iSnmp = 3;
        cmbCommandType->ItemIndex+1;
        int irw=StrToInt(Item->SubItems->Strings[26]);
        int _iCaseVtoG = StrToInt(Item->SubItems->Strings[23]);
        int _iCaseVID = StrToInt(Item->SubItems->Strings[24]);
        AnsiString _iCaseDef = Item->SubItems->Strings[25];
        ADOQuery1->SQL->Text="Insert Into Sets(DevID,OpMode,OpStep,OID,CallType,"\
                             "LinkPort,DataType,AValue,ValueObj,ValueSource,ValueDesc,"\
                             "ValueSet,PortType,LinkLast,LinkValue,PortDesc,IF,IfValue,"\
                             "IfDoId,CommandType,Telnet,ErrorEnd,skipcase,remark,"\
                             "readwrite,casevtog,casevid,casedefv,DLLName)values("\
                             "'"+ IntToStr(DevID) +"',"\
                             "'"+ cmbOPValue->Items->Strings[cmbOP->Items->IndexOf(Item->Caption)]+"',"\
                             "'"+ Item->SubItems->Strings[0]+"',"\
                             "'"+ Item->SubItems->Strings[1]+"',"\
                             "'"+ IntToStr(cmbCallType->Items->IndexOf(Item->SubItems->Strings[2])+1)+"',"\
                             "'"+ IntToStr(Item->SubItems->Strings[3]=="连接"?1:2)+"',"\
                             "'"+ IntToStr(cmbDataType->Items->IndexOf(Item->SubItems->Strings[4])+1)+"',"\
                             "'"+ Item->SubItems->Strings[5]+"',"\
                             "'"+ IntToStr(cmbUse->Items->IndexOf(Item->SubItems->Strings[6])+1)+"',"\
                             "'"+ Item->SubItems->Strings[7]+"',"\
                             "'"+ Item->SubItems->Strings[8]+"',"\
                             "'"+ Item->SubItems->Strings[10]+"',"\
                             "'"+ IntToStr(cmbPortType->Items->IndexOf(Item->SubItems->Strings[11])+1)+"',"\
                             "'"+ IntToStr(cmbLinkLast->Items->IndexOf(Item->SubItems->Strings[13])+1)+"',"\
                             "'"+ Item->SubItems->Strings[14]+"',"\
                             "'"+ Item->SubItems->Strings[12]+"',"\

                             "'"+ IntToStr((Item->SubItems->Strings[15]=="IF")?1:2)+ "',"\
                             "'"+ Item->SubItems->Strings[16]+ "',"\
                             "'"+ IntToStr(DoIpID)+ "',"\
                             "'"+ IntToStr(iSnmp)+"',"\
                             "'"+ Item->SubItems->Strings[19]+"',"\
                             "'"+ Item->SubItems->Strings[20]+"',"\
                             "'"+ Item->SubItems->Strings[22]+"',"\
                             "'"+ Item->SubItems->Strings[21]+"',"\
                             "'"+IntToStr(irw)+"',"\
                             "'"+IntToStr(_iCaseVtoG)+"',"\
                             "'"+IntToStr(_iCaseVID)+"',"\
                             "'"+_iCaseDef+"',"\
                             "'"+ Item->SubItems->Strings[9]+"')";
        mmLog->Lines->Add(ADOQuery1->SQL->Text);
        ADOQuery1->ExecSQL();
    }

    ShowMessage("保存成功");
    FChange = false;
}
void __fastcall TfrmMain::ListView3SelectItem(TObject *Sender,
        TListItem *Item, bool Selected)
{
    if(ListView3->Selected!=NULL)
    {
        if(OldItemIndex==-1)
            OldItemIndex= ListView3->Selected->Index;
        if(OldItemIndex!= ListView3->Selected->Index)
        {
            SaveSet();
            OldItemIndex= ListView3->Selected->Index;
        }
        int DevID=StrToInt(ListView3->Selected->SubItems->Strings[1]);
        int tempv;
        ADOQuery1->SQL->Text ="select * from Sets where DevID="+IntToStr(DevID)+" Order by OpMode,OpStep";
        ADOQuery1->Open();
        ListView4->Clear();
        while(!ADOQuery1->Eof)
        {
            TListItem*Item = ListView4->Items->Add();
            int ind=cmbOPValue->Items->IndexOf(ADOQuery1->FieldByName("OpMode")->AsString);
            Item->Caption = cmbOP->Items->Strings[ind];
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("OpStep")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("OID")->AsString);

            /*01*/Item->SubItems->Add(cmbCallType->Items->Strings[ADOQuery1->FieldByName("CallType")->AsInteger-1]);

            ind = ADOQuery1->FieldByName("LinkPort")->AsInteger;
            /*01*/Item->SubItems->Add((ind==1)?"连接":"不连接");

            /*01*/Item->SubItems->Add(cmbDataType->Items->Strings[ADOQuery1->FieldByName("DataType")->AsInteger-1]);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("AValue")->AsString);

            /*01*/Item->SubItems->Add(cmbUse->Items->Strings[ADOQuery1->FieldByName("ValueObj")->AsInteger-1]);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("ValueSource")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("ValueDesc")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("DLLName")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("ValueSet")->AsString);
            /*01*/Item->SubItems->Add(cmbPortType->Items->Strings[ADOQuery1->FieldByName("PortType")->AsInteger-1]);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("PortDesc")->AsString);
            /*01*/Item->SubItems->Add(cmbLinkLast->Items->Strings[ADOQuery1->FieldByName("LinkLast")->AsInteger-1]);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("LinkValue")->AsString);

            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("If")->AsInteger==1?"IF":"");
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("IfValue")->AsString);

            ind=cmbOPValue->Items->IndexOf(ADOQuery1->FieldByName("IfDoId")->AsString);
            /*01*/Item->SubItems->Add(cmbOP->Items->Strings[ind]);

            /*01*/Item->SubItems->Add(cmbCommandType->Items->Strings[ADOQuery1->FieldByName("CommandType")->AsInteger-1]);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("Telnet")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("ErrorEnd")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("remark")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("skipcase")->AsString);

            tempv = ADOQuery1->FieldByName("caseVtoG")->AsInteger;
            /*01*/Item->SubItems->Add(IntToStr(tempv));//case的值是动态获取
            tempv = ADOQuery1->FieldByName("caseVID")->AsInteger;
            /*01*/Item->SubItems->Add(IntToStr(tempv));
            Item->SubItems->Add(ADOQuery1->FieldByName("casedefv")->AsString);
            /*01*/Item->SubItems->Add(ADOQuery1->FieldByName("readwrite")->AsString);
            ADOQuery1->Next();
        }
    }
    else
    {
        if(OldItemIndex!= -1)
        {
            SaveSet();
            OldItemIndex= -1;
        }
        ListView4->Clear();
    }
}
//---------------------------------------------------------------------------



void __fastcall TfrmMain::btnDelClick(TObject *Sender)
{
    if(ListView3->Selected==NULL)
    {
        Application->MessageBoxA("请选择一个设备!","提示",MB_ICONINFORMATION);
        return;
    }
    if(ListView4->Selected!=NULL)
    {
        if(Application->MessageBoxA("确定删除选中的操作项吗?","提示",MB_YESNO+MB_ICONINFORMATION)==IDYES)
        {
            ListView4->Selected->Delete();
            FChange = true;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmbOPChange(TObject *Sender)
{
    if(!bShow)
        return;
    int cc=0;
    if(btnSave->Enabled)
    {
        TWinControl* comp=(TWinControl*)Sender;
        if(comp->Tag==1)
        {
            for(int i =0;i<ListView4->Items->Count;i++)
            {
                if(ListView4->Items->Item[i]->Caption==(cmbOP->Text))
                {
                    cc++;
                }
            }
            edtStep->Text = IntToStr(cc+1);
        }
        cmbTaskSet->Enabled = cmbUse->ItemIndex==0?false:true;
        edtDLL->Enabled = cmbCallType->ItemIndex==0?false:true;
        edtLinkValue->Enabled = cmbLinkLast->ItemIndex==2?true:false;
        return;
    }
    //if(!btnClose->Enabled)return;
    Application->MessageBoxA("请点击\"添加\"或\"编辑\"以进行修改状态!","提示",MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::FormShow(TObject *Sender)
{
    bShow = true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnSetValueClick(TObject *Sender)
{
    if(FrmAnayValue->ShowValue(edtSource->Text,edtDesc->Text)==mrOk && btnSave->Enabled)
    {
        edtSource->Text = FrmAnayValue->getS1();
        edtDesc->Text = FrmAnayValue->getS2();
    }
}
//---------------------------------------------------------------------------
void TfrmMain::ReloadTask()
{
    ListView5->Clear();
    ADOQuery1->SQL->Text = "select * from TaskSets order by SetName";
    ADOQuery1->Open();
    while(!ADOQuery1->Eof)
    {
        TListItem*Item=ListView5->Items->Add();
        Item->Caption = ADOQuery1->FieldByName("SetName")->AsString;
        Item->SubItems->Add(ADOQuery1->FieldByName("remark")->AsString);
        ADOQuery1->Next();
    }
}
void __fastcall TfrmMain::btnAddTaskClick(TObject *Sender)
{
    if(FrmTaskSet->ShowModal()==mrOk)
    {
        AnsiString s=FrmTaskSet->Edit1->Text;
        int id=-1;
        for(int i=0;i<ListView5->Items->Count;i++)
        {
            if(ListView5->Items->Item[i]->Caption==s)
            {
                id = i;
                break;
            }
        }
        if(id==-1)
        {
            TListItem *Item = ListView5->Items->Add();
            Item->Caption = s;
            Item->SubItems->Add(FrmTaskSet->Memo1->Text);
        }
        else
        {
            Application->MessageBoxA("参数已经存在","提示",MB_OK);
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnEditTaskClick(TObject *Sender)
{
    TListItem*Item=ListView5->Selected;
    if(Item==NULL)
        return;
    FrmTaskSet->Edit1->Text = Item->Caption;
    FrmTaskSet->Memo1->Text = Item->SubItems->Strings[0];
    if(FrmTaskSet->ShowModal()==mrOk)
    {
        Item->Caption = FrmTaskSet->Edit1->Text;
        Item->SubItems->Strings[0] = FrmTaskSet->Memo1->Text;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnDelTaskClick(TObject *Sender)
{
    TListItem*Item=ListView5->Selected;
    if(Item==NULL)
        return;
    if(Application->MessageBoxA("确定删除?","提示",MB_YESNO|MB_ICONINFORMATION)==ID_YES)
    {
        Item->Delete();
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnSaveTaskClick(TObject *Sender)
{
    Screen->Cursor = crHourGlass;
    try
    {
        ADOQuery1->SQL->Text ="delete from TaskSets";
        ADOQuery1->ExecSQL();
        for(int i=0;i<ListView5->Items->Count;i++)
        {
            TListItem *Item=ListView5->Items->Item[i];
            ADOQuery1->SQL->Text="insert into TaskSets(SetName,remark)values("\
                                 "'"+Item->Caption+"',"\
                                 "'"+Item->SubItems->Strings[0]+"')";
            ADOQuery1->ExecSQL();
        }
        ShowMessage("保存成功");
    }
    catch(...)
    {}
    Screen->Cursor = crDefault;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::cmbPortTypeChange(TObject *Sender)
{
    btnPortDesc->Enabled = cmbPortType->ItemIndex==2?true:false;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::StatusBar1DblClick(TObject *Sender)
{
    frmAbout = new TfrmAbout(this);
    frmAbout->ShowModal();
    frmAbout->Free();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::ListView4SelectItem(TObject *Sender,
        TListItem *Item, bool Selected)
{
    //TListItem*Item=ListView4->Selected;
    if(Item==NULL)
        return;
    bShow = false;
    try
    {
        int ind=cmbOP->Items->IndexOf(Item->Caption);
        cmbOP->ItemIndex = ind;
        cmbOPValue->ItemIndex = ind;
        edtStep->Text = Item->SubItems->Strings[0];
        edtOID->Text = Item->SubItems->Strings[1];
        cmbCallType->ItemIndex = cmbCallType->Items->IndexOf(Item->SubItems->Strings[2]);

        chkLinkPort->Checked = (Item->SubItems->Strings[3]=="连接")?true:false;
        cmbDataType->ItemIndex = cmbDataType->Items->IndexOf(Item->SubItems->Strings[4]);
        edtValue->Text = Item->SubItems->Strings[5];
        cmbUse->ItemIndex = cmbUse->Items->IndexOf(Item->SubItems->Strings[6]);
        edtSource->Text = Item->SubItems->Strings[7];
        edtDesc->Text = Item->SubItems->Strings[8];
        edtDLL->Text = Item->SubItems->Strings[9];
        cmbTaskSet->Text = Item->SubItems->Strings[10];
        cmbPortType->ItemIndex = cmbPortType->Items->IndexOf(Item->SubItems->Strings[11]);
        edtPortDesc->Text = Item->SubItems->Strings[12];
        btnPortDesc->Enabled=cmbPortType->ItemIndex==2?true:false;
        cmbLinkLast->ItemIndex = cmbLinkLast->Items->IndexOf(Item->SubItems->Strings[13]);
        edtLinkValue->Text = Item->SubItems->Strings[14];
        chkIf->Checked = Item->SubItems->Strings[15]=="IF"?true:false;
        edtCase->Text = Item->SubItems->Strings[16];
        cmbDoOP->ItemIndex = cmbDoOP->Items->IndexOf(Item->SubItems->Strings[17]);
        cmbCommandType->ItemIndex = cmbCommandType->Items->IndexOf(Item->SubItems->Strings[18]);
        btnTelnet->Hint = Item->SubItems->Strings[19];
        btnCase->Hint = Item->SubItems->Strings[22];
        chkErrorEnd->Checked = Item->SubItems->Strings[20]=="1";
        Memo1->Text = Item->SubItems->Strings[21];

        iCaseVtoG = StrToInt(Item->SubItems->Strings[23]);
        iCaseVID = StrToInt(Item->SubItems->Strings[24]);
        iCaseDef = Item->SubItems->Strings[25];

        int irw=StrToInt(Item->SubItems->Strings[26]);
        cmbRW->ItemIndex = irw-1;
        cmbCommandTypeChange(cmbCommandType);
    }
    catch(...)
    {}
    bShow= true;

}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::cmbCommandTypeChange(TObject *Sender)
{
    btnTelnet->Enabled = cmbCommandType->ItemIndex==1?true:false;
    btnCase->Enabled = cmbCommandType->ItemIndex==2?true:false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMain::btnTelnetClick(TObject *Sender)
{
    FrmTelnetEdit = new TFrmTelnetEdit(NULL);
    FrmTelnetEdit->Memo1->Text = btnTelnet->Hint;
    if(FrmTelnetEdit->ShowModal()==mrOk)
        btnTelnet->Hint = FrmTelnetEdit->Memo1->Text;
    delete FrmTelnetEdit;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMain::btnCaseClick(TObject *Sender)
{
    frmCase = new TfrmCase(NULL);
    frmCase->ComboBox1->Items->Assign(cmbOP->Items);
    frmCase->ComboBox2->Items->Assign(cmbOPValue->Items);
    frmCase->ComboBox1->Items->Insert(0,"N");
    frmCase->cmbGetValueID->Items->Assign(cmbOP->Items);
    frmCase->ComboBox2->Items->Insert(0,"N");
    frmCase->AddValue(btnCase->Hint);
    frmCase->chkValueFrmSW->Checked = iCaseVtoG==1;
    frmCase->edtDef->Text = iCaseDef;
    int id = cmbOPValue->Items->IndexOf(IntToStr(iCaseVID));
    //DoIpID = StrToInt(cmbOPValue->Items->Strings[DoIpID]);
    frmCase->cmbGetValueID->ItemIndex = id;//iCaseVID;
    if(frmCase->ShowModal()==mrOk){
        btnCase->Hint=frmCase->getValue();
        iCaseVtoG = 0;
        if(frmCase->chkValueFrmSW->Checked)
            iCaseVtoG = 1;
        iCaseVID = frmCase->cmbGetValueID->ItemIndex;
        iCaseVID = StrToInt(cmbOPValue->Items->Strings[iCaseVID]);
        iCaseDef = frmCase->edtDef->Text;
    }
    delete frmCase;
}
//---------------------------------------------------------------------------


