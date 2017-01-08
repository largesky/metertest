
#include "resource.h"
#include "..\Include\DLT645\DLT6452007.h"

DLT6452007::DLT6452007()
{
}

const wchar_t *DLT6452007::GetName()
{
	return L"DLT645_2007协议";
}

const wchar_t *DLT6452007::GetDes()
{
	return L"DLT645_2007协议";
}

int DLT6452007::Init()
{
	if(this->LoadCmdFile(L"\\Config\\DLT6452007Cmd.xml") ==false)
	{
		return 1;
	}
	if(this->LoadDIFile(L"\\Config\\DLT6452007DI.xml") ==false)
	{
		return 1;
	}
	return 0;
}