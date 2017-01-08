
#ifndef CONNECTION_H
#define CONNECTION_H
#include "MeterBaseComm.h"

/*
数据连接类
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
	写出数据的每一个字节时间间隔，
	如果为0表示连续出，否则每一个字节间将使用该时间进行延时
	如果该值不为0，则 bitWriteTimeOut有效，否则无效
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
	写出数据
	buf 数据地址
	offset 起始位置，以byte 计算
	len 数据长度
	返回 写出数据的长度
	返回 -1 表示出现错误
	*/
	virtual int WriteData(void * buf,int offset,int len)=0;

	/*
	读取数据
	buf 数据地址
	len 缓冲区数据长度
	返回 读取数据的长度
	返回 -1 表示出现错误
	**/
	virtual int ReadData(void * buf,int len)=0;
};
#endif