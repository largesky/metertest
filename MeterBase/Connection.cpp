
#include "..\Include\MeterBase\Connection.h"


const  int Connection::STREAM_TYPE_COMM=1;
const  int Connection::STREAM_TYPE_UDP=2;
const  int Connection::STREAM_TYPE_TCP=3;
const  int Connection::STREAM_TYPE_FILEMAPPING=4;
const  int Connection::STATE_CLOSE=0;
const  int Connection::STATE_OPEN=1;

Connection::Connection()
{
	this->bitReadTimeOut=500;
	this->frameReadTimeOut=2000;
	this->bitWriteTimeOut=100;
	this->bitWriteIntervalTime=0;
}

int Connection::GetBitReadTimeOut()
{
	return this->bitReadTimeOut;
}

void Connection::SetBitReadTimeOut(int time)
{
	this->bitReadTimeOut=time;
}

int Connection::GetFrameReadTimeOut()
{
	return this->frameReadTimeOut;
}

void Connection::SetFrameReadTimeOut(int time)
{
	this->frameReadTimeOut=time;
}

int Connection::GetBitWriteTimeOut()
{
	return this->bitWriteTimeOut;
}

void Connection::SetBitWriteTimeOut(int time)
{
	this->bitWriteTimeOut=time;
}

int Connection::GetBitWriteIntervalTime()
{
	return this->bitWriteIntervalTime;
}

void Connection::SetBitWriteIntervalTime(int time)
{
	this->bitWriteIntervalTime=time;
}
