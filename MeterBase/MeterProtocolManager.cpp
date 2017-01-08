#include "..\Include\MeterBase\MeterProtocolManager.h"

MeterProtocolManager::MeterProtocolManager()
{
}

int MeterProtocolManager::InitAll()
{
	std::map<const wchar_t * ,MeterProtocol *>::iterator index=this->items.begin();
	while(index != this->items.end())
	{
		index->second->Init();
		index++;
	}
	return 0;
}