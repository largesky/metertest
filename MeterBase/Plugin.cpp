
#include "..\Include\MeterBase\Plugin.h"
using namespace LargeSky;

Plugin::Plugin()
{
	this->pluginDes=0;
	this->pluginName=0;
	this->pluginType=0;
	this->moduleFile=0;
	this->hModule=NULL;
}

Plugin::~Plugin()
{
	delete this->pluginDes;
	delete this->pluginName;
	delete this->pluginType;
	delete this->moduleFile;
}

const wchar_t * Plugin::GetPluginType()
{
	return this->pluginType;
}

void Plugin::SetPluginType(const wchar_t * value)
{
	this->pluginType=value;
}

const wchar_t * Plugin::GetPluginName()
{
	return this->pluginName;
}

void Plugin::SetPluginName(const wchar_t * value)
{
	this->pluginName=value;
}

const wchar_t * Plugin::GetPluginDes()
{
	return this->pluginDes;
}

void Plugin::SetPluginDes(const wchar_t * value)
{
	this->pluginDes=value;
}

bool Plugin::GetIsOK()
{
	return this->isOK;
}

const wchar_t * Plugin::GetModuleFile()
{
	return this->moduleFile;
}

void Plugin::SetModuleFile(const wchar_t *value)
{
	size_t len=_tcslen(value) +1;
	wchar_t *tmp=new wchar_t[len];
	_tcscpy_s(tmp,len,value);
	this->moduleFile=tmp;
}

bool Plugin::Load()
{
	if(this->moduleFile==0)
	{
		this->isOK=false;
		return false;
	}
	this->hModule=LoadLibrary(this->moduleFile);
	if(this->hModule ==NULL)
	{
		this->isOK=false;
		return false;
	}

	GETPLUGINTYPECALLBACK * typeCallBack=(GETPLUGINTYPECALLBACK*)GetProcAddress(this->hModule,"GETPLUGINTYPE");
	if(typeCallBack ==0)
	{
		this->isOK=false;
		return false;
	}

	const wchar_t * type=typeCallBack();
	this->SetPluginType(type);

	GETPLUGINDNAMECALLBACK * nameCallBack=(GETPLUGINDNAMECALLBACK *)GetProcAddress(this->hModule,"GETPLUGINNAME");
	if(nameCallBack ==0)
	{
		this->isOK=false;
		return false;
	}
	const wchar_t *name=nameCallBack();
	this->SetPluginName(name);

	GETPLUGINDESCALLBACK * desCallBack=(GETPLUGINDESCALLBACK *)GetProcAddress(this->hModule,"GETPLUGINDES");
	if(desCallBack==0)
	{
		this->isOK=false;
		return false;
	}
	const wchar_t *des=desCallBack();
	this->SetPluginDes(des);

	INSTALLCALLBACK * install=(INSTALLCALLBACK *)GetProcAddress(this->hModule,"INSTALL");
	if(install ==0)
	{
		this->isOK=false;
		return false;
	}

	DWORD ret=install();
	if(ret !=0)
	{
		this->isOK=false;
		return false;
	}
	return true;
}

bool Plugin::UnLoad()
{
	if(this->hModule !=0)
	{
		UNINSTALLCALLBACK* uninstall=(UNINSTALLCALLBACK*)GetProcAddress(this->hModule,"UNINSTALL");
		if(uninstall !=0)
		{
			uninstall();
		}
		FreeLibrary(this->hModule);
	}
	return true;
}