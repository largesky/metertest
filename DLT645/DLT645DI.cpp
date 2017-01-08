#include "..\Include\DLT645\DLT645DI.h"
#include "..\Include\DLT645\DLT645Frame.h"

DLT645DI::DLT645DI()
{
	this->di=0;
	this->des=0;
}

DLT645DI::~DLT645DI()
{
	delete this->di;
	delete this->des;
}

const wchar_t *DLT645DI::GetDI()
{
	return this->di;
}

void DLT645DI::SetDI(const wchar_t *di)
{
	DLT645Frame::DupString(&this->di,di,true);
}

const wchar_t *DLT645DI::GetDes()
{
	return this->des;
}

void DLT645DI::SetDes(const wchar_t *des)
{
	DLT645Frame::DupString(&this->des,des,true);
}