#include "..\Include\DLT645\DLT645FrameRecv.h"


DLT645FrameRecv::DLT645FrameRecv()
{
	this->frameOrginal=0;
}

DLT645FrameRecv::~DLT645FrameRecv()
{
	if(this->frameOrginal !=0)
	{
		delete this->frameOrginal;
	}
}

int DLT645FrameRecv::GetFrameLen()
{
	if(this->GetOrignalBuf() ==0)
		return 0;
	return (int)wcslen(this->GetOrignalBuf());
}

const wchar_t *DLT645FrameRecv::GetOrignalBuf()
{
	return this->frameOrginal;
}

bool DLT645FrameRecv::ParseFrame(char *buf,int buflen)
{
	return false;
}