#ifndef METERBASECOMM_H
#define METERBASECOMM_H

#include <SDKDDKVer.h>

// Windows ͷ�ļ�:
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
// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <Commctrl.h>
//����������
extern "C"
{
	//��ȡ��� ����
	typedef const wchar_t * (GETPLUGINTYPECALLBACK)();

	//��ȡ�������
	typedef const wchar_t * (GETPLUGINDNAMECALLBACK)();

	//��ȡ�������
	typedef const wchar_t * (GETPLUGINDESCALLBACK)();

	//��װ���
	typedef DWORD (INSTALLCALLBACK)();

	//�Ƴ����
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