
#include "..\Include\MeterBase\KeyValueSelecter.h"
#include "resource.h"
#include <CommCtrl.h>
static KeyValueSelector * protocolSelector;
INT_PTR CALLBACK MeterSelect(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			protocolSelector=(KeyValueSelector *)lParam;
			std::map<const wchar_t*,const wchar_t *> *keyValues=&protocolSelector->KeyValues;
			//插入 列
			HWND hList=::GetDlgItem(hDlg,IDC_LIST1);
			LVCOLUMN protocolName={0};
			protocolName.pszText=L"名称";
			protocolName.mask=LVCF_TEXT|LVCF_WIDTH;
			protocolName.cx=150;
			int i=(int)	::SendMessage(hList,LVM_INSERTCOLUMN,0,(LPARAM)(&protocolName));

			LVCOLUMN protocolDes={0};
			protocolDes.pszText=L"描述";
			protocolDes.mask=LVCF_TEXT|LVCF_WIDTH;
			protocolDes.cx=400;
			i=(int)	::SendMessage(hList,LVM_INSERTCOLUMN,1,(LPARAM)(&protocolDes));

			//插入数据
			std::map<const wchar_t*,const wchar_t *>::iterator index=keyValues->begin();
			i=0;
			while(index != keyValues->end())
			{
				LVITEM itemName;
				LVITEM itemDes;
				ZeroMemory((void *)(&itemName),sizeof(itemName));
				ZeroMemory((void *)(&itemDes),sizeof(itemDes));

				itemName.mask =LVIF_TEXT;
				itemDes.mask=LVIF_TEXT;

				itemName.pszText=(wchar_t *)index->first;
				itemName.iItem=i;

				itemDes.pszText=(wchar_t *)index->second;
				itemDes.iItem=i;
				itemDes.iSubItem=1;

				ListView_InsertItem(hList,&itemName);
				ListView_SetItem(hList,&itemDes);
				index++;
				i++;
			}
			ListView_SetExtendedListViewStyleEx(hList,  LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			if(protocolSelector->WindowTitle !=0)
			{
				SetWindowText(hDlg,protocolSelector->WindowTitle);
			}
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			protocolSelector->IsOK=true;
			int selectedIndex=ListView_GetNextItem(GetDlgItem(hDlg,IDC_LIST1),-1,LVNI_SELECTED);
			if(selectedIndex <0)
			{
				MessageBox(hDlg,L"请选择相应协议",L"系统提示",MB_OK|MB_ICONQUESTION);
			}
			else
			{
				ListView_GetItemText(GetDlgItem(hDlg,IDC_LIST1),selectedIndex,0,protocolSelector->SelectedProtocolName,500);
				EndDialog(hDlg, LOWORD(wParam));
			}
			return (INT_PTR)TRUE;
		}
		if( LOWORD(wParam) == ID_CANCEL)
		{
			protocolSelector->IsOK=false;
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	case WM_SIZE:
		{
			RECT rect;
			::GetClientRect(hDlg,&rect);
			RECT btnOK;
			::GetWindowRect(GetDlgItem(hDlg,IDOK),&btnOK);
			int btnOKHigh=btnOK.bottom-btnOK.top;
			int btnOKWidth=btnOK.right-btnOK.left;
			::MoveWindow(GetDlgItem(hDlg,IDC_LIST1),0,0,rect.right,rect.bottom-(btnOK.bottom-btnOK.top )-20 ,TRUE);
			::MoveWindow(GetDlgItem(hDlg,IDOK),rect.right/2,rect.bottom-btnOKHigh-10, btnOKWidth,btnOKHigh,TRUE);
			::MoveWindow(GetDlgItem(hDlg,ID_CANCEL),rect.right/2+ btnOKWidth+10,rect.bottom-btnOKHigh-10, btnOKWidth,btnOKHigh,TRUE);
			break;
		}
	case WM_CLOSE:
		{
			EndDialog(hDlg, LOWORD(wParam));
			break;
		}
	}
	return (INT_PTR)FALSE;
}

bool KeyValueSelector::ShowSelectWindow(HWND hParent)
{
	if(hParent==0)
	{
		hParent=::GetDesktopWindow();
	}
	INT_PTR ret=DialogBoxParam((HINSTANCE)g_MeterBaseModule,MAKEINTRESOURCE(IDD_SELECTMETERPROTOCOL),hParent,MeterSelect,(LPARAM)(this));
	if(ret==-1)
	{
		return false;
	}
	return true;
}