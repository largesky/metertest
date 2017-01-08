
#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "MeterBaseComm.h"

namespace LargeSky
{
	class Plugin;

	class METERBASE_API PluginManager
	{
	protected :
		//配置文件路径
		wchar_t * configFile;
		//插件管理者名称
		wchar_t * name;

		static std::map<const wchar_t * ,PluginManager *> pluginManagers;

		std::vector<Plugin *> plugins;
	public :

		PluginManager(const wchar_t * name,const wchar_t * configFile);

		const wchar_t *GetConfigFile();
		void SetConfigFile(const wchar_t *file);

		const wchar_t *GetName();
		void SetName(const wchar_t *name);

		int LoadPlugins();

		int UnLoadPlugins();

		static bool AddPluginManager(PluginManager * pluginManager);

		static bool RemovePluginManager(const wchar_t * name);

		static int LoadAllPlugins(const wchar_t *configFile,bool isFromFile);

		static int GetPluginManagerCount();

		static int LoadFromPluginFile(const wchar_t *configFile);

		static int UnLoadAllPlugins();

		~PluginManager();
	};
}
#endif