#ifndef METERPROTOCOLMANAGER_H
#define METERPROTOCOLMANAGER_H
#include "MeterBaseComm.h"
#include "ItemManager.h"
#include "MeterProtocol.h"

class METERBASE_API MeterProtocolManager :public ItemManager<MeterProtocol,MeterProtocolManager>
{
public :
	MeterProtocolManager();
	
	int InitAll();
};
#endif