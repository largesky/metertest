#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H
#include "MeterBaseComm.h"

template <typename Item,typename Manager >
class  ItemManager
{
protected :
	std::map<const wchar_t *,Item * > items;
	static Manager* Instance;
public :

	ItemManager()
	{
		Instance=static_cast<Manager*>( this);
	}

	static Manager* GetInstance()
	{
		return Instance;
	}

	int InstallItem(Item* item)
	{
		std::map<const wchar_t *,Item *>::iterator index=this->items.find(item->GetName());
		if(index != this->items.end())
		{
			return -1;
		}
		this->items[item->GetName()]=item;
		return 0;
	}

	int UninstallItem(const wchar_t* name)
	{
		this->items.erase(name);
		return 0;
	}

	Item* GetItemByName(const wchar_t *itemName)
	{
		std::map<const wchar_t *,Item *>::iterator index=this->items.begin();
		while(index != this->items.end())
		{
			if(_tcscmp(index->first,itemName) ==0)
			{
				return index->second;
			}
			index++;
		}
		return 0;
	}

	std::vector<const wchar_t *> GetAllItemNames()
	{
		std::vector<const wchar_t*> names;
		std::map<const wchar_t*, Item *>::iterator index=this->items.begin();
		while(index != this->items.end())
		{
			names.push_back(index->first);
			index++;
		}
		return names;
	}

	void GetAllItemNameAndDes(std::map<const wchar_t *,const wchar_t*> *value)
	{
		std::map<const wchar_t *,Item *>::iterator index=this->items.begin();
		while(index != this->items.end())
		{
			(*value)[index->first]=index->second->GetDes();
			index++;
		}
	}
};
template <typename Item,typename Manager> Manager* ItemManager<Item,Manager>::Instance=0;
#endif