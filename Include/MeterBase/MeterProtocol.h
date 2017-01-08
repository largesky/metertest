
#ifndef METERPROTOCOL_H
#define METERPROTOCOL_H
#include "MeterBaseComm.h"

class Connection;
class METERBASE_API MeterProtocol
{
public:

	Connection *connection;
public :

	MeterProtocol();

	virtual const wchar_t* GetName()=0;

	virtual const wchar_t* GetDes()=0;

	virtual int  Init()=0;

	virtual int Unload()=0;

	virtual HWND CreateTargetWindow(HWND hWndParent)=0;

	virtual bool SetConnection(Connection *connection)=0;

	virtual int Stop()=0;

	virtual ~MeterProtocol();
};

#endif