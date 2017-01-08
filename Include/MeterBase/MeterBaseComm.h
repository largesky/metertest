#ifndef METERBASECOMM_H
#define METERBASECOMM_H

#include <SDKDDKVer.h>

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
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <Commctrl.h>
//定义插件方法
extern "C"
{
	//获取插件 类型
	typedef const wchar_t * (GETPLUGINTYPECALLBACK)();

	//获取插件名称
	typedef const wchar_t * (GETPLUGINDNAMECALLBACK)();

	//获取插件描述
	typedef const wchar_t * (GETPLUGINDESCALLBACK)();

	//安装插件
	typedef DWORD (INSTALLCALLBACK)();

	//移出插件
	typedef DWORD (UNINSTALLCALLBACK)();
}

#ifndef Byte
#define Byte unsigned char
#endif

#ifdef METERBASE_EXPORTS
#define METERBASE_API __declspec(dllexport)
#else
#define METERBASE_API __declspec(dllimport)
#endif
extern HMODULE g_MeterBaseModule;

#pragma warning(disable :4251)
#endif