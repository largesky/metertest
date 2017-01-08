#ifndef PLUGIN_H
#define PLUGIN_H
#include "MeterBaseComm.h"

namespace LargeSky
{
	/*
	²å¼þÀà
	**/
	class METERBASE_API Plugin
	{
	protected:
		const wchar_t *pluginType;
		const wchar_t *pluginName;
		const wchar_t *pluginDes;
		const wchar_t *moduleFile;
		bool isOK;
		HMODULE hModule;

		void SetPluginType(const wchar_t * value);
		void SetPluginName(const wchar_t * value);
		void SetPluginDes(const wchar_t * value);

	public :

		Plugin();

		const wchar_t *GetPluginType();

		const wchar_t *GetPluginName();

		const wchar_t *GetPluginDes();

		const wchar_t *GetModuleFile();

		void SetModuleFile(const wchar_t * moduleFile);

		bool GetIsOK();

		bool Load();

		bool UnLoad();

		~Plugin();
	};
}
#endif