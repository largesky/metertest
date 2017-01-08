#ifndef DLT645COMM_H
#define DLT645COMM_H
// Windows 头文件:
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
	//获取插件 类型
	DLT645_API const wchar_t * GETPLUGINTYPE();

	//获取插件名称
	DLT645_API const wchar_t * GETPLUGINNAME();

	//获取插件描述
	DLT645_API const wchar_t * GETPLUGINDES();

	//安装插件
	DLT645_API DWORD INSTALL();

	//移出插件
	DLT645_API DWORD UNINSTALL();
}

extern HMODULE g_HModule;
class DLT645;
class DLT645FrameSend;
extern DLT645 *g_DLT645;
extern DLT645FrameSend *g_DLT645FrameSend;
extern bool g_IsUpdateCmd;
#endif