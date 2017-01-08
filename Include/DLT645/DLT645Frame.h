#ifndef DLT645FRAME_H
#define DLT645FRAME_H

#include "DLT645Comm.h"

class DLT645_API DLT645Frame
{
public :
	static  wchar_t FE;

	/*
		��һ�� wchar_t ��ʾ���ַ�ת���� ��Ӧ�� ����
	*/
	static char WCharToDigit(wchar_t chr);

	/*
		��һ������ ת���� ��Ӧ�� wchar_t
	**/
	static wchar_t DigitToWChar(char chr);

	/*
	�� data ָ������� ���� BCD��װ����ת��������ָ����ֵ addChar ���������浽buf��
	*/
	static int ReverseAndAdd(const wchar_t *data,size_t len,char *buf,char addChar);

	/*
		ʹ�� ch1 �� ch2 ����һ�� BCD char
		���� MakeBCDChar(L'1',L'a') ������ 0x1A
	*/
	static char MakeBCDChar(wchar_t ch1,wchar_t ch2);

	/*
	���ַ���ת���� bcd ��ʾ�� ����
	���� L"1afd34" ת���� 0x1A,0xFD,0x34
	*/
	static int MakeBCDString(wchar_t *source,char *buf);

	/*
		��һ��BCD char ת�������� wchar_t
		����
		wchar_t ch1,ch2;
		char a=0xaf;
		ExpandBCDChar(A,&ch1,&ch2) 
		�� ch1=L'A',ch2=L'F'
	*/
	static void ExpandBCDChar(char value,wchar_t *ch1,wchar_t *ch2);

	/*
	��BCD �ַ���ת���� wchar_t �ַ���
	*/
	static void ExpandBCDString(char *value,int len,wchar_t *buf);

	/*
		���� ָ�����ݵ�XORֵ
	**/
	static char GetXOR(const char *buf,int offset,int len);

	/*
	�����ַ��ȥ����β�ո񣬲���䣬ʹ֮���� 12 ���ַ�
	**/
	static bool MakeAddressOK(wchar_t **address);

	/*
	�ַ������ƣ�
	deleteDst �Ƿ��ͷ� dstָ����ָ������ݣ������ָ��ָ������
	*/
	static bool DupString(wchar_t ** dst,const wchar_t * source,bool deleteDst);

protected :
	void UpdateDataFromUI(HWND hDlg);
	wchar_t *address;
	wchar_t cmd;
	wchar_t *di;
	wchar_t *userCode;
	wchar_t *password;
	wchar_t *data;
	wchar_t xor;

	int feCount;
public :

	DLT645Frame();
	~DLT645Frame();

	const wchar_t *GetAddress();
	void SetAddress(const wchar_t *address);

	wchar_t GetCmd();
	void SetCmd(wchar_t cmd);

	const wchar_t *GetDI();
	void SetDI(const wchar_t *di);

	const wchar_t *GetUserCode();
	void SetUserCode(const wchar_t *userCode);

	const wchar_t *GetPassword();
	void SetPassword(const wchar_t * password);

	const wchar_t *GetData();
	void SetData(const wchar_t * data);

	int GetDataLen();

	virtual int GetFrameLen()=0;

	int GetFECount();

	void SetFECount(int feCount);
};
#endif