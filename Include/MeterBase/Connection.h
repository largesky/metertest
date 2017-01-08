
#ifndef CONNECTION_H
#define CONNECTION_H
#include "MeterBaseComm.h"

/*
����������
**/
class METERBASE_API Connection
{
public :
	static const int STREAM_TYPE_COMM;
	static const int STREAM_TYPE_UDP;
	static const int STREAM_TYPE_TCP;
	static const int STREAM_TYPE_FILEMAPPING;

	static const int STATE_OPEN;
	static const int STATE_CLOSE;
protected :
	int bitReadTimeOut;
	int frameReadTimeOut;
	int bitWriteTimeOut;

	/*
	д�����ݵ�ÿһ���ֽ�ʱ������
	���Ϊ0��ʾ������������ÿһ���ֽڼ佫ʹ�ø�ʱ�������ʱ
	�����ֵ��Ϊ0���� bitWriteTimeOut��Ч��������Ч
	**/
	int bitWriteIntervalTime;

	CRITICAL_SECTION readCriticalSection;
	CRITICAL_SECTION writeCritialSection;

public :

	Connection();

	int GetBitReadTimeOut();

	void SetBitReadTimeOut(int time);

	int GetFrameReadTimeOut();

	void SetFrameReadTimeOut(int time);

	int GetBitWriteTimeOut();

	void SetBitWriteTimeOut(int time);

	int GetBitWriteIntervalTime();

	void SetBitWriteIntervalTime(int time);

	virtual const wchar_t * GetName()=0;

	virtual const wchar_t * GetDes()=0;

	virtual int GetType()=0;

	virtual bool ShowConfigWindow(HWND parent)=0;

	virtual bool Open()=0;

	virtual bool Close()=0;

	/*
	д������
	buf ���ݵ�ַ
	offset ��ʼλ�ã���byte ����
	len ���ݳ���
	���� д�����ݵĳ���
	���� -1 ��ʾ���ִ���
	*/
	virtual int WriteData(void * buf,int offset,int len)=0;

	/*
	��ȡ����
	buf ���ݵ�ַ
	len ���������ݳ���
	���� ��ȡ���ݵĳ���
	���� -1 ��ʾ���ִ���
	**/
	virtual int ReadData(void * buf,int len)=0;
};
#endif