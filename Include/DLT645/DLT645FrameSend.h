#ifndef DLT645FRAMESEND_H
#define DLT645FRAMESEND_H

#include "DLT645Frame.h"

class DLT645_API DLT645FrameSend : public DLT645Frame
{
public :
	int GetDataLen();

	int GetFrameLen();
	/*
	组帧
	buf 用来结果数据
	buflen 指示结果的数据长度
	frameLen 返回整个帧的长度
	**/
	bool WrapFrame(char *buf, int buflen, int *frameLen);

	void UpdateDataFromUI(HWND hDlg);
};
#endif