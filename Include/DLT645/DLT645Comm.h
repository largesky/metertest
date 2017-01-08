#ifndef DLT645COMM_H
#define DLT645COMM_H
// Windows ͷ�ļ�:
#include <SDKDDKVer.h>
#include <windows.h>

#include "..\..\Include\MeterBase\MeterBaseAll.h"
#include <string>
#include <string.h>
#include <xstring>
#include <assert.h>
#ifdef DLT645_EXPORTS
#define DLT645_API __declspec(dllexport)
#else
#define DLT645_API __declspec(dllimport)
#endif
extern "C"
{
	//��ȡ��� ����
	DLT645_API const wchar_t * GETPLUGINTYPE();

	//��ȡ�������
	DLT645_API const wchar_t * GETPLUGINNAME();

	//��ȡ�������
	DLT645_API const wchar_t * GETPLUGINDES();

	//��װ���
	DLT645_API DWORD INSTALL();

	//�Ƴ����
	DLT645_API DWORD UNINSTALL();
}

extern HMODULE g_HModule;
class DLT645;
class DLT645FrameSend;
extern DLT645 *g_DLT645;
extern DLT645FrameSend *g_DLT645FrameSend;
extern bool g_IsUpdateCmd;
#endif