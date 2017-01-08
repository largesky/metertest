#include "..\Include\DLT645\DLT645Cmd.h"
#include "..\Include\DLT645\DLT645Frame.h"
DLT645Cmd::DLT645Cmd()
{
	this->address=0;
	this->cmd=0;
	this->di=0;
	this->userCode=0;
	this->password=0;
	this->data=0;
	this->cmdName=0;

	this->addressEnable=true;
	this->diEnable=true;
	this->userCodeEnable=true;
	this->passwordEnable=true;
	this->dataEnable=true;
}

DLT645Cmd::~DLT645Cmd()
{
	delete this->address;
	delete this->di;
	delete this->userCode;
	delete this->password;
	delete this->cmdName;
	delete this->data;
}


const wchar_t *DLT645Cmd::GetAddress()
{
	return this->address;
}

void DLT645Cmd::SetAddress(const wchar_t* address)
{
	DLT645Frame::DupString(&this->address,address,true);
}

wchar_t DLT645Cmd::GetCmd()
{
	return this->cmd;
}

void DLT645Cmd::SetCmd(wchar_t cmd)
{
	this->cmd=(char)cmd;
}

const wchar_t *DLT645Cmd::GetDI()
{
	return this->di;
}

void DLT645Cmd::SetDI(const wchar_t *di)
{
	DLT645Frame::DupString(&this->di,di,true);
}

const wchar_t *DLT645Cmd::GetUserCode()
{
	return this->userCode;
}

void DLT645Cmd::SetUserCode(const wchar_t *userCode)
{
	DLT645Frame::DupString(&this->userCode,userCode,true);
}

const wchar_t *DLT645Cmd::GetPassword()
{
	return this->password;
}

void DLT645Cmd::SetPassword(const wchar_t * password)
{
	DLT645Frame::DupString(&this->password,password,true);
}

const wchar_t *DLT645Cmd::GetData()
{
	return this->data;
}

void DLT645Cmd::SetData(const wchar_t *data)
{
	DLT645Frame::DupString(&this->data,data,true);
}

bool DLT645Cmd::GetAddressEnable()
{
	return this->addressEnable;
}

void DLT645Cmd::SetAddressEnable(bool enable)
{
	this->addressEnable=enable;
}

bool DLT645Cmd::GetDIEnable()
{
	return this->diEnable;
}

void DLT645Cmd::SetDIEnable(bool enable)
{
	this->diEnable=enable;
}

bool DLT645Cmd::GetUserCodeEnable()
{
	return this->userCodeEnable;
}

void DLT645Cmd::SetUserCodeEnable(bool enable)
{
	this->userCodeEnable=enable;
}

bool DLT645Cmd::GetPasswordEnable()
{
	return this->passwordEnable;
}

void DLT645Cmd::SetPasswordEnable(bool enable)
{
	 this->passwordEnable=enable;
}

bool DLT645Cmd::GetDataEnable()
{
	return this->dataEnable;
}

void DLT645Cmd::SetDataEnable(bool enable)
{
	this->dataEnable=enable;
}

const wchar_t * DLT645Cmd::GetName()
{
	return this->cmdName;
}

void DLT645Cmd::SetName(const wchar_t *name)
{
	DLT645Frame::DupString(&this->cmdName,name,true);
}