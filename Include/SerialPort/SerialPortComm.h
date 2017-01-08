#ifndef SERIALPORTCOMM_H
#define SERIALPORTCOMM_H

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>
#include <map>
#include <string>
#include <string.h>
#include <fstream> 
#include <iostream> 
#include <tchar.h>
#include <vector>
#include <xdebug>
#include <assert.h>

#include "..\MeterBase\Connection.h"

#ifdef SERIALPORT_EXPORTS
#define SERIALPORT_API __declspec(dllexport)
#else
#define SERIALPORT_API __declspec(dllimport)
#endif

extern HMODULE g_HModule;

extern "C"
{
	//获取插件 类型
	SERIALPORT_API const wchar_t * GETPLUGINTYPE();

	//获取插件名称
	SERIALPORT_API const wchar_t * GETPLUGINNAME();

	//获取插件描述
	SERIALPORT_API const wchar_t * GETPLUGINDES();

	//安装插件
	SERIALPORT_API DWORD INSTALL();

	//移出插件
	SERIALPORT_API DWORD UNINSTALL();
}

#endif