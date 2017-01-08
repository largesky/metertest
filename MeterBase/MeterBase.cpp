#include "..\Include\MeterBase\MeterBase.h"

bool GetAbsoFilePath(wchar_t *file)
{
	wchar_t configFilePath[MAX_PATH]={0};
	if(GetModuleFileName(NULL,configFilePath,MAX_PATH) ==0)
	{
		return false;
	}
	std::wstring filePath(configFilePath);
	std::wstring::size_type index=filePath.find_last_of(L'\\');
	if(index <=0)
	{
		return false;
	}
	filePath.resize(index);
	filePath.append(file);
	_tcscpy_s(file,MAX_PATH, filePath.c_str());
	return 1;
}


bool IsVistaOrLater()
{
	OSVERSIONINFOW infoEx={sizeof(OSVERSIONINFOW)};
	if(::GetVersionEx(&infoEx) ==FALSE)
	{
		return false;
	}
	if(infoEx.dwMajorVersion >=6)
	{
		return true;
	}
	return false;
}