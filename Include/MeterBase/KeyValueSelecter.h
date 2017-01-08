
#ifndef KEYVALUESELECTER_H
#define KEYVALUESELECTER_H
#include "MeterBaseComm.h"

INT_PTR CALLBACK MeterSelect(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

//协议选择工具结构信息
class METERBASE_API KeyValueSelector
{
public :
	wchar_t* SelectedProtocolName;
	bool IsOK;
	std::map<const wchar_t*,const wchar_t*> KeyValues;
	wchar_t* WindowTitle;

	KeyValueSelector()
	{
		this->SelectedProtocolName=new wchar_t[500];
		this->WindowTitle=0;
		this->IsOK=false;
	}

	bool ShowSelectWindow(HWND hParent);

	~KeyValueSelector()
	{
		delete (this->SelectedProtocolName);
	}
};
#endif