#include "..\Include\DLT645\DLT645FrameSend.h"
#include "resource.h"
#include <WindowsX.h>
#include "..\Include\DLT645\DLT645Cmd.h"
#include "..\Include\DLT645\DLT645.h"

int DLT645FrameSend::GetDataLen()
{
	int diLen=0;
	if(this->GetDI() !=0)
	{
		diLen=(int)wcslen(this->GetDI())/2;
	}

	int userAndPasswordlen=0;
	if(this->GetUserCode() !=0 && wcslen(this->GetUserCode()) >0)
	{
		userAndPasswordlen=8;
	}

	int datalen=0;
	if(this->GetData() !=0)
	{
		datalen=(int)(wcslen(this->GetData() )+1)/2;
	}

	return diLen+userAndPasswordlen+datalen;
}

int DLT645FrameSend::GetFrameLen()
{
	int dateLen=this->GetDataLen();
	return this->feCount+10+dateLen+2;
}

bool DLT645FrameSend::WrapFrame(char *buf,int buflen,int *frameLen)
{
	//  前缀 oxFE
	size_t curPos=0;

	for(int i=0;i<this->feCount;i++)
	{
		buf[curPos++]=(char)FE;
	}

	//0x68;
	buf[curPos++]=0x68;

	//地址
	MakeAddressOK(&this->address);
	if(ReverseAndAdd(this->GetAddress(),12,buf+curPos,0x00) <6)
	{
		return false;
	}
	curPos+=6;

	// 0x68
	buf[curPos++]=0x68;

	//cmd
	buf[curPos++]=(char)this->GetCmd();

	//data length
	buf[curPos++]=(char)this->GetDataLen();
	// di
	if(ReverseAndAdd(this->GetDI(),wcslen(this->GetDI()),buf+curPos,0x33) <(int) wcslen(this->GetDI())/2)
	{
		return false;
	}
	curPos+=wcslen(this->GetDI())/2;
	// 操作者代码
	if(this->GetUserCode() !=0)
	{
		if(ReverseAndAdd(this->GetUserCode(),wcslen(this->GetUserCode()),buf+curPos,0x33) <(int) wcslen(this->GetUserCode())/2)
		{
			return false;
		}
		curPos+=wcslen(this->GetUserCode())/2;
		if(this->GetPassword() ==0)
		{
			return false;
		}
		if(ReverseAndAdd(this->GetPassword(),wcslen(this->GetPassword()),buf+curPos,0x33) <(int) wcslen(this->GetPassword())/2)
		{
			return false;
		}
		curPos+=wcslen(this->GetPassword()) /2;
	}

	//数据
	if(ReverseAndAdd(this->GetData(),wcslen(this->GetData()),buf+curPos,0x33) <(int) wcslen(this->GetData()) /2)
	{
		return false;
	}
	curPos+=wcslen(this->GetData())/2;
	// cs
	buf[curPos++]=GetXOR(buf,this->GetFECount(),(int)curPos-this->GetFECount());
	// 0x16
	buf[curPos++]=0x16;
	*frameLen=(int)curPos;
	assert(_CrtCheckMemory());
	return true;
}

void DLT645FrameSend::UpdateDataFromUI(HWND hDlg)
{
	BOOL translated=0;
	wchar_t text[MAX_PATH]={0};
	//fe
	this->SetFECount(GetDlgItemInt(hDlg,IDC_FECOUNT,&translated,FALSE));

	//address
	GetDlgItemText(hDlg,IDC_ADDRESS,text,MAX_PATH);
	this->SetAddress(text);

	//cmd
	int selectedIndex=ComboBox_GetCurSel(GetDlgItem(hDlg,IDC_CMD));
	int charLen=ComboBox_GetLBText(GetDlgItem(hDlg,IDC_CMD),(WPARAM)selectedIndex,text);
	DLT645Cmd * cmd=(DLT645Cmd *)(g_DLT645->GetCmd(text));
	this->SetCmd(cmd->GetCmd());

	//di
	GetDlgItemText(hDlg,IDC_DI,text,MAX_PATH);
	this->SetDI(text);

	//data
	GetDlgItemText(hDlg,IDC_DATA,text,MAX_PATH);
	this->SetData(text);

	//usercode
	GetDlgItemText(hDlg,IDC_USERCODE,text,MAX_PATH);
	this->SetUserCode(text);

	//password
	GetDlgItemText(hDlg,IDC_PASSWORD,text,MAX_PATH);
	this->SetPassword(text);
}