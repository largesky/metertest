#ifndef DLT645CMD_H
#define DLT645CMD_H

#include "DLT645Comm.h"

class DLT645_API DLT645Cmd
{
protected :
	wchar_t *address;
	char cmd;
	wchar_t *di;
	wchar_t *userCode;
	wchar_t *password;
	wchar_t *data;

	wchar_t *cmdName;

	bool addressEnable;
	bool diEnable;
	bool userCodeEnable;
	bool passwordEnable;
	bool dataEnable;

public :

	DLT645Cmd();
	~DLT645Cmd();

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

	bool GetAddressEnable();
	void SetAddressEnable(bool enable);

	bool GetDIEnable();
	void SetDIEnable(bool enable);

	bool GetUserCodeEnable();
	void SetUserCodeEnable(bool enable);

	bool GetPasswordEnable();
	void SetPasswordEnable(bool enable);

	bool GetDataEnable();
	void SetDataEnable(bool enable);

	const wchar_t * GetName();
	void SetName(const wchar_t * name);
};
#endif