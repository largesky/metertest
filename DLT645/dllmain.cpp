// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
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
	//��ȡ��� ����
	const wchar_t * GETPLUGINTYPE()
	{
		return L"MeterProtocol";
	}

	//��ȡ�������
	const wchar_t * GETPLUGINNAME()
	{
		return L"DLT645MeterProtocol";
	}

	//��ȡ�������
	const wchar_t * GETPLUGINDES()
	{
		return L"DLT645Э�飬����1997��2007";
	}

	//��װ���
	DWORD INSTALL()
	{
		g_DLT6451997=new DLT6451997();
		MeterProtocolManager::GetInstance()->InstallItem(g_DLT6451997);

		g_DLT6452007 = new DLT6452007();
		MeterProtocolManager::GetInstance()->InstallItem(g_DLT6452007);
		return 0;
	}

	//�Ƴ����
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