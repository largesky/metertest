#include "..\Include\DLT645\DLT645DI.h"
#include "..\Include\DLT645\DISelector.h"
#include "resource.h"

DISelector::DISelector(std::map<const wchar_t *,std::vector<DLT645DI *> *> *diGroups)
{
	assert(diGroups);
	this->diGroups=diGroups;
}

bool DISelector::ShowDialog(HWND hWnd)
{
	INT_PTR ret=DialogBoxParam((HINSTANCE)g_HModule,MAKEINTRESOURCE(IDD_DISELECTOR),hWnd,&DISelector::DISelectorProc,(LPARAM)this);
	return ret == IDOK;
}

DISelector *g_DISelector;
INT_PTR CALLBACK DISelector::DISelectorProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			int ret=0;
			g_DISelector=(DISelector *)lParam;
			ListView_EnableGroupView(GetDlgItem(hDlg,IDC_LIST1),TRUE);
			ListView_SetExtendedListViewStyleEx(GetDlgItem(hDlg,IDC_LIST1), LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES  ,LVS_EX_FULLROWSELECT |LVS_EX_GRIDLINES );
			//SendMessage(GetDlgItem(hDlg,IDC_LIST1), LVM_SETVIEW, LV_VIEW_TILE, 0); // 启用平铺

			//插入 列
			LVCOLUMN column={sizeof(LVCOLUMN)};
			column.mask=LVCF_TEXT|LVCF_WIDTH;
			column.pszText=L"DI值";
			column.cx=100;
			ret=ListView_InsertColumn(GetDlgItem(hDlg,IDC_LIST1),0,&column);
			column.cx=400;
			column.pszText=L"描述";
			ret=ListView_InsertColumn(GetDlgItem(hDlg,IDC_LIST1),1,&column);
			DWORD style=0;
			LVGROUP item;
			ZeroMemory(&item,sizeof(item));
			item.cbSize=sizeof(item);
			
			if(IsVistaOrLater())
			{
				item.mask=LVGF_GROUPID | LVGF_HEADER| LVGF_ALIGN | LVGF_STATE;
				item.state =LVGS_COLLAPSIBLE;
			}
			else
			{
				item.mask=LVGF_GROUPID | LVGF_HEADER| LVGF_ALIGN;
			}
			item.uAlign=LVGA_HEADER_LEFT;

			std::map<const wchar_t *,std::vector<DLT645DI *> *>::iterator index=g_DISelector->diGroups->begin();
			ret=0;
			int itemIndex=0;
			int groupIndex=0;
			while(index != g_DISelector->diGroups->end())
			{
				item.pszHeader=(wchar_t *)index->first;
				item.iGroupId=groupIndex;
				ret=(int)ListView_InsertGroup(GetDlgItem(hDlg,IDC_LIST1),groupIndex,&item);

				//插入数据
				for(size_t i=0;i<index->second->size();i++)
				{
					int isOK=0;
					LVITEM insertItem={sizeof(LVITEM)};
					insertItem.mask=LVIF_TEXT|LVIF_GROUPID;
					insertItem.pszText=(wchar_t *)index->second->at(i)->GetDI();
					insertItem.iItem=itemIndex;
					insertItem.iGroupId=groupIndex;
					isOK=ListView_InsertItem(GetDlgItem(hDlg,IDC_LIST1),&insertItem);
					
					LVITEM diDes={sizeof(LVITEM)};
					diDes.mask=LVIF_TEXT/*|LVIF_GROUPID*/;
					diDes.pszText=(wchar_t *)index->second->at(i)->GetDes();
					diDes.iItem=itemIndex;
					diDes.iSubItem=1;
					//diDes.iGroupId=groupIndex;
					isOK=ListView_SetItem(GetDlgItem(hDlg,IDC_LIST1),&diDes);
					if(isOK ==FALSE)
					{
						int sfsd=3454;
					}
					itemIndex++;
				}
				index++;
				groupIndex++;
			}
			return (INT_PTR)TRUE;
		}
	case WM_COMMAND:
		if(LOWORD(wParam) ==IDOK)
		{
			int selectedIndex=ListView_GetNextItem(GetDlgItem(hDlg,IDC_LIST1),-1,LVNI_SELECTED);
			if(selectedIndex <0)
			{
				MessageBox(hDlg,L"请选择相应的DI",L"系统提示",MB_OK);
				return (INT_PTR)TRUE;
			}
			ListView_GetItemText(GetDlgItem(hDlg,IDC_LIST1),selectedIndex,0,g_DISelector->SelectedDI,8);
			EndDialog(hDlg,IDOK);
			return (INT_PTR)TRUE;
		}
		else if(LOWORD(wParam) ==IDCANCEL)
		{
			EndDialog(hDlg,IDCANCEL);
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
			::MoveWindow(GetDlgItem(hDlg,IDCANCEL),rect.right/2+ btnOKWidth+10,rect.bottom-btnOKHigh-10, btnOKWidth,btnOKHigh,TRUE);
			break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}