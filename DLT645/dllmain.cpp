// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "..\Include\DLT645\DLT645Comm.h"
#include "..\Include\DLT645\DLT6451997.h"
#include "..\Include\DLT645\DLT6452007.h"

HMODULE g_HModule;
DLT6451997 *g_DLT6451997;
DLT6452007 *g_DLT6452007;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	g_HModule=hModule;
	g_DLT6451997=0;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C"
{
	//获取插件 类型
	const wchar_t * GETPLUGINTYPE()
	{
		return L"MeterProtocol";
	}

	//获取插件名称
	const wchar_t * GETPLUGINNAME()
	{
		return L"DLT645MeterProtocol";
	}

	//获取插件描述
	const wchar_t * GETPLUGINDES()
	{
		return L"DLT645协议，包括1997与2007";
	}

	//安装插件
	DWORD INSTALL()
	{
		g_DLT6451997=new DLT6451997();
		MeterProtocolManager::GetInstance()->InstallItem(g_DLT6451997);

		g_DLT6452007 = new DLT6452007();
		MeterProtocolManager::GetInstance()->InstallItem(g_DLT6452007);
		return 0;
	}

	//移出插件
	DWORD UNINSTALL()
	{
		if(g_DLT6451997)
		{
			MeterProtocolManager::GetInstance()->UninstallItem(g_DLT6451997->GetName());
			delete g_DLT6451997;
			g_DLT6451997=0;
		}
		if(g_DLT6452007)
		{
			MeterProtocolManager::GetInstance()->UninstallItem(g_DLT6452007->GetName());
			delete g_DLT6452007;
			g_DLT6452007=0;
		}
		return 0;
	}
}