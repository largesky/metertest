#ifndef DLT645FRAME_H
#define DLT645FRAME_H

#include "DLT645Comm.h"

class DLT645_API DLT645Frame
{
public :
	static  wchar_t FE;

	/*
		将一个 wchar_t 表示的字符转换成 对应的 数字
	*/
	static char WCharToDigit(wchar_t chr);

	/*
		将一个数字 转换成 对应的 wchar_t
	**/
	static wchar_t DigitToWChar(char chr);

	/*
	将 data 指向的数据 进行 BCD组装，反转，并加上指定的值 addChar 将其结果储存到buf中
	*/
	static int ReverseAndAdd(const wchar_t *data,size_t len,char *buf,char addChar);

	/*
		使用 ch1 和 ch2 生成一个 BCD char
		例如 MakeBCDChar(L'1',L'a') 将返回 0x1A
	*/
	static char MakeBCDChar(wchar_t ch1,wchar_t ch2);

	/*
	将字符串转换成 bcd 表示的 数据
	例如 L"1afd34" 转换成 0x1A,0xFD,0x34
	*/
	static int MakeBCDString(wchar_t *source,char *buf);

	/*
		将一个BCD char 转换成两个 wchar_t
		例如
		wchar_t ch1,ch2;
		char a=0xaf;
		ExpandBCDChar(A,&ch1,&ch2) 
		则 ch1=L'A',ch2=L'F'
	*/
	static void ExpandBCDChar(char value,wchar_t *ch1,wchar_t *ch2);

	/*
	将BCD 字符串转换成 wchar_t 字符串
	*/
	static void ExpandBCDString(char *value,int len,wchar_t *buf);

	/*
		计算 指定数据的XOR值
	**/
	static char GetXOR(const char *buf,int offset,int len);

	/*
	处理地址，去处首尾空格，并填充，使之满足 12 个字符
	**/
	static bool MakeAddressOK(wchar_t **address);

	/*
	字符串复制，
	deleteDst 是否释放 dst指针所指向的数据，如果该指针指向数据
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