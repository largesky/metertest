#include "..\Include\DLT645\DLT6451997.h"
#include "resource.h"

DLT6451997::DLT6451997()
{
}

const wchar_t *DLT6451997::GetName()
{
	return L"DLT645_1997协议";
}

const wchar_t *DLT6451997::GetDes()
{
	return L"DLT645_1997协议";
}

int DLT6451997::Init()
{
	if(this->LoadCmdFile(L"\\Config\\DLT6451997Cmd.xml") ==false)
	{
		return 1;
	}
	if(this->LoadDIFile(L"\\Config\\DLT6451997DI.xml") ==false)
	{
		return 1;
	}
	return 0;
}