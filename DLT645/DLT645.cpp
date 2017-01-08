
#include "..\Include\DLT645\DLT645.h"
#include "resource.h"
#include "..\Include\MeterBase\XmlHelper.h"
#include "..\Include\DLT645\DLT645Cmd.h"
#include "..\Include\DLT645\DLT645FrameSend.h"
#include "..\Include\DLT645\DLT645DI.h"
#include "..\Include\DLT645\DISelector.h"
#include <Windowsx.h >
#include <time.h>

DLT645 *g_DLT645;
DLT645FrameSend *g_DLT645FrameSend=new DLT645FrameSend();
bool g_IsUpdateCmd=false;

DLT645::DLT645()
{
	this->hWnd=0;
}

DLT645::~DLT645()
{
	if(this->hWnd !=0)
	{
		::DestroyWindow(this->hWnd);
	}
	for(size_t i=0;i<this->cmds.size();i++)
	{
		delete this->cmds[i];
	}
	this->cmds.clear();

	std::map<const wchar_t *,std::vector<DLT645DI *>*>::iterator index=this->diGroups.begin();
	while(index != this->diGroups.end())
	{
		for(size_t i=0;i<index->second->size();i++)
		{
			delete index->second->at(i);
		}
		index->second->clear();
		delete index->second;
	}
	this->diGroups.clear();
}

const wchar_t * DLT645::GetName()
{
	return L"DLT645";
}

const wchar_t * DLT645::GetDes()
{
	return L"DLT645基类";
}

int DLT645::Init()
{
	return 0;
}

int DLT645::Unload()
{
	this->isStop=true;
	this->Stop();
	return 0;
}

HWND DLT645::CreateTargetWindow(HWND hWndParent)
{
	return ::CreateDialogParam((HINSTANCE)g_HModule,MAKEINTRESOURCE(IDD_DLT645),hWndParent,DLT645WindowProc,(LPARAM)this);
}

bool DLT645::SetConnection(Connection *con)
{
	this->connection=con;
	return true;
}

int DLT645::Stop()
{
	if(this->hWnd !=0)
	{
		::DestroyWindow(this->hWnd);
	}
	return 0;
}

bool ConverToBool(const wchar_t * data)
{
	if(_wcsicmp(data,L"true")==0)
	{
		return true;
	}
	return false;
}

DLT645Cmd * DLT645::GetCmd(const wchar_t *name)
{
	for(size_t i=0;i<this->cmds.size();i++)
	{
		if(_tcsicmp(this->cmds[i]->GetName(),name) ==0)
		{
			return this->cmds[i];
		}
	}
	return 0;
}

bool DLT645::LoadCmdFile(const wchar_t *cmdFile)
{
	assert(cmdFile);
	XmlHelper xmlDoc;
	wchar_t filePath[MAX_PATH]={0};
	_tcscpy_s(filePath,MAX_PATH,cmdFile);
	if(GetAbsoFilePath(filePath)==false)
	{
		return false;
	}
	if(xmlDoc.LoadFile(filePath) ==false)
	{
		return false;
	}
	IXMLDOMNodeList *cmdNodes=0;
	if(xmlDoc.GetDoucumentElement()->selectNodes(L"/DLT645Cmd/Cmd",&cmdNodes) != S_OK)
	{
		return false;
	}
	IXMLDOMNode * cmdNode=0;
	VARIANT value;
	while(cmdNodes->nextNode(&cmdNode) ==S_OK)
	{
		DLT645Cmd *cmd=new DLT645Cmd();
		IXMLDOMNode *node=0;
		//address
		if(cmdNode->selectSingleNode(L"Address",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetAddress(value.bstrVal);
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
			continue;
		cmd->SetAddressEnable(ConverToBool(value.bstrVal));

		//Cmd
		if(cmdNode->selectSingleNode(L"Cmd",&node) !=S_OK)
			continue;
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetCmd(_wtoi(value.bstrVal));
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
		{
			continue;
		}

		//DI
		if(cmdNode->selectSingleNode(L"DI",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetDI(value.bstrVal);
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
			continue;
		cmd->SetDIEnable(ConverToBool(value.bstrVal));

		//UserCode
		if(cmdNode->selectSingleNode(L"UserCode",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetUserCode(value.bstrVal);
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
			continue;
		cmd->SetUserCodeEnable(ConverToBool(value.bstrVal));

		//Password
		if(cmdNode->selectSingleNode(L"Password",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetPassword(value.bstrVal);
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
			continue;
		cmd->SetPasswordEnable(ConverToBool(value.bstrVal));

		//data
		if(cmdNode->selectSingleNode(L"Data",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetData(value.bstrVal);
		if(XmlHelper::GetAttribute(node,L"enable",&value) != true)
			continue;
		cmd->SetPasswordEnable(ConverToBool(value.bstrVal));

		//name
		if(cmdNode->selectSingleNode(L"Name",&node) !=S_OK)
		{
			continue;
		}
		if(XmlHelper::GetAttribute(node,L"value",&value) != true)
		{
			continue;
		}
		cmd->SetName(value.bstrVal);
		this->cmds.push_back(cmd);
	}
	xmlDoc.Close();
	return true;
}

bool DLT645::LoadDIFile(const wchar_t * diFile)
{
	assert(diFile);
	XmlHelper xmlDoc;
	wchar_t filePath[MAX_PATH]={0};
	_tcscpy_s(filePath,MAX_PATH,diFile);
	if(GetAbsoFilePath(filePath)==false)
	{
		return false;
	}
	if(xmlDoc.LoadFile(filePath) ==false)
	{
		return false;
	}
	IXMLDOMNodeList *diGroupNodes=0;
	if(xmlDoc.GetDoucumentElement()->selectNodes(L"/DLT645DI/DIGroup",&diGroupNodes) != S_OK)
	{
		return false;
	}
	IXMLDOMNode * diGroupNode=0;
	VARIANT value;
	while(diGroupNodes->nextNode(&diGroupNode) ==S_OK)
	{
		IXMLDOMNode *diNode=0;
		IXMLDOMNodeList *diNodes=0;
		std::vector<DLT645DI *> *diGroup=new std::vector<DLT645DI *>();
		if(XmlHelper::GetAttribute(diGroupNode,L"group",&value)==false)
		{
			continue;
		}
		wchar_t *pGroup=0;
		DLT645Frame::DupString(&pGroup,value.bstrVal,false);
		this->diGroups[pGroup]=diGroup;
		//DI结点
		if(diGroupNode->selectNodes(L"DI",&diNodes) ==S_OK)
		{
			while(diNodes->nextNode(&diNode) ==S_OK)
			{
				DLT645DI *di=new DLT645DI();
				//读取值
				if(XmlHelper::GetAttribute(diNode,L"value",&value)==false)
				{
					continue;
				}
				di->SetDI(value.bstrVal);
				//读取 描述
				if(XmlHelper::GetAttribute(diNode,L"des",&value) ==false)
				{
					continue;
				}
				di->SetDes(value.bstrVal);
				diGroup->push_back(di);
			}
			continue;
		}
	}
	return true;
}

void UpdateUI(HWND hDlg)
{
	if(g_IsUpdateCmd==true)
	{
		return ;
	}
	g_DLT645FrameSend->UpdateDataFromUI(hDlg);
	int len=g_DLT645FrameSend->GetFrameLen();
	char *buf=new char[len+1];
	int realFrameLen=0;
	if(g_DLT645FrameSend->WrapFrame(buf,len+1,&realFrameLen) ==true)
	{
		wchar_t *tmp=new wchar_t[2*len+1];
		tmp[2*len]=0;
		assert(_CrtCheckMemory());
		DLT645Frame::ExpandBCDString(buf,len,tmp);
		SetDlgItemText(hDlg,IDC_DATATOSEND,tmp);
		assert(_CrtCheckMemory());
		delete tmp;
	}
}

bool DLT645::SendData(char *buf,int offset,int len)
{
	int ret=this->connection->WriteData(buf,offset,len);
	return ret==len;
}

HWND CreateTabPageAndContent(HWND hTabControl,wchar_t *title,int index)
{
	TCITEM tapPage={0};
	HWND tabpage=0;
	RECT rect={0};
	int ret=0;
	tapPage.mask=TCIF_TEXT;
	tapPage.pszText=title;
	if(TabCtrl_InsertItem(hTabControl,index,&tapPage)==-1)
	{
		assert(0);
	}
	::GetClientRect(hTabControl,&rect);
	RECT itemSize={0};
	TabCtrl_GetItemRect(hTabControl, index, &itemSize);

	//创建listview 
	HWND listView =CreateWindow(WC_LISTVIEW,L"",
		WS_CHILD | LVS_REPORT,0,itemSize.bottom+1,
		rect.right-rect.left,
		rect.bottom-rect.top-itemSize.bottom,
		hTabControl,0,(HINSTANCE)g_HModule,0);

	ListView_SetExtendedListViewStyleEx(listView,LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES,LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES);
	LVCOLUMN col={0};
	col.mask=LVCF_TEXT | LVCF_WIDTH;

	col.pszText=L"时间";
	col.cx=200;
	ret=ListView_InsertColumn(listView,0,&col);

	col.pszText=L"数据";
	col.cx=1000;
	ret=ListView_InsertColumn(listView,1,&col);
	return listView;
}

void SetWindowWidth(HWND hWndParent,HWND hWndChild)
{
	RECT rectGroup={0};
	RECT rect={0};
	::GetWindowRect(hWndChild,&rectGroup);
	::GetWindowRect(hWndParent,&rect);
	MoveWindow(hWndChild,rectGroup.left-rect.left,rectGroup.top-rect.top,rect.right-rectGroup.left-5,rectGroup.bottom-rectGroup.top,TRUE);
}

void SetWindowWidth(HWND hDlg,int id)
{
	SetWindowWidth(hDlg,GetDlgItem(hDlg,id));
}

void AppendContent(HWND hWnd,wchar_t * data)
{
	LVITEM ldata={0};
	LVITEM ltime={0};
	wchar_t timeStr[MAX_PATH]={0};

	assert(::IsWindow(hWnd));

	//处理时间
	struct tm newTime={0};
	time_t currentTime={0};

	time(&currentTime);
	//newTime=localtime(&currentTime);
	localtime_s(&newTime,&currentTime);
	wchar_t timeTmp[100]={0};
	_wasctime_s(timeTmp,100,&newTime);
	wcscpy_s(timeStr,MAX_PATH,timeTmp);

	ldata.mask=LVIF_TEXT;
	ltime.mask=LVIF_TEXT;

	int count=ListView_GetItemCount(hWnd);

	ldata.pszText=data;
	ltime.pszText=timeStr;

	ldata.iSubItem=1;
	ldata.iItem=count;
	ltime.iItem=count;

	int ret=ListView_InsertItem(hWnd,&ltime);
	if(ret ==-1)
	{
		::MessageBox(hWnd,L"插入时间失败",L"系统提示",MB_OK);
		return  ;
	}
	ret=ListView_SetItem(hWnd,&ldata);
	if(ret ==-1)
	{
		::MessageBox(hWnd,L"插入数据失败",L"系统提示",MB_OK);
	}
}

INT_PTR CALLBACK DLT645::DLT645WindowProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			g_DLT645=(DLT645*)lParam;
			for(size_t i=0;i<g_DLT645->cmds.size();i++)
			{
				ComboBox_AddString(GetDlgItem(hDlg,IDC_CMD),g_DLT645->cmds[i]->GetName());
			}
			SendMessage(GetDlgItem(hDlg,IDC_CMD), CB_SETCURSEL, 0, 0 );
			//报建tapcontrol
			g_DLT645->hWndSended=CreateTabPageAndContent(GetDlgItem(hDlg,IDC_SENDANDRECIVE),L"发送数据",1);
			g_DLT645->hWndRecvied=CreateTabPageAndContent(GetDlgItem(hDlg,IDC_SENDANDRECIVE),L"接收数据",2);
			NMHDR   nmhdr; 
			nmhdr.code = TCN_SELCHANGE;       
			nmhdr.hwndFrom =GetDlgItem(hDlg,IDC_SENDANDRECIVE);       
			nmhdr.idFrom= IDC_SENDANDRECIVE;   
			::SendMessage(hDlg,  WM_NOTIFY,MAKELONG(TCN_SELCHANGE,0),(LPARAM)(&nmhdr));
			PostMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_CMD,CBN_SELCHANGE),(LPARAM)(GetDlgItem(hDlg,IDC_CMD)));
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		if(LOWORD(wParam) == IDC_CMD && HIWORD(wParam) == CBN_SELCHANGE )
		{
			int selectedIndex=ComboBox_GetCurSel((HWND)lParam);
			wchar_t text[MAX_PATH]={0};
			int charLen=ComboBox_GetLBText((HWND)lParam,(WPARAM)selectedIndex,text);
			DLT645Cmd * cmd=(DLT645Cmd *)(g_DLT645->GetCmd(text));
			if(cmd ==0)
			{
				return (INT_PTR)TRUE;
			}
			g_IsUpdateCmd=true;
			//设置指令内容
			SetDlgItemInt(hDlg,IDC_FECOUNT,g_DLT645FrameSend->GetFECount(),false);
			SetDlgItemText(hDlg,IDC_ADDRESS,cmd->GetAddress());
			SetDlgItemText(hDlg,IDC_DI,cmd->GetDI());
			SetDlgItemText(hDlg,IDC_DATA,cmd->GetData());
			SetDlgItemText(hDlg,IDC_USERCODE,cmd->GetUserCode());
			g_IsUpdateCmd=false;
			SetDlgItemText(hDlg,IDC_PASSWORD,cmd->GetPassword());

			//设置控件的使能
			EnableWindow(GetDlgItem(hDlg,IDC_ADDRESS),(BOOL)(cmd->GetAddressEnable()));
			EnableWindow(GetDlgItem(hDlg,IDC_DI),(BOOL)(cmd->GetDIEnable()));
			EnableWindow(GetDlgItem(hDlg,IDC_DATA),(BOOL)(cmd->GetDataEnable()));
			EnableWindow(GetDlgItem(hDlg,IDC_USERCODE),(BOOL)(cmd->GetUserCodeEnable()));
			EnableWindow(GetDlgItem(hDlg,IDC_PASSWORD),(BOOL)(cmd->GetPasswordEnable()));
			g_IsUpdateCmd=false;
		}
		if(LOWORD(wParam) ==IDC_SEND)
		{
			if(g_DLT645->connection ==0)
			{
				MessageBox(hDlg,L"请先选择通信协议",L"系统提示",MB_OK);
				return (INT_PTR)TRUE;
			}
			char *sendBuf=0;
			int sendLen=0;
			if(::IsDlgButtonChecked(hDlg,IDC_ORGINDATA) ==FALSE)
			{
				UpdateUI(hDlg);
				sendLen=g_DLT645FrameSend->GetFrameLen();
				sendBuf=new char[sendLen+1];
				if(g_DLT645FrameSend->WrapFrame(sendBuf,sendLen+1,&sendLen) ==false)
				{
					return (INT_PTR)(TRUE);
				}
			}
			else
			{
				sendLen=::GetWindowTextLength(GetDlgItem(hDlg,IDC_DATATOSEND));
				if(sendLen<=0)
				{
					return (INT_PTR)TRUE;
				}
				wchar_t *text=new wchar_t[sendLen+1];
				sendBuf =new char[sendLen+1];
				::GetDlgItemText(hDlg,IDC_DATATOSEND,text,sendLen+1);
				sendLen=DLT645Frame::MakeBCDString(text,sendBuf);
				delete text;
			}
			//发送数据
			if(g_DLT645->connection->WriteData(sendBuf,0,sendLen) ==false)
			{

			}
			// 添加到发送信息中
			wchar_t *tmpBuf=new wchar_t[sendLen*2+1];
			tmpBuf[sendLen*2]=0;
			DLT645Frame::ExpandBCDString(sendBuf,sendLen,tmpBuf);
			AppendContent(g_DLT645->hWndSended,tmpBuf);
			delete tmpBuf;
			//读取数据
			char readBuf[1024]={0};
			int readLen=g_DLT645->connection->ReadData(readBuf,1024);
			//将读取的数据添加到信息中
			wchar_t wReadBuf[1024]={0};
			DLT645Frame::ExpandBCDString(readBuf,readLen,wReadBuf);
			AppendContent(g_DLT645->hWndRecvied,wReadBuf);
		}
		if(LOWORD(wParam) ==IDC_CHOSEDI)
		{
			DISelector selector(&g_DLT645->diGroups);
			if(selector.ShowDialog(hDlg))
			{
				g_DLT645FrameSend->SetDI(selector.SelectedDI);
				SetDlgItemText(hDlg,IDC_DI,selector.SelectedDI);
			}
		}
		if(HIWORD(wParam) == EN_CHANGE)
		{
			if(LOWORD(wParam) !=IDC_FECOUNT &&
				LOWORD(wParam) !=IDC_ADDRESS &&
				LOWORD(wParam) !=IDC_DI &&
				LOWORD(wParam) !=IDC_DATA&&
				LOWORD(wParam) != IDC_USERCODE&&
				LOWORD(wParam) != IDC_PASSWORD)
			{
				break;
			}
			UpdateUI(hDlg);
		}
		if(HIWORD(wParam) ==BN_CLICKED  && LOWORD(wParam) == IDC_ORGINDATA)
		{
			int ret=IsDlgButtonChecked(hDlg,IDC_ORGINDATA) ;
			if(IsDlgButtonChecked(hDlg,IDC_ORGINDATA) ==BST_CHECKED)
			{
				EnableWindow(GetDlgItem(hDlg,IDC_DATATOSEND),TRUE);
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg,IDC_DATATOSEND),FALSE);
			}
		}
		break;
	case WM_NOTIFY :
		{
			LPNMHDR lp=(LPNMHDR)lParam;
			if(lp->code == TCN_SELCHANGE && lp->idFrom==IDC_SENDANDRECIVE)
			{
				int selIndex=TabCtrl_GetCurSel(lp->hwndFrom);
				if(selIndex==-1)
				{
					return (INT_PTR)TRUE;
				}
				HWND hwnd;
				if(selIndex==0)
				{
					hwnd=g_DLT645->hWndSended;
				}
				else
				{
					hwnd=g_DLT645->hWndRecvied;
				}
				ShowWindow(g_DLT645->hWndRecvied,SW_HIDE);
				ShowWindow(g_DLT645->hWndSended,SW_HIDE);
				int ret;
				ret =ShowWindow(hwnd,SW_SHOW);
			}
		}
	case WM_SIZE:
		{
			SetWindowWidth(hDlg,IDC_GROUPBASIC);
			SetWindowWidth(hDlg,IDC_GROUPOPERATION);
			SetWindowWidth(hDlg,IDC_GROUPADVANCE);
			SetWindowWidth(hDlg,IDC_GROUPDATATOSEND);
			SetWindowWidth(hDlg,IDC_DATATOSEND);
			SetWindowWidth(hDlg,IDC_DATA);
			SetWindowWidth(hDlg,IDC_SENDANDRECIVE);

			RECT rect={0};
			RECT itemSize={0};
			RECT rectDlg={0};
			::GetWindowRect(hDlg,&rectDlg);
			::GetWindowRect(GetDlgItem(hDlg,IDC_SENDANDRECIVE),&rect);
			//设置高度
			MoveWindow(GetDlgItem(hDlg,IDC_SENDANDRECIVE),rect.left-rectDlg.left,rect.top-rectDlg.top,rect.right-rect.left,rectDlg.bottom-rect.top,TRUE);
			::GetWindowRect(GetDlgItem(hDlg,IDC_SENDANDRECIVE),&rect);

			TabCtrl_GetItemRect(GetDlgItem(hDlg,IDC_SENDANDRECIVE), 0, &itemSize);
			MoveWindow(g_DLT645->hWndRecvied,0,itemSize.bottom+1,rect.right-rect.left,rect.bottom-rect.top-itemSize.bottom,TRUE);
			MoveWindow(g_DLT645->hWndSended,0,itemSize.bottom+1,rect.right-rect.left,rect.bottom-rect.top-itemSize.bottom,TRUE);
		}
		break;
	}
	return (INT_PTR)FALSE;
}