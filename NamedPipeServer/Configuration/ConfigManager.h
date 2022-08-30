#pragma once

#include "Utils/Utils.h"
#include "PipeServer/PipeServer.h"
#include "Configs.h"

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

class ConfigManager
{
private:
	std::unordered_map<std::string, std::string> ConfigMap{ };

	bool LoadToConfigMap();
	void LoadToServerConfigsCache();
	void LoadToClientConfigsCache() const;

	template<typename T>
	void Add(const std::string& key, T value)
	{
		std::stringstream ss; ss << value;
		ConfigMap.try_emplace(key, ss.str());
	}

	void Add(const std::string& key, std::string& value)
	{
		ConfigMap.try_emplace(key, value);
	}

public:
	const std::string CONFIG_VALID_KEY_CHARS = "abcdefghijklmnopqrstuvwxyz_0123456789";
	const std::string CONFIG_WHITESPACES = " \t\r\n\v\b\f";
	const std::wstring ConfigFileName = L"config";

	std::wstring ConfigDirPath = L"\\TRAINER\\WalkingZombie2\\";
	std::wstring ConfigFilePath{ };

	bool Setup();

	bool Load();

	bool Save(bool sortAlphabetically = false) const;

	template<typename T>
	T Get(const std::string& key, T no_key_value, bool add_when_not_found = false)
	{
		T value{ };

		try
		{
			std::stringstream stringValue(ConfigMap.at(key));
			stringValue >> value;
			return value;
		}
		catch (...)
		{
			if (add_when_not_found)
			{
				Add(key, no_key_value);
			}

			return no_key_value;
		}
	}

	const char* GetAsCStr(const std::string& key, const char* no_key_value, bool add_when_not_found = false)
	{
		try
		{
			return ConfigMap.at(key).c_str();
		}
		catch (...)
		{
			if (add_when_not_found)
			{
				Add(key, no_key_value);
			}

			return no_key_value;
		}
	}

	template<typename T>
	void Set(const std::string& key, T value, bool add_when_not_found = false)
	{
		// Convert T to lowercase string
		std::string stringValue{ std::to_string(value) };
		Utils::ToLowerStr(stringValue);

		try
		{
			ConfigMap.at(key) = stringValue;
		}
		catch (const std::out_of_range& e)
		{
			if (add_when_not_found)
			{
				Add(key, stringValue);
			}

			spdlog::error("[ConfigMap.at] {0}", e.what());
		}
	}
};

extern ConfigManager g_ConfigManager;
#endif 