#include "..\Include\MeterBase\PluginManager.h"
#include "..\Include\MeterBase\Plugin.h"
#include <MsXml2.h>
#include <objbase.h>
#include <ObjIdl.h>
#include <ObjSafe.h>
#include <atlbase.h>
#include <atlcom.h>
#include "..\Include\MeterBase\FileHelper.h"
#include "..\Include\MeterBase\XmlHelper.h"
#include "..\Include\MeterBase\MeterBase.h"

using namespace LargeSky;

std::map<const wchar_t *,PluginManager *> PluginManager::pluginManagers;

PluginManager::PluginManager(const wchar_t * name,const wchar_t * file)
{
	this->SetName(name);
	this->SetConfigFile(file);
}

const wchar_t * PluginManager::GetConfigFile()
{
	return this->configFile;
}

void PluginManager::SetConfigFile(const wchar_t * file)
{
	if(file ==0)
	{
		this->configFile=0;
		return ;
	}
	size_t len=_tcslen(file)+1;
	wchar_t * tmp=new wchar_t[len];
	_tcscpy_s(tmp,len,file);
	this->configFile=tmp;
}

const wchar_t * PluginManager::GetName()
{
	return this->name;
}

void PluginManager::SetName(const wchar_t * name)
{
	if(name ==0)
	{
		return ;
	}
	size_t len=_tcslen(name)+1;
	wchar_t *tmp=new wchar_t[len];
	_tcscpy_s(tmp,len,name);
	this->name=tmp;
}

PluginManager::~PluginManager()
{
	delete this->configFile;
	delete this->name;
}

bool PluginManager::AddPluginManager(PluginManager * pluginManager)
{
	pluginManagers[pluginManager->GetName()]=pluginManager;
	return true;
}

bool PluginManager::RemovePluginManager(const wchar_t *name)
{
	std::map<const wchar_t *,PluginManager *>::iterator index=pluginManagers.find(name);
	if(index == pluginManagers.end())
	{
		return false;
	}
	pluginManagers.erase(name);
	return true;
}

int PluginManager::LoadPlugins()
{
	int loaded=0;

	for(size_t i=0; i<this->plugins.size();i++)
	{
		if(this->plugins[i]->Load())
		{
			loaded++;
		}
	}
	return loaded;
}

int PluginManager::UnLoadPlugins()
{
	int unLoadedPlugin=0;
	return unLoadedPlugin;
}

int PluginManager::LoadFromPluginFile(const wchar_t *configFile)
{
	std::vector<LargeSky::Plugin *> plugins;
	int loadedPlugin=0;
	wchar_t moduleDir[MAX_PATH]={0};
	wchar_t configFilePath[MAX_PATH]={0};

	_tcscpy_s(configFilePath,MAX_PATH,configFile);
	if(GetAbsoFilePath(configFilePath) ==false)
	{
		return 0;
	}
	if(GetAbsoFilePath(moduleDir) ==false)
	{
		return 0;
	}

	//º”‘ÿ≤Âº˛
	XmlHelper xmlDoc;
	if(xmlDoc.LoadFile(configFilePath) !=true)
	{
		return 0;
	}
	IXMLDOMNodeList *pluginGroupNodes=0;
	if(xmlDoc.GetDoucumentElement()->selectNodes(L"/Plugins/PluginGroup",&pluginGroupNodes) != S_OK)
	{
		return -1;
	}
	IXMLDOMNode *pluginGroupNode=0;
	while(pluginGroupNodes->nextNode(&pluginGroupNode) == S_OK)
	{
		IXMLDOMNodeList *pluginNodes=0;
		if(pluginGroupNode->selectNodes(L"Plugin",&pluginNodes) !=S_OK)
		{
			continue;
		}
		IXMLDOMNode * pluginNode=0;
		while(pluginNodes->nextNode(&pluginNode) ==S_OK)
		{
			wchar_t dll[MAX_PATH]={0};
			IXMLDOMNode *dllNode=0;
			if(pluginNode->selectSingleNode(L"Dll",&dllNode) !=S_OK)
			{
				break;
			}
			VARIANT attValue;
			if(XmlHelper::GetAttribute(dllNode,L"value",&attValue) !=true)
			{
				continue;
			}
			std::wstring dllpath(moduleDir);
			dllpath.append(L"\\");
			dllpath.append(attValue.bstrVal);
			if(FileHelper::FileExist(dllpath.c_str()) ==false)
			{
				dllpath.clear();
				dllpath.append(moduleDir);
				dllpath.append(L"\\Plugin\\");
				dllpath.append(attValue.bstrVal);
			}
			LargeSky::Plugin *plugin=new LargeSky::Plugin();
			plugin->SetModuleFile(dllpath.c_str());
			plugins.push_back(plugin);
		}
	}

	//º”‘ÿ
	for(size_t i=0 ;i <plugins.size();i++)
	{
		if(plugins[i]->Load())
		{
			loadedPlugin++;
		}
	}
	xmlDoc.Close();
	return loadedPlugin;
}

int PluginManager::LoadAllPlugins(const wchar_t *configFile,bool isFromFile)
{
	if(isFromFile)
	{
		return PluginManager::LoadFromPluginFile(configFile);
	}
	int loadedPlugin=0;
	std::map<const wchar_t *,PluginManager *>::iterator index=pluginManagers.begin();
	while(index != pluginManagers.end())
	{
		loadedPlugin+=index->second->LoadPlugins();
		index ++;
	}
	return loadedPlugin;
}

int PluginManager::GetPluginManagerCount()
{
	return (int) pluginManagers.size();
}

int PluginManager::UnLoadAllPlugins()
{
	int loadedPlugin=0;

	std::map<const wchar_t *,PluginManager *>::iterator index=pluginManagers.begin();
	while(index != pluginManagers.end())
	{
		loadedPlugin+=index->second->UnLoadPlugins();
	}
	return loadedPlugin;
}