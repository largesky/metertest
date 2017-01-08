#ifndef DLT645FRAMESEND_H
#define DLT645FRAMESEND_H

#include "DLT645Frame.h"

class DLT645_API DLT645FrameSend : public DLT645Frame
{
public :
	int GetDataLen();

	int GetFrameLen();
	/*
	��֡
	buf �����������
	buflen ָʾ��������ݳ���
	frameLen ��������֡�ĳ���
	**/
	bool WrapFrame(char *buf, int buflen, int *frameLen);

	void UpdateDataFromUI(HWND hDlg);
};
#endif