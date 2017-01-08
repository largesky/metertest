#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include "MeterBaseComm.h"
#include "ItemManager.h"
#include "Connection.h"

class METERBASE_API ConnectionManager : public ItemManager<Connection,ConnectionManager>
{
public :
	ConnectionManager();
};
#endif