#ifndef SERIALPORTCOMM_H
#define SERIALPORTCOMM_H

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
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

#include "..\MeterBase\Connection.h"

#ifdef SERIALPORT_EXPORTS
#define SERIALPORT_API __declspec(dllexport)
#else
#define SERIALPORT_API __declspec(dllimport)
#endif

extern HMODULE g_HModule;

extern "C"
{
	//��ȡ��� ����
	SERIALPORT_API const wchar_t * GETPLUGINTYPE();

	//��ȡ�������
	SERIALPORT_API const wchar_t * GETPLUGINNAME();

	//��ȡ�������
	SERIALPORT_API const wchar_t * GETPLUGINDES();

	//��װ���
	SERIALPORT_API DWORD INSTALL();

	//�Ƴ����
	SERIALPORT_API DWORD UNINSTALL();
}

#endif