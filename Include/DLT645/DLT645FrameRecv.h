#ifndef DLT645FRAMERECV_H
#define DLT645FRAMERECV_H

#include "DLT645Frame.h"
class DLT645_API DLT645FrameRecv : public DLT645Frame
{
protected :
	wchar_t * frameOrginal;
public :
	DLT645FrameRecv();
	~DLT645FrameRecv();

	int GetFrameLen();

	wchar_t GetXor();

	const wchar_t * GetOrignalBuf();

	/*
	解析帧
	buf 要解析的数据
	buflen 数据的长度
	**/
	bool ParseFrame(char *buf,int buflen);

};
#endif